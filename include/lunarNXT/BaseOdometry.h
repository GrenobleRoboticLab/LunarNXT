#ifndef BASEODOMETRY_H
#define BASEODOMETRY_H

#include "ros/ros.h"
#include "tf/transform_broadcaster.h"
#include "kdl/frames.hpp"
#include "sensor_msgs/JointState.h"
#include "nav_msgs/Odometry.h"
#include "nxt_msgs/Range.h"
#include "nxt_msgs/JointCommand.h"
#include "tf_conversions/tf_kdl.h"

#define PUBLISH_TF true

class BaseOdometry {
private:
	std::vector<float> leftPosition;
	std::vector<float> rightPosition;
	
	float rot_covar;
	
	bool initialized;
	KDL::Frame pose;
	
	tf::TransformBroadcaster br;

	ros::NodeHandle n;
	ros::Publisher publisher;
public:
	BaseOdometry();
	nav_msgs::Odometry update(const sensor_msgs::JointState::ConstPtr msg);
	
};

#endif
