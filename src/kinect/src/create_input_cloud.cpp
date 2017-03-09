// pcl headers
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl/console/parse.h>

// visualization headers
#include <pcl/io/openni_grabber.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/point_picking_event.h>
#include <boost/thread/thread.hpp>

// filters headers
#include <pcl/filters/filter.h>
#include <pcl/filters/passthrough.h>

// ros headers
#include "ros/ros.h"

using namespace std;
using namespace pcl;

#define PATH_TO_FILE "/home/melfa/objects" 

int i=0; // Holds the index of the point of the cloud
Grabber* openniGrabber;  // OpenNI grabber that takes data from the device.
pcl::PointCloud<pcl::PointXYZ> cloud; // The input.pcd point cloud
boost::shared_ptr<visualization::CloudViewer> viewer;   // Point cloud viewer object
PointCloud<PointXYZRGBA>::Ptr filtered_fov(new PointCloud<PointXYZRGBA>);  // Filtered Field of View

void showHelp(char * program_name);  // This function displays the help
void grabberCallback(const PointCloud<PointXYZRGBA>::ConstPtr& cloud); // This function is called every time the device has new data.
void pp_callback (const visualization::PointPickingEvent& event, void* viewer_void);  // Obtain the XYZ point coordinates of a point that the user just clicked on. 

boost::shared_ptr<visualization::CloudViewer> createViewer()
{
    boost::shared_ptr<visualization::CloudViewer> v
    (new visualization::CloudViewer("Input cloud"));
    v->registerPointPickingCallback(pp_callback);

    return (v);
}

// Main function
int main (int argc, char** argv)
{
    // Show help
  if (console::find_switch (argc, argv, "-h") || console::find_switch (argc, argv, "--help"))
  {
      showHelp (argv[0]);
      return 0;
  }

  // Ros init
  ros::init(argc, argv, "create_input_cloud");
  ros::NodeHandle n;
  ros::Rate loop_rate(100);

  // Set cloud size
  cloud.resize(15);

  // Init OpenNIGrabber
  openniGrabber = new OpenNIGrabber();
  if (openniGrabber == 0)
      return -1;
  boost::function<void (const PointCloud<PointXYZRGBA>::ConstPtr&)> f = boost::bind(&grabberCallback, _1);
  openniGrabber->registerCallback(f);

  viewer = createViewer();
  openniGrabber->start();

  while (ros::ok() && !viewer->wasStopped())
  {
      boost::this_thread::sleep(boost::posix_time::seconds(1));
      ros::spinOnce();
      loop_rate.sleep();
  }

  return (0);
}


/** Cycle **/   
void grabberCallback(const PointCloud<PointXYZRGBA>::ConstPtr& viz_cloud)
{
      if (! viewer->wasStopped())
    {
        // Filter the field of view of the kinect       
        PassThrough<PointXYZRGBA> filter_fov; // Passthrough Filter object
        filter_fov.setInputCloud(viz_cloud);
        filter_fov.setFilterFieldName("x");
        filter_fov.setFilterLimits(-0.25,0.25);
        filter_fov.filter(*filtered_fov);

        filter_fov.setInputCloud(filtered_fov);
        filter_fov.setFilterFieldName("y");
        filter_fov.setFilterLimits(0.05,0.7);
        filter_fov.filter(*filtered_fov);

        filter_fov.setInputCloud(filtered_fov);
        filter_fov.setFilterFieldName("z");
        filter_fov.setFilterLimits(0.7,3);
        filter_fov.filter(*filtered_fov);

        viewer->showCloud(filtered_fov);
    }
}

// Fill in the cloud here
void pp_callback (const visualization::PointPickingEvent& event, void* viewer_void)
{ 
    if (event.getPointIndex () == -1)
    {
        return;
    }

    // Get the coordinates of the point
    float x,y,z; 
    event.getPoint(x,y,z);  

    // Save the point in cloud (in mm)
    cloud.points[i].x = 1000*x;    cloud.points[i].y = 1000*y; cloud.points[i].z = 1000*z;  
    cout << "The XYZ coordinates of the point " << i+1 <<" are: ("
        << x << ", "
        << y << ", "
        << z << ")." << endl;

    // Increment the cloud index
    i++;

    // The cloud is competly filled
    if(i==15)
    { 
      // Save the cloud as input.pcd
      stringstream filename;
      filename << PATH_TO_FILE << "/input.pcd";
      pcl::io::savePCDFileASCII (filename.str(), cloud);
      std::cerr << "Saved " << cloud.points.size () << " data points to input.pcd." << std::endl;    
      
      // Terminate node
      ros::shutdown();
    }
}

/** Help **/ 
void showHelp(char * program_name)
{
    cout << endl;
    cout << "Usage: " << program_name << endl;
    cout << "-h:  Show this help.\n" << endl;
    cout << "Create input.pcd cloud for the camera calibration \n";    
    cout << "The user add the coordinate of the 15 points of cloud \n"
         << "by simply holding SHIFT key and pressing on the desired\n"
         << "point from the seen enviorement.\n"
    << endl;
}
