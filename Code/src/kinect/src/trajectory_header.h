// PCL headers
#include <iostream>
#include <sstream> 
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/kdtree/kdtree_flann.h>

// ROS headers
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <std_srvs/Empty.h>

// ROS message types header
#include <kinect/KinectCommand.h>
#include <kinect/SensorCommand.h>
#include <mitsubishi_melfa/MelfaCommand.h>
#include <mitsubishi_melfa/PositionCommand.h>




