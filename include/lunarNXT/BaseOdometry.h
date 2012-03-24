#ifndef BASEODOMETRY_H
#define BASEODOMETRY_H

#include "ros/ros.h"
#include "kdl/frames.hpp"
#include "sensor_msgs/JointState.h"
#include "nav_msgs/Odometry.h"
#include "nxt_msgs/Range.h"
#include "nxt_msgs/JointCommand.h"
#include "tf_conversions/tf_kdl.h"

class BaseOdometry {
private:
	std::vector<float> leftPosition;
	std::vector<float> rightPosition;
	
	float rot_covar;
	
	bool initialized;
	KDL::Frame pose;
	
	ros::NodeHandle n;
	ros::Publisher publisher;
public:
	BaseOdometry();
	nav_msgs::Odometry update(sensor_msgs::JointState msg);
	
};

#endif
