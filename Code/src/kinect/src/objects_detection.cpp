#include "detection_header.h"

using namespace std;
using namespace pcl;

/** Variables **/
// The coordinates of the point A in the robot's coordinates system
#define X_A -115
#define Y_A -10
#define Z_A -290

#define PATH_TO_FILE "/home/marouane/objects" 
// dimension for workspace
#define X_MINUS -0.25
#define X_PLUS 0.25
#define Y_MINUS -0.15
#define Y_PLUS 3
#define Z_MINUS 0.7
#define Z_PLUS 3

float x,y,z;                               // The coordinates of the clicked point
Grabber* openniGrabber;                    // OpenNI grabber that takes data from the device
unsigned int round_ctr = 0;                // A round counter for the numbering of the times new objects are introduced
bool keyPressed(false), hint(true);        // Checkes if the [SPACE] key is pressed
Eigen::Matrix<float, 4, 4> transform_pcl;  // Holds the transformation matrix with the TransformationEstimationSVD

ros::Publisher detection_publisher; // Ros publisher
kinect::KinectCommand command;      // Command to send to the object_trajectory node
                                    // i.e. to the /object_detected topic 

/** Functions **/
void showHelp(char * program_name);  // This function displays the help
void grabberCallback(const PointCloud<PointXYZRGBA>::ConstPtr& cloud); // This function is called every time the device has new data.
void keyboardEventOccurred(const visualization::KeyboardEvent& event, void* nothing); // For detecting when [SPACE] is pressed
void pp_callback (const visualization::PointPickingEvent& event, void* viewer_void);  // This function displays the coordinate of a point 
                                                                                      // simply by holding SHIFT and clicking on it in the viewer

/** Clouds **/ // Object for storing the point cloud.
PointCloud<PointXYZ>::Ptr source_cloud (new PointCloud<PointXYZ>);           // Ŝcene cloud (downsampled)
PointCloud<PointXYZ>::Ptr filtered_cloud (new PointCloud<PointXYZ>);         // Filtered cloud (only objects)
PointCloud<PointXYZRGBA>::Ptr filtered_fov(new PointCloud<PointXYZRGBA>);    // Filtered Field of View

/** Visualization **/
boost::shared_ptr<visualization::CloudViewer> viewer;           // Point cloud viewer object
visualization::PCLVisualizer main_viewer("Main cloud");         // Main visualizer for the source cloud and the objects
visualization::PCLVisualizer auxiliary_viewer("Trajectories");  // Auxiliary visualizer for the trajectories

// Creates, initializes and returns a new viewer.
boost::shared_ptr<visualization::CloudViewer> createViewer()
{
    boost::shared_ptr<visualization::CloudViewer> v
    (new visualization::CloudViewer("Kinect Viewer"));
    v->registerKeyboardCallback(keyboardEventOccurred);
    v->registerPointPickingCallback(pp_callback);
    return (v);
}

/** Main **/   
int main (int argc, char** argv)
{
    // Show help
    if (console::find_switch (argc, argv, "-h") || console::find_switch (argc, argv, "--help"))
    {
        showHelp (argv[0]);
        return 0;
    }

    // Initialize node   
    ros::init(argc, argv, "objects_detection");  
    ros::NodeHandle n;
    ros::Rate loop_rate(100);

    // Initialize publisher
    detection_publisher = n.advertise<kinect::KinectCommand>("object_detected", 1000); // Publish to object_detected topic
    
    // Add 3D colored axes to the viewer windows
    main_viewer.addCoordinateSystem(0.1, "reference", 0);
    auxiliary_viewer.addCoordinateSystem(100, "reference", 0);

    // Display the coodinate of a point by holding left SHIFT and clicking on it
    main_viewer.registerPointPickingCallback (pp_callback, (void*)&main_viewer);
    auxiliary_viewer.registerPointPickingCallback (pp_callback, (void*)&auxiliary_viewer);

    //** Compute the transformation matrix **/
    // Load the input and target clouds
    PointCloud<PointXYZ>::Ptr input_cloud (new PointCloud<PointXYZ>); 
    PointCloud<PointXYZ>::Ptr target_cloud (new PointCloud<PointXYZ>);
    stringstream filename_1,filename_2;
    filename_1 << PATH_TO_FILE << "/input.pcd";
    filename_2 << PATH_TO_FILE << "/target.pcd";
    io::loadPCDFile<PointXYZ>(filename_1.str(), *input_cloud); 
    io::loadPCDFile<PointXYZ>(filename_2.str(), *target_cloud);   
    registration::TransformationEstimationSVD<PointXYZ, PointXYZ, float> estimate;
    // Save the transformation matrix in transform_pcl
    estimate.estimateRigidTransformation(*input_cloud,*target_cloud,transform_pcl); 

    // Initialize OpenNIGrabber
    openniGrabber = new OpenNIGrabber();
    if (openniGrabber == 0)
        return -1;
    boost::function<void (const PointCloud<PointXYZRGBA>::ConstPtr&)> f = boost::bind(&grabberCallback, _1);
    openniGrabber->registerCallback(f);

    viewer = createViewer();
    openniGrabber->start();

    // Main loop, until one of the viewer is closed
    while (ros::ok() && !viewer->wasStopped() && !main_viewer.wasStopped() && !auxiliary_viewer.wasStopped())
    {
        boost::this_thread::sleep(boost::posix_time::seconds(1));
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
} 

/** Cycle **/   
void grabberCallback(const PointCloud<PointXYZRGBA>::ConstPtr& cloud)
{
    // Displays the scene from the Kinect
    if (! viewer->wasStopped())
    {
        // Filter the field of view of the kinect       
        PassThrough<PointXYZRGBA> filter_fov; // Passthrough Filter object
        // Filter X
        filter_fov.setInputCloud(cloud);
        filter_fov.setFilterFieldName("x");
        filter_fov.setFilterLimits(X_MINUS,X_PLUS);
        filter_fov.filter(*filtered_fov);

        // Filter Y
        filter_fov.setInputCloud(filtered_fov);
        filter_fov.setFilterFieldName("y");
        filter_fov.setFilterLimits(Y_MINUS,Y_PLUS);
        filter_fov.filter(*filtered_fov);

        // Filter Z
        filter_fov.setInputCloud(filtered_fov);
        filter_fov.setFilterFieldName("z");
        filter_fov.setFilterLimits(Z_MINUS,Z_PLUS);
        filter_fov.filter(*filtered_fov);

        // Display only the necessary workspace
        viewer->showCloud(filtered_fov); 
    }

    /** Display hint **/  
    if (hint)
    {
        cout << "Waiting for [SPACE] key to be pressed \n" << endl;
        hint = false; // Displays the hint only once
    }

    /** [SPACE] key is pressed i.e. Start the processing **/
    if (keyPressed) 
    {       
        main_viewer.removeAllPointClouds(0);   // Clear the auxiliary viewer for the new objects
        auxiliary_viewer.removeAllPointClouds(0);   // Clear the auxiliary viewer for the new objects
 
        round_ctr++;  // Increment the round number
        cout << "***********************  Start the processing cycle *********************** \n"  
             <<"Start processing objects for the " << round_ctr << " time.\n" << endl;

        /** Save the frame **/ 
        stringstream filename;
        filename << PATH_TO_FILE << "/scene.pcd";
        if (io::savePCDFile(filename.str(), *filtered_fov, false) == 0)
            {
                cout << "Frame saved. \n" << endl;
            }
        else 
            PCL_ERROR("Problem saving %s.\n", filename.str().c_str());

        // Load the scene as an XYZ source_cloud (without the RGB colors)
        PCDReader reader;
        reader.read (filename.str(), *source_cloud);

        /** Remove NaN  **/  // Remove NaN from Point Cloud        
        vector<int> mapping;
        removeNaNFromPointCloud(*source_cloud, *source_cloud, mapping);

        /** Downsampling  **/  // Create the filtering object: downsample the dataset using a leaf size of 1cm
        VoxelGrid<PointXYZ> vg;
        vg.setInputCloud (source_cloud);
        vg.setLeafSize (0.01f, 0.01f, 0.01f); // Leaf size can be adjusted here
        vg.filter (*source_cloud);

        // Add the point clouds to the main viewer and pass the color handler
        visualization::PointCloudColorHandlerCustom<PointXYZ> source_cloud_color_handler(source_cloud, 255, 255, 255);  // White
        main_viewer.addPointCloud (source_cloud, source_cloud_color_handler, "source cloud");

        /** Filtering  **/  // Filter the planar model (table) using RANSAC        
        // Create the segmentation object for the planar model and set all the parameters
        SACSegmentation<PointXYZ> seg;
        PointIndices::Ptr inliers (new PointIndices);
        ModelCoefficients::Ptr coefficients (new ModelCoefficients);
        PCDWriter writer;
        seg.setOptimizeCoefficients (true);
        seg.setModelType (SACMODEL_PLANE);
        seg.setMethodType (SAC_RANSAC);
        seg.setMaxIterations (1000);      // Set the maximum number of iterations
        seg.setDistanceThreshold (0.02); // Set the distance threshold
        ExtractIndices<PointXYZ> extract;

        int nr_points = (int) source_cloud->points.size ();
        // While 30% of the original cloud is still there
        while (source_cloud->points.size () > 0.3 * nr_points)
        {
            // Segment the largest planar component from the remaining cloud
            seg.setInputCloud (source_cloud);
            seg.segment (*inliers, *coefficients);
            if (inliers->indices.size () == 0)
            {
              cout << "Could not estimate a planar model for the given dataset." << endl;
              break;
            }
 
            // Extract the planar inliers from the input cloud
            extract.setInputCloud (source_cloud);
            extract.setIndices (inliers);
            // Remove the planar inliers, extract the rest
            extract.setNegative (true);
            extract.filter (*filtered_cloud);
            *source_cloud = *filtered_cloud;
        }        

        /** Clustering  **/  // Creating the KdTree object for the search method of the extraction        
        search::KdTree<PointXYZ>::Ptr tree (new search::KdTree<PointXYZ>);
        tree->setInputCloud (filtered_cloud);
        vector<PointIndices> cluster_indices;
        EuclideanClusterExtraction<PointXYZ> ec;
        ec.setClusterTolerance (0.01); // Cluster tolerance size can be adjusted here
        ec.setMinClusterSize (10);     // Minimum cloud size
        ec.setMaxClusterSize (25000);  // Maximum cloud size
        ec.setSearchMethod (tree);
        ec.setInputCloud (filtered_cloud);
        ec.extract (cluster_indices);

        int j = 0; // Number of objects clustered
        for (vector<PointIndices>::const_iterator it = cluster_indices.begin (); it != cluster_indices.end (); ++it)
        {
            PointCloud<PointXYZ>::Ptr cluster_cloud (new PointCloud<PointXYZ>); // Cluster cloud
            for (vector<int>::const_iterator pit = it->indices.begin (); pit != it->indices.end (); ++pit)
            cluster_cloud->points.push_back (filtered_cloud->points[*pit]);
            cluster_cloud->width = cluster_cloud->points.size ();
            cluster_cloud->height = 1;
            cluster_cloud->is_dense = true;

            // Save the object cloud
            stringstream ss, sc, sl;
            ss << PATH_TO_FILE << "/object_cloud_" << j << ".pcd";
            sc << PATH_TO_FILE << "/trajectory_cloud_" << j << ".pcd"; 
            sl << PATH_TO_FILE << "/line_trajectory_cloud_" << j << ".pcd"; 
            writer.write<PointXYZ> (ss.str (), *cluster_cloud, false);

            /** Centroid  **/  // Object to store the centroid coordinates
            Eigen::Vector4f centroid;
            compute3DCentroid(*cluster_cloud, centroid);            

            /** Filter the trajectory  **/
            PointCloud<PointXYZ>::Ptr trajectory_cloud(new PointCloud<PointXYZ>); 
            PointCloud<PointXYZ>::Ptr transformed_traj_cloud (new PointCloud<PointXYZ>); // Transformed trajectory 

            // Passthrough Filter to extract only a trajectory crossing the centroid
            PassThrough<PointXYZ> filter_trajectory;
            filter_trajectory.setInputCloud(cluster_cloud); 
            // Leave only a trajectory going through the y of centroid point 
            filter_trajectory.setFilterFieldName("y");
            filter_trajectory.setFilterLimits(centroid[1]-0.003, centroid[1]+0.003);
            filter_trajectory.filter(*trajectory_cloud);

            // Improve the trajectory with a VoxelGrid filter
            //vg.setInputCloud (trajectory_cloud);
            //vg.setLeafSize (0.05f, 0.2f, 0.02f); // Dimension of the 3D voxel grid 
            //vg.filter(*trajectory_cloud);

            /** Visualize on main_viewer  **/
            // Define R,G,B colors for the point cloud
            visualization::PointCloudColorHandlerCustom<PointXYZ> cluster_cloud_color_handler(cluster_cloud, 154, 205, 50);    // Green
            visualization::PointCloudColorHandlerCustom<PointXYZ> trajectory_cloud_color_handler(trajectory_cloud, 255, 0, 0); // Red
            // Add the objects and trajectory point clouds
            main_viewer.addPointCloud (cluster_cloud, cluster_cloud_color_handler, ss.str());
            main_viewer.addPointCloud (trajectory_cloud, trajectory_cloud_color_handler, sc.str());

            /** Transformation of the trajectory to the robot's coordinates system **/
            // Convert the trajectory_cloud from m to mm    
            for (size_t i = 0; i < trajectory_cloud->points.size (); ++i)
            {
                trajectory_cloud->points[i].x = 1000*trajectory_cloud->points[i].x;
                trajectory_cloud->points[i].y = 1000*trajectory_cloud->points[i].y;
                trajectory_cloud->points[i].z = 1000*trajectory_cloud->points[i].z;
            } 

            // First apply the transformattion between input and traget clouds
            transformPointCloud (*trajectory_cloud, *transformed_traj_cloud, transform_pcl);

            // Add a translation of the coordinates system from the point A to the robots's coordinates system
            Eigen::Affine3f transform_translation = Eigen::Affine3f::Identity();
            transform_translation.translation() << X_A, Y_A, Z_A;
            transformPointCloud (*transformed_traj_cloud, *transformed_traj_cloud, transform_translation);

            /** Projecting points of the trajectory to create a line **/
            PointCloud<PointXYZ>::Ptr cloud_projected (new PointCloud<PointXYZ>);

            // Obtain the cloud fitting to a line model
            ModelCoefficients::Ptr coefficients_line (new ModelCoefficients ()); // The 6 coefficients of the line
            PointIndices::Ptr inliers_line (new PointIndices);            
            SACSegmentation<PointXYZ> seg_line;
            seg_line.setOptimizeCoefficients (true);
            seg_line.setModelType (SACMODEL_LINE);
            seg_line.setMethodType (SAC_RANSAC);
            seg_line.setDistanceThreshold (1);

            seg_line.setInputCloud (transformed_traj_cloud);
            seg_line.segment (*inliers_line, *coefficients_line); 

            if (inliers_line->indices.size () == 0)
            {
              cout << "Could not estimate a line model for the given dataset." << endl;
              break;
            }

            // Projects the points on the obtained line model
            ProjectInliers<PointXYZ> proj;
            proj.setModelType (SACMODEL_LINE);
            proj.setInputCloud (transformed_traj_cloud);
            proj.setModelCoefficients (coefficients_line);
            proj.filter (*cloud_projected); 

            // Save the final trajectory cloud
            writer.write<PointXYZ> (sc.str (), *cloud_projected, false);

            /** Visualize on auxiliary_viewer  **/
            // Define R,G,B colors for the point cloud
            visualization::PointCloudColorHandlerCustom<PointXYZ> cloud_projected_color_handler(cloud_projected, 255, 150, 200); // Pink
            visualization::PointCloudColorHandlerCustom<PointXYZ> transformed_traj_cloud_color_handler(transformed_traj_cloud, 255, 255, 255); // White
            // Add the point clouds to the viewer and pass the color handler
            auxiliary_viewer.addPointCloud (cloud_projected, cloud_projected_color_handler, sl.str());
            auxiliary_viewer.addPointCloud (transformed_traj_cloud, transformed_traj_cloud_color_handler, sc.str());           

            /** Write the coordinates of the trajectory **/           
            cout << "The trajectory of the object_" << j << " is:" << endl;
            for (size_t k=0; k < cloud_projected->points.size (); ++k)
                cout << "    " << cloud_projected->points[k].x
                          << "    " << cloud_projected->points[k].y
                          << "    " << cloud_projected->points[k].z
                          << endl;
                cout << "\n" << endl;   

            j++; // Increment the object counter           
        } // End clustering
  
        cout << "The number of objects found is " << j << ".\n" << endl;
        keyPressed = false;  // Reset keyPressed
        hint = true; // Reset hint

        // Send a message to the /object_detected topic to signalize the start of processing the objects
        command.start = 1;  // Indicate to the object_trajectory node the presence of new objects
        command.objNum = j; // Holds the number of object
        detection_publisher.publish(command); // Send command

        cout << "\n************************  End the processing cycle ************************ \n \n " << endl;
    } 
    else
    {
        // Send a message to the /object_detected topic to signalize that the system is waiting for the [SPACE] key impulse
        command.start = 0;         
        detection_publisher.publish(command);
    }
} 

/** Help **/ 
void showHelp(char * program_name)
{
    cout << endl;
    cout << "Usage: " << program_name << endl;
    cout << "-h:  Show this help.\n" << endl;
    cout << "press [SPACE] to start the processing";    
    cout << "\nPoint cloud displayed :  \n"
         << "          in main_viewer: white = downsampled scene \n"
         << "                          green = objects\n"
         << "                            red = trajectory\n"
         << "          in auxiliary_viewer: white = original trajectory \n"
         << "                                pink = projected trajectory\n"
    << endl;
}

/** Keyboard **/  
void keyboardEventOccurred(const visualization::KeyboardEvent& event, void* nothing)
{
    if (event.getKeySym() == "space" && event.keyDown())
        keyPressed = true;
}

/** Coordinate **/   
void pp_callback (const visualization::PointPickingEvent& event, void* viewer_void)
{ 
    if (event.getPointIndex () == -1)
    {
        return;
    }
    event.getPoint(x,y,z);  
    cout << "The XYZ coordinates of the clicked point are: ("
        << x << ", "
        << y << ", "
        << z << ")." << endl;
}
