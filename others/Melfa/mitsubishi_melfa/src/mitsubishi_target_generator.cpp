/*
 * ROS node to test the trajectory generator.
 * It publishes position commands.
 */


// ROS
#include "ros/ros.h"
#include <mitsubishi_melfa/PositionCommand.h>

// STANDARD
#include <vector>
#include <fstream>
#include <ostream>
#include <iostream>

int main(int argc, char **argv)
{
	// Init node
	ros::init(argc, argv, "mitsubishi_target_generator");

	// init publisher
	ros::NodeHandle n;
	ros::Publisher chatter_pub = n.advertise<mitsubishi_melfa::PositionCommand>("mitsubishi_targets", 1000, true);
	ros::Rate loop_rate(0.2);

	// Target points
	std::vector<mitsubishi_melfa::PositionCommand> vecAllTargets;
	mitsubishi_melfa::PositionCommand NewPos;
	float Velocities[3] = {0.1,0.3,0.5};


	for(int i = 0; i < 3; i++)
	{
		// move 100 mm forward	
		NewPos.x = 0;
		NewPos.y = 100;
		NewPos.z = 0;
		NewPos.velocity_factor = Velocities[i];
		vecAllTargets.push_back(NewPos);

		// move 100 mm to left // and up
		NewPos.x = -100;
		NewPos.y = 100;
		NewPos.z = 100; // 100
		NewPos.velocity_factor = Velocities[i];
		vecAllTargets.push_back(NewPos);

		// move 100 mm back
		NewPos.x = -100;
		NewPos.y = 0;
		NewPos.z = 100; // 100
		NewPos.velocity_factor = Velocities[i];
		vecAllTargets.push_back(NewPos);

		// Move back to origin
		NewPos.x = 0;
		NewPos.y = 0;
		NewPos.z = 0;
		NewPos.velocity_factor = Velocities[i];
		vecAllTargets.push_back(NewPos);
	}

	std::cout << "Target generator successfully initialized" << std::endl;

	// main loop
	int count = 0;
	while (ros::ok())
	{
		// compute current index
		int iCurr_Point_Index = count % 12;

		// get target point
		mitsubishi_melfa::PositionCommand Point;
		Point = vecAllTargets.at(iCurr_Point_Index);

		// Publish
		ROS_INFO("Velocity: %f, Position: X: %f, Y: %f, Z: %f", Point.velocity_factor, Point.x, Point.y, Point.z );
		chatter_pub.publish(Point);

		// Call callbacks
		ros::spinOnce();

		// sleep
		loop_rate.sleep();
		++count;
	}


  return 0;
}
