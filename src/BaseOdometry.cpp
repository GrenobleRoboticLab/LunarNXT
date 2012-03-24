#include "lunarNXT/BaseOdometry.h"

#define RADIUS 0.022
#define WHEELBASICS 7.5


BaseOdometry::BaseOdometry() {
	this->leftPosition = std::vector<float>();
	this->rightPosition = std::vector<float>();
	this->publisher = n.advertise<nav_msgs::Odometry>("odom", 5);
	this->initialized = false;
}

nav_msgs::Odometry BaseOdometry::update(sensor_msgs::JointState msg) {
	std::vector<float> leftPos = std::vector<float>();
	std::vector<float> rightPos = std::vector<float>();
	
	for (unsigned int i = 0; i < msg.position.size(); i++) {
		if (msg.name.at(i) == "motor_l")
			leftPos.push_back(msg.position.at(i));
		else if (msg.name.at(i) == "motor_r")
			leftPos.push_back(msg.position.at(i));
	}
	
	if (!this->initialized) {
		this->leftPosition = leftPos;
		this->rightPosition = rightPos;
		this->pose = KDL::Frame();
		this->initialized = true;
	}
	else {
		float delta_l_pos;
		for (unsigned int i = 0; i < leftPos.size(); i++) delta_l_pos += leftPos.at(i);
		for (unsigned int i = 0; i < this->leftPosition.size(); i++) delta_l_pos -= this->leftPosition.at(i);
		
		float delta_r_pos;
		for (unsigned int i = 0; i < rightPos.size(); i++) delta_r_pos += rightPos.at(i);
		for (unsigned int i = 0; i < this->rightPosition.size(); i++) delta_r_pos -= this->rightPosition.at(i);
		
		float delta_trans = (delta_l_pos + delta_r_pos) * RADIUS / 2.0;
		float delta_rot   = (delta_r_pos - delta_l_pos)* RADIUS /(2.0 * WHEELBASICS);
		
		ROS_INFO("DELTA ROTATION = %f", delta_rot);
		ROS_INFO("DELTA TRANSLATION = %f", delta_trans);

		KDL::Twist twist = KDL::Twist(KDL::Vector(delta_trans, 0, 0), KDL::Vector(0, 0, delta_rot));
		this->leftPosition = leftPos;
		this->rightPosition = rightPos;
		this->pose = KDL::addDelta(this->pose, this->pose.M  * twist);

		this->rot_covar = 1.0;
		if (delta_rot == 0) this->rot_covar = 0.00000000001;

		nav_msgs::Odometry odom = nav_msgs::Odometry();
		odom.header.stamp = ros::Time::now();
		tf::PoseKDLToMsg(this->pose, odom.pose.pose);
		boost::array<float, 36> covar = {0.00001, 0, 0, 0, 0, 0, 0, 0.00001, 0, 0, 0, 0, 0, 0, 10.0000, 0, 0, 0, 0, 0, 0, 1.00000, 0, 0, 0, 0, 0, 0, 1.00000, 0, 0, 0, 0, 0, 0, this->rot_covar};
		odom.pose.covariance = covar;
		this->publisher.publish(odom);
		return odom;
	}
	return nav_msgs::Odometry();
}
