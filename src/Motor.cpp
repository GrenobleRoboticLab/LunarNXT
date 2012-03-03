#include "lunarNXT/Motor.h"

Motor::Motor(ros::NodeHandle n, std::string name){
	this->name = name;
	this->publisher = n.advertise<nxt_msgs::JointCommand>("joint_command", 5);
	this->subscriber = n.subscribe("joint_state", 15, &Motor::motorCallback, this);
	this->lastMsg = sensor_msgs::JointState();		
}

void Motor::motorCallback(const sensor_msgs::JointState::ConstPtr& msg) {
	if (msg->name.back() == this->name) {
		this->lastMsg.name.push_back(msg->name.back());
		this->lastMsg.position.push_back(msg->position.back());
		this->lastMsg.velocity.push_back(msg->velocity.back());
		this->lastMsg.effort.push_back(msg->effort.back());
	}
}

void Motor::motorManager(float effort) {
	nxt_msgs::JointCommand jc = nxt_msgs::JointCommand();
	jc.name = this->name;
	jc.effort = effort;
	this->publisher.publish(jc);
}

sensor_msgs::JointState Motor::getLastMsg() { return this->lastMsg; }

float Motor::getLastPos() { 	return this->lastMsg.position.back(); }
float Motor::getLastVel() { 	return this->lastMsg.velocity.back(); }
float Motor::getLastEffort() { 	return this->lastMsg.effort.back(); }
