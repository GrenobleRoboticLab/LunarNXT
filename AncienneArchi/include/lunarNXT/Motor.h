#ifndef MOTOR_H
#define MOTOR_H

#include "ros/ros.h"
#include "lunarNXT/AbstractSensor.h"
#include "nxt_msgs/JointCommand.h"
#include "sensor_msgs/JointState.h"

class Motor : public AbstractSensor {
private:
	sensor_msgs::JointState lastMsg;
	ros::Publisher publisher;
	void motorCallback(const sensor_msgs::JointState::ConstPtr& msg);
	bool hasOrder;
	float endPos;

public:
	Motor(ros::NodeHandle n, std::string name);
	
	void motorManager(float effort);
	
	void giveOrder(float effort, float endPos);
	sensor_msgs::JointState getLastMsg();
	float getLastPos();
	float getLastVel();
	float getLastEffort();
};

#endif
