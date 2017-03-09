// pcl headers
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_cloud.h>
#include <pcl/console/parse.h>
#include <pcl/point_types.h>
#include "pcl/common/common_headers.h"
#include <pcl/registration/icp.h>

// visualization headers
#include <pcl/io/openni_grabber.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/point_picking_event.h>
#include <boost/thread/thread.hpp>

// filters headers
#include <pcl/filters/filter.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/conditional_removal.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/voxel_grid.h>

// pcl features
#include <pcl/features/normal_3d.h>
#include <pcl/common/centroid.h>
#include <pcl/octree/octree.h>
#include <pcl/common/transforms.h>

// c++ headers
#include <sstream> 
#include <unistd.h>
#include <stdio.h>

// ros headers
#include "ros/ros.h"
#include <std_srvs/Empty.h>
#include "std_msgs/String.h"

#define PATH_TO_FILE "/home/melfa/objects" 

using namespace std;
using namespace pcl;

float x,y,z; 

void pp_callback (const visualization::PointPickingEvent& event, void* viewer_void);
void showHelp(char * program_name);  // This function displays the help

// This is the main function
int main (int argc, char** argv)
{

    // Show help
  if (console::find_switch (argc, argv, "-h") || console::find_switch (argc, argv, "--help"))
  {
      showHelp (argv[0]);
      return 0;
  }


  ros::init(argc, argv, "calibration");
  ros::NodeHandle n;

  stringstream filename_1,filename_2;
  filename_1 << PATH_TO_FILE << "/input.pcd";
  filename_2 << PATH_TO_FILE << "/target.pcd";

  pcl::PointCloud<pcl::PointXYZ> cloud;
  pcl::PointCloud<pcl::PointXYZ>::Ptr input_cloud (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr transformed_cloud (new pcl::PointCloud<pcl::PointXYZ> ());
  pcl::PointCloud<pcl::PointXYZ>::Ptr translated_cloud (new pcl::PointCloud<pcl::PointXYZ> ());

  cloud.resize(15);

  // Fill the input cloud
  cloud.points[0].x = 0.108007;  cloud.points[0].y = 0.113452; cloud.points[0].z = 0.953;  // A
  cloud.points[1].x = 0.111554;  cloud.points[1].y = 0.166899;  cloud.points[1].z = 0.908;  // B
  cloud.points[2].x = 0.116851;   cloud.points[2].y = 0.221446;   cloud.points[2].z = 0.858; // C
  cloud.points[3].x = 0.0372124;   cloud.points[3].y = 0.111637;   cloud.points[3].z = 0.953; // D
  cloud.points[4].x = 0.04214;   cloud.points[4].y = 0.16598;   cloud.points[4].z = 0.903; // E
  cloud.points[5].x = 0.0461429;   cloud.points[5].y = 0.221;   cloud.points[5].z = 0.85; // F
  cloud.points[6].x = -0.0314;   cloud.points[6].y = 0.112143;   cloud.points[6].z = 0.942; // G
  cloud.points[7].x = -0.0262467;   cloud.points[7].y = 0.166793;   cloud.points[7].z = 0.889; // H
  cloud.points[8].x = -0.0232276;   cloud.points[8].y = 0.220262;   cloud.points[8].z = 0.841; // I
  cloud.points[9].x = -0.100839;   cloud.points[9].y = 0.111548;   cloud.points[9].z = 0.937; // J
  cloud.points[10].x = -0.0968191;   cloud.points[10].y = 0.165855;   cloud.points[10].z = 0.884; // K
  cloud.points[11].x = -0.0932657;   cloud.points[11].y = 0.220809;   cloud.points[11].z = 0.837; // L
  
  cloud.points[12].x = 0.107402;   cloud.points[12].y = 0.0914248;   cloud.points[12].z = 0.932; // 
  cloud.points[13].x = -0.0273114;   cloud.points[13].y = 0.146489;   cloud.points[13].z = 0.869; // 
  cloud.points[14].x = -0.103473;   cloud.points[14].y = 0.0930391;   cloud.points[14].z = 0.913; // 

  for (size_t i = 0; i < cloud.points.size (); ++i)
  {
    cloud.points[i].x = 1000*cloud.points[i].x;
    cloud.points[i].y = 1000*cloud.points[i].y;
    cloud.points[i].z = 1000*cloud.points[i].z;
  } 

  // Save input.pcd
  pcl::io::savePCDFileASCII (filename_1.str(), cloud);
  std::cerr << "Saved " << cloud.points.size () << " data points to input.pcd." << std::endl;
  io::loadPCDFile<PointXYZ>(filename_1.str(), *input_cloud);


  // Fill the target.pcd
  cloud.points[0].x = 0;    cloud.points[0].y = 0; cloud.points[0].z = 0;  // A
  cloud.points[1].x = 0;  cloud.points[1].y = 75;  cloud.points[1].z = 0;  // B
  cloud.points[2].x = 0;     cloud.points[2].y = 150;   cloud.points[2].z = 0; // C
  cloud.points[3].x = 70;   cloud.points[3].y = 0;   cloud.points[3].z = 0; // D
  cloud.points[4].x = 70;   cloud.points[4].y = 75;   cloud.points[4].z = 0; // E
  cloud.points[5].x = 70;   cloud.points[5].y = 150;   cloud.points[5].z = 0; // F
  cloud.points[6].x = 140;   cloud.points[6].y = 0;   cloud.points[6].z = 0; // G
  cloud.points[7].x = 140;   cloud.points[7].y = 75;   cloud.points[7].z = 0; // H
  cloud.points[8].x = 140;   cloud.points[8].y = 150;   cloud.points[8].z = 0; // I
  cloud.points[9].x = 210;   cloud.points[9].y = 0;   cloud.points[9].z = 0; // J
  cloud.points[10].x = 210;   cloud.points[10].y = 75;   cloud.points[10].z = 0; // K
  cloud.points[11].x = 210;   cloud.points[11].y = 150;   cloud.points[11].z = 0; // L
  cloud.points[12].x = 0;   cloud.points[12].y = 0;   cloud.points[12].z = 30; // 
  cloud.points[13].x = 140;   cloud.points[13].y = 75;   cloud.points[13].z = 30; // 
  cloud.points[14].x = 210;   cloud.points[14].y = 0;   cloud.points[14].z = 30; // 
  
  // Save target.pcd
  pcl::io::savePCDFileASCII (filename_2.str(), cloud);
  std::cerr << "Saved " << cloud.points.size () << " data points to target.pcd.\n" << std::endl;
  io::loadPCDFile<PointXYZ>(filename_2.str(), *target_cloud);


  // Transformation Estimation
  Eigen::Matrix<float, 4, 4> transform_icp;
  pcl::registration::TransformationEstimationSVD<pcl::PointXYZ, pcl::PointXYZ, float> estimate;
  estimate.estimateRigidTransformation(*input_cloud,*target_cloud,transform_icp);
  pcl::transformPointCloud (*input_cloud, *transformed_cloud, transform_icp);  

  // Print the transformation
  printf ("Transformation Matrix\n");
  std::cout << transform_icp << std::endl;

  // Add translation
  Eigen::Affine3f transform_t = Eigen::Affine3f::Identity();
  transform_t .translation() << -110, -60, -258;
  printf ("\nTranslation Matrix\n");
  std::cout << transform_t.matrix() << std::endl;
  pcl::transformPointCloud (*transformed_cloud, *translated_cloud, transform_t);


  // Print the results
  std::cout << "\n \n ORIGNIAL coordinates " << std::endl;
  for (size_t j = 0; j < input_cloud->points.size (); ++j)
    std::cout << "    " << input_cloud->points[j].x
              << " "    << input_cloud->points[j].y
              << " "    << input_cloud->points[j].z << std::endl;
  cout << "\n";

  std::cout << "\n \n TARGET coordinates " << std::endl;
  for (size_t j = 0; j < target_cloud->points.size (); ++j)
    std::cout << "    " << target_cloud->points[j].x
              << " "    << target_cloud->points[j].y
              << " "    << target_cloud->points[j].z << std::endl;
  cout << "\n";

  std::cout << "TRANSFORMED coordinates" << std::endl;
  for (size_t j = 0; j < transformed_cloud->points.size (); ++j)
  {  
    std::cout << "    " << int(transformed_cloud->points[j].x)
              << " "    << int(transformed_cloud->points[j].y)
              << " "    << int(transformed_cloud->points[j].z) << std::endl;           
  }
  cout << "\n";

  std::cout << "FINAL coordinates" << std::endl;
  for (size_t j = 0; j < translated_cloud->points.size (); ++j)
  {  
    std::cout << "    " << int(translated_cloud->points[j].x)
              << " "    << int(translated_cloud->points[j].y)
              << " "    << int(translated_cloud->points[j].z) << std::endl;           
  }
  cout << "\n";

 
  pcl::visualization::PCLVisualizer viewer ("Matrix transformation example");

  // Define R,G,B colors for the point cloud
  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> input_cloud_color_handler (input_cloud, 255, 255, 255);
  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_handler (transformed_cloud, 230, 20, 20); // Red
  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> target_cloud_color_handler (target_cloud, 20, 230, 20); // green
  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> translated_cloud_color_handler (translated_cloud, 20, 20, 230); // blue 

  viewer.addPointCloud (input_cloud, input_cloud_color_handler, "input_cloud");
  viewer.addPointCloud (transformed_cloud, transformed_cloud_color_handler, "transformed_cloud"); 
  viewer.addPointCloud (target_cloud, target_cloud_color_handler, "target_cloud");
  viewer.addPointCloud (translated_cloud, translated_cloud_color_handler, "taranslated_cloud");


  viewer.addCoordinateSystem (100, "cloud", 0);
  viewer.setBackgroundColor(0.05, 0.05, 0.05, 0); // Setting background to a dark grey
  viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "target_cloud");
  viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloud");
  viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "translated_cloud");

  viewer.registerPointPickingCallback (pp_callback, (void*)&viewer);

  while (!viewer.wasStopped ()) { // Display the visualiser until 'q' key is pressed
    viewer.spinOnce ();
  }

  return 0;
}

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


/** Help **/ 
void showHelp(char * program_name)
{
    cout << endl;
    cout << "Usage: " << program_name << endl;
    cout << "-h:  Show this help.\n" << endl;
    cout << "Create input.pcd and target.pcd clouds for the camera calibration \n";    
    cout << "and returns the transformation matrix between them \n"
    << endl;
}

