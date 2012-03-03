#include <ros/ros.h>
#include <stdio.h>

#include "lunarNXT/LunarNXT.h"

int main(int argc, char** argv) {
	ros::init(argc, argv, "lunarNXT");
	ros::NodeHandle n;

	LunarNXT lunar = LunarNXT(n);	
	
	ros::spin();
	
	return(0);
}

