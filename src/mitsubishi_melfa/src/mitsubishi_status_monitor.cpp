/*
 * Status monitor ROS node.
 * It receives a MelfaCommand message and displays the content
 * on a terminal.
 */

#include "ros/ros.h"
#include <mitsubishi_melfa/MelfaCommand.h>

// callback function to display the contents of the message
void chatterCallback(const mitsubishi_melfa::MelfaCommand& Status)
{

  switch(Status.iControl_type)
  {
    case 1:
    ROS_INFO("Current Position: X: %f, Y: %f, Z: %f",  Status.x, Status.y, Status.z );
    break;

    case 2:
    ROS_INFO("Current Joint Configuration: J1: %f, J2: %f, J3: %f, J4: %f, J5: %f, J6: %f",  Status.j1, Status.j2, Status.j3, Status.j4, Status.j5, Status.j6);
    break;

    default:
    break;
  }

}

int main(int argc, char **argv)
{
  // init node
  ros::init(argc, argv, "mitsubishi_status_monitor");
  // node handle
  ros::NodeHandle n;
  // init subscriber
  ros::Subscriber sub = n.subscribe("mitsubishi_melfa_status", 1000, chatterCallback);
  ros::spin();

  return 0;
}
