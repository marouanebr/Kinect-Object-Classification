/*
 * ROS node to test the anytime stop functionality.
 */

#include "ros/ros.h"
#include "std_msgs/Bool.h"


int main(int argc, char **argv)
{
  // init node
  ros::init(argc, argv, "mitsubishi_anytime_stop");
  // node handle
  ros::NodeHandle n;
  // init publisher
  ros::Publisher chatter_pub = n.advertise<std_msgs::Bool>("mitsubishi_anytime_stop", 1000);
  // publisher rate
  ros::Rate loop_rate(100);

  int count = 0;
  bool bStop = true;
  while (ros::ok())
  {

    ROS_INFO("%i", bStop);

    std_msgs::Bool Stop_Message;
    Stop_Message.data = bStop;
    chatter_pub.publish(Stop_Message);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
