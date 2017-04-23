cmake_minimum_required(VERSION 2.8.3)
project(kinect)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
  std_msgs
  message_generation
  pcl_conversions 
  pcl_ros 
  sensor_msgs
  mitsubishi_melfa
)

set(PCL_BUILD_TYPE Release)
## Generate messages in the 'msg' folder
 add_message_files(
   FILES
   KinectCommand.msg
   SensorCommand.msg
 )

## Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
   std_msgs
 )

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES assignment_2_1
  CATKIN_DEPENDS geometry_msgs roscpp rospy std_msgs message_runtime pcl_conversions pcl_ros sensor_msgs mitsubishi_melfa
)

include_directories(include
  ${PCL_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS}
)
 
#include_directories(${PCL_INCLUDE_DIRS})
#link_directories(${PCL_LIBRARY_DIRS})
#add_definitions(${PCL_DEFINITIONS})

#file(GLOB path_SRC
#	"src/*.h"
#	"src/*.cpp"
#)

add_executable(objects_trajectory src/objects_trajectory.cpp)
target_link_libraries(objects_trajectory ${catkin_LIBRARIES})

add_executable(objects_detection src/objects_detection.cpp)
target_link_libraries(objects_detection ${catkin_LIBRARIES} ${PCL_LIBRARIES} libvtkCommon.so libvtkFiltering.so)

add_executable(create_input_cloud src/create_input_cloud.cpp)
target_link_libraries(create_input_cloud ${catkin_LIBRARIES} ${PCL_LIBRARIES} libvtkCommon.so libvtkFiltering.so)

# add_executable (calibration src/calibration.cpp)
# target_link_libraries (calibration ${catkin_LIBRARIES} ${PCL_LIBRARIES} libvtkCommon.so libvtkFiltering.so)
