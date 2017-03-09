// PCL headers
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/console/parse.h>
#include "pcl/common/common_headers.h"

// PCL visualization headers
#include <pcl/io/openni_grabber.h>
#include <boost/thread/thread.hpp>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/point_picking_event.h>

// PCL filters headers
#include <pcl/filters/filter.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/conditional_removal.h>
#include <pcl/filters/extract_indices.h>

// PCL clustering and transformation
#include <pcl/octree/octree.h>
#include <pcl/kdtree/kdtree.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/common/transforms.h>
#include <pcl/filters/project_inliers.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/sample_consensus/method_types.h>

// pcl features
#include <pcl/common/centroid.h>
#include <pcl/registration/icp.h>
#include <pcl/features/normal_3d.h>

// c++ headers
#include <sstream> 
#include <unistd.h>
#include <stdio.h>

// ROS headers
#include "ros/ros.h"
#include <std_srvs/Empty.h>
#include "std_msgs/String.h"
#include <kinect/KinectCommand.h>


