/*
 * Trajectory Generator ROS node.
 * It publishes sample points of a desired trajectory.
 */

// ROS
#include "ros/ros.h"
#include <mitsubishi_melfa/PositionCommand.h>
#include <mitsubishi_melfa/MelfaCommand.h>

// STANDARD
#include <fstream>
#include <vector>
#include <queue>
#include <ostream>
#include <iostream>
#include <math.h>  

// utility structure
struct Offset
{
  float x;
  float y;
  float z;  
};

// container
std::vector<mitsubishi_melfa::PositionCommand> AllTargets;
std::queue<mitsubishi_melfa::MelfaCommand> AllMessages;

// Set maximal velocity
const float fMaximalIncrement = 1.775; // [mm]. 1.775 Mmm / 7.1 ms = 250 mm/s. This is the maximum speed of the teach pad.

// subscriber callback
void new_target_position(const mitsubishi_melfa::PositionCommand& NewPos) 
{
  // check if velocity is valid
  double dMinVelocity = 0.01;
  if(NewPos.velocity_factor < dMinVelocity)
  {
  	std::cout << "Velocity factor invalid. Must be higher than 0.01. Not processing current command." << std::endl;
  	return;
  }

  // Define Control and recieve type
  // Control type: 0: None / 1: XYZ / 2:JOINT / 3: PULSE
  int iControl_Type = 1;

  //define data to monitor:
  //[0: None]
  //[1: XYZ / 2:JOINT / 3: PULSE] Command value
  //[4: XYZ/ 5: JOINT/ 6: PULSE] Command value after the filter process 
  //[7: XYZ/ 8:JOINT/ 9:PULSE] Feedback value
  char cRecieve_1 = 1;
  char cRecieve_2 = 4;
  char cRecieve_3 = 7;
  char cRecieve_4 = 10;

  // This determines the velocity. It is set in the PositionCommand message
  float fIncrement = fMaximalIncrement * NewPos.velocity_factor;

  // get last position
  mitsubishi_melfa::PositionCommand LastPos;
  LastPos = AllTargets.back();

  // save new target
  AllTargets.push_back(NewPos);

  // calc distance between targets
  float fDeltaX = NewPos.x - LastPos.x;
  float fDeltaY = NewPos.y - LastPos.y;
  float fDeltaZ = NewPos.z - LastPos.z;    
  float fDistanceBetweenTargets = sqrt(fDeltaX*fDeltaX + fDeltaY*fDeltaY +  fDeltaZ*fDeltaZ);

  // calculate distance between sample points
  float fNecessaryIncrements = floor(fDistanceBetweenTargets / fIncrement);

  Offset NewOffset;
  NewOffset.x = fDeltaX / fNecessaryIncrements;
  NewOffset.y = fDeltaY / fNecessaryIncrements;
  NewOffset.z = fDeltaZ / fNecessaryIncrements;

  if(isnan(NewOffset.x) || isnan(NewOffset.y) || isnan(NewOffset.z) )
  {
  	std::cout << "Invalid sample point. Not processing current command." << std::endl;
  	return;
  }

  // compute sample points
  for(int i = 0; i <= fNecessaryIncrements; i++)
  {
    // compute new point towards the goal
    if(i < fNecessaryIncrements)
    {
      LastPos.x += NewOffset.x;
      LastPos.y += NewOffset.y;
      LastPos.z += NewOffset.z;
    }
    // if goal is reached save it as last sample point
    else
    {
      LastPos.x = NewPos.x;
      LastPos.y = NewPos.y;
      LastPos.z = NewPos.z;
    }

    // pack to melfa message
    mitsubishi_melfa::MelfaCommand NewMelfaMessage;

    NewMelfaMessage.iControl_type = iControl_Type;
    NewMelfaMessage.Type_Monitor1 = cRecieve_1;
    NewMelfaMessage.Type_Monitor2 = cRecieve_2;
    NewMelfaMessage.Type_Monitor3 = cRecieve_3;
    NewMelfaMessage.Type_Monitor4 = cRecieve_4;

    NewMelfaMessage.x = LastPos.x;
    NewMelfaMessage.y = LastPos.y;
    NewMelfaMessage.z = LastPos.z;
    NewMelfaMessage.rot_x = (float)0.0;
    NewMelfaMessage.rot_y = (float)0.0;
    NewMelfaMessage.rot_z = (float)0.0;

    AllMessages.push(NewMelfaMessage);
  }

}


int main(int argc, char **argv)
{
  // set first target to zero (origin)
  mitsubishi_melfa::PositionCommand StartPos;
  StartPos.x = 0;
  StartPos.y = 0;
  StartPos.z = 0;
  StartPos.velocity_factor = 0.1;
  AllTargets.push_back(StartPos);

  // ROS inits
  ros::init(argc, argv, "mitsubishi_trajectory_generator");
  ros::NodeHandle rosNodeHandle;
  ros::Publisher chatter_pub = rosNodeHandle.advertise<mitsubishi_melfa::MelfaCommand>("mitsubishi_target_sample_positions", 1000);
  ros::Subscriber chatter_sub = rosNodeHandle.subscribe("mitsubishi_targets",1000, new_target_position);
  
  ros::Rate loop_rate(300);

  std::cout << "Trajectory generator successfully initialized" << std::endl;

  // main loop
  int count = 0;
  while (ros::ok())
  {
    if(!AllMessages.empty())
    {
      mitsubishi_melfa::MelfaCommand Next_Message = AllMessages.front();
      AllMessages.pop();

      ROS_INFO("ControlType: %i Current Position: X: %f, Y: %f, Z: %f", Next_Message.iControl_type, Next_Message.x, Next_Message.y, Next_Message.z );
      chatter_pub.publish(Next_Message);
    }

    ros::spinOnce();
    loop_rate.sleep();
    count++;
  }


  return 0;
}
