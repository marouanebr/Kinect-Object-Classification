#include "trajectory_header.h"

// ROS publisher and subscriber
ros::Publisher sensor_publisher; // to start/end recording data corresponding an object
ros::Publisher trajectory_publisher; // to send the trajectory that the arm should follows
ros::Subscriber position_subscriber;  // to get the current position of the robot's arm
ros::Subscriber objects_subscriber; // to start/end the process of the objects

// ROS messages
mitsubishi_melfa::MelfaCommand currentPos; // Holds the current position of the robot's arm
mitsubishi_melfa::PositionCommand Point; // Holds the desired position of the robot's arm	
kinect::SensorCommand sensor; // controls the classification node 

using namespace std;
using namespace pcl;


/** Variables **/
// The offset corresponds to the point P1 of the robot's arm
#define OFFSET_X 0.009992
#define OFFSET_Y 250.000015
#define OFFSET_Z 290.029999
#define SENSOR_HEIGHT 100
#define VELOCITY_FACTOR 0.3

/** Function headers **/
void trajectoryCallback(const kinect::KinectCommand::ConstPtr & command);  // For sending the trajectory to follow by the robot's arm
void positionCallback(const mitsubishi_melfa::MelfaCommand::ConstPtr & Status); // For getting the current position of the robot arm

/** Main **/
int main(int argc, char **argv)
{
	/** ROS Stuff **/
    // Initialize node   
	ros::init(argc, argv, "objects_trajectory");	
	ros::NodeHandle n;
	ros::Rate loop_rate(1000);


	// Initialize publishers and subscriber
	objects_subscriber = n.subscribe("object_detected", 1000, trajectoryCallback); 		  // New objects detected
	position_subscriber = n.subscribe("mitsubishi_melfa_status", 1000, positionCallback); // Get current position
	sensor_publisher = n.advertise<kinect::SensorCommand>("sensor_topic", 1000, true); 	  // Notify the sensor to start/end the object processing
	trajectory_publisher = n.advertise<mitsubishi_melfa::PositionCommand>("mitsubishi_targets", 10, true); // Move the robot's arm

	while (ros::ok())
	{
		ros::spinOnce();
		loop_rate.sleep();
	}
	
	return 0;
}

/** Move along trajectory **/
void trajectoryCallback(const kinect::KinectCommand::ConstPtr & command)
{
	if(command->start == true) // Start command is received (from the object_detection node)
	{
	  	ROS_INFO("New objects detected!\n");   

	  	// Point clouds objects
		PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>); 	 		 // Holds the object trajectory 
		PointCloud<pcl::PointXYZ>::Ptr orgonized_cloud (new pcl::PointCloud<pcl::PointXYZ>); // Holds the orgonized trajectory 

		// Set the velocity factor
		Point.velocity_factor = VELOCITY_FACTOR; 

		/** Cycle **/
		for( int i = 0; i < command->objNum; i++) // For each object	
		{
			//  1- Go to initial position 	        
	        std::cout << "Go to initial Position" << std::endl; 
			Point.x = 0;	Point.y = 0;	Point.z = 0;			  	
			trajectory_publisher.publish(Point); // Move the robot's arm

			// 2- Wait until initial position is reached
			bool cond_x, cond_y, cond_z, reached; // Conditions
			do
			{		
				cond_x = int(currentPos.x) == int(OFFSET_X);
				cond_y = int(currentPos.y) == int(OFFSET_Y);
				cond_z = int(currentPos.z) == int(OFFSET_Z);
				reached = cond_x && cond_y && cond_z;
				ros::spinOnce();
			}
			while(!reached);

			std::cout << "Initial position reached. \n \n " << std::endl; 
    		ros::Duration(2).sleep();	// Tempo to be sure that the sensor is stable

	  		cout << "*** Processing the object *** \n \n " << endl;

			// 3- Load the point cloud data of the object trajectory
	        stringstream filename;	
	        filename << "/home/melfa/objects/trajectory_cloud_" << i << ".pcd";
	  		if (pcl::io::loadPCDFile<pcl::PointXYZ> (filename.str(), *cloud) == -1)  //* load the file
			{
			    PCL_ERROR ("Couldn't read file filename.str() \n");
			    return;
			} 		
			else
			{
				std::cout << "Loaded "
	            << cloud->width * cloud->height
	            << " data points from "<< filename.str() << " for the object with id: " << i << "\n"
	            << std::endl;
			}			    

			// 4- Orgonize the cloud 
			*orgonized_cloud  = *cloud;
			// kdTree object
			pcl::KdTreeFLANN<pcl::PointXYZ> kdtree;
			kdtree.setInputCloud (cloud);
			pcl::PointXYZ searchPoint;

			// Set first point in the cloud
			orgonized_cloud->points[0].x = cloud->points[0].x;
			orgonized_cloud->points[0].y = cloud->points[0].y;
			orgonized_cloud->points[0].z = cloud->points[0].z;

			// Find the K nearest neighbor to the first point from the cloud object
			// and add them to the orgonized_cloud object
			int K = cloud->points.size () -1;

			std::vector<int> pointIdxNKNSearch(K);
			std::vector<float> pointNKNSquaredDistance(K);

			if ( kdtree.nearestKSearch (orgonized_cloud->points[0], K, pointIdxNKNSearch, pointNKNSquaredDistance) > 0 )
			{
				for (size_t n = 0; n < pointIdxNKNSearch.size (); ++n)				
				{			
					orgonized_cloud->points[n+1].x = cloud->points[ pointIdxNKNSearch[n] ].x;
					orgonized_cloud->points[n+1].y = cloud->points[ pointIdxNKNSearch[n] ].y;
					orgonized_cloud->points[n+1].z = cloud->points[ pointIdxNKNSearch[n] ].z;	
				}
			}
	    
			// 5- For each point of the trajectory	
		    for (size_t j = 0; j < orgonized_cloud->points.size (); ++j)
			{				
				// i- Display the coordinates
		    	std::cout << "Desired coordinates   " << orgonized_cloud->points[j].x
		              << " "    << orgonized_cloud->points[j].y
		              << " "    << orgonized_cloud->points[j].z + SENSOR_HEIGHT << std::endl;

		        // ii- Compute the realtive movement of the robot's arm      
				Point.x = orgonized_cloud->points[j].x;
				Point.y = orgonized_cloud->points[j].y;
				Point.z = orgonized_cloud->points[j].z + SENSOR_HEIGHT; 
				
				// iii- Publish to the trajectory_generator node i.e. move the arm
			  	trajectory_publisher.publish(Point);

			  	// iv- Wait until the point is reached (otherwise the buffer gets full easily)
				do
				{		
					// Check each coordinate with some tolerance
					cond_x = (int(Point.x) <= ceil(currentPos.x - int(OFFSET_X))) && (int(Point.x) >= floor(currentPos.x - int(OFFSET_X)));
					cond_y = (int(Point.y) <= ceil(currentPos.y - int(OFFSET_Y))) && (int(Point.y) >= floor(currentPos.y - int(OFFSET_Y)));
					cond_z = (int(Point.z) <= ceil(currentPos.z - int(OFFSET_Z))) && (int(Point.z) >= floor(currentPos.z - int(OFFSET_Z)));
					reached = cond_x && cond_y && cond_z;
					ros::spinOnce();
				}
				while(!reached);
				std::cout << "Point reached! Go to next point \n" << std::endl;   				  

			  	// v- Notify the sensor node to start recording data when the first the object is touched
			  	if(j==0)
			  	{	
			  		ROS_INFO("Point 0 => Start recording object data \n"); 
			  		sensor.id = i;
					sensor.begin = 1;
					sensor.finish = 0;
					sensor_publisher.publish(sensor); // Notify the sensor to start processing the object i
			  	}
			  	else if (j == cloud->points.size()-1)
			  	{
			  		ROS_INFO("Final point => End recording object data"); 
			  		sensor.id = i;
					sensor.begin = 0;
					sensor.finish = 1;
					sensor_publisher.publish(sensor); // Notify the sensor to stop processing the object i
			  	}	
			  	//ros::Duration(1).sleep();	// tempo after each point reached (uncomment to check the correct operation)
	  		}
	  		cout << "\n \n*** Object processed *** \n \n " << endl;

	  		// 6- If the last object was processed
	  		if( i == command->objNum-1)
	  		{
				// Return to initial position 
				std::cout << "All object processed => Return to initial position" << std::endl;
				Point.x = 0;	Point.y = 0;	Point.z = 0;			  	
				trajectory_publisher.publish(Point);
			}
	  	}	  		  	
	  	cout << "\n************************  End of the cycle ************************ \n \n " << endl;
	}
}

/** Get current position of the robot's arm **/
void positionCallback(const mitsubishi_melfa::MelfaCommand::ConstPtr & Status)
{
	currentPos.x = Status->x;
	currentPos.y = Status->y;
	currentPos.z = Status->z;
}


