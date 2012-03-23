#include "lunarNXT/MoveMgr.h"
#include "nxt_msgs/JointCommand.h"

#define MINRANGE 0.2
#define PI 3.14159265

MoveMgr::MoveMgr() { }

MoveMgr::MoveMgr(ros::Publisher publisher, std::string leftName, std::string rightName) {
	this->publisher = publisher;
	this->leftName = leftName;
	this->rightName = rightName;
	this->hasGoal = false;
}

void MoveMgr::linearMove(float effort) {
	this->publish(effort, effort);
}

void MoveMgr::turnLeft(float effort) {
	this->publish(-effort, effort);
}

void MoveMgr::turnRight(float effort) {
	this->publish(effort, -effort);
}

void MoveMgr::linearMove(float effort, int cm) {
	// TODO: avancer en cm => regarder https://nxt.foote-ros-pkg.googlecode.com/hg/nxt/nxt_controllers/scripts/base_controller.py
}

void MoveMgr::turn(float effort, float rad) {
	// TODO: cf linearMove
}

void MoveMgr::updateLeft(float position, float effort) {
	this->leftPosition = position;
	this->leftEffort = effort;
}

void MoveMgr::updateRight(float position, float effort) {
	this->rightPosition = position;
	this->rightEffort = effort;
}

void MoveMgr::updateRange(float range) {
	if (range < MINRANGE) this->publish(0, 0);
}

void MoveMgr::publish(float leftEffort, float rightEffort) {
	nxt_msgs::JointCommand leftCommand = nxt_msgs::JointCommand();
	nxt_msgs::JointCommand rightCommand = nxt_msgs::JointCommand();
	
	leftCommand.name = this->leftName;
	leftCommand.effort = leftEffort;

	rightCommand.name = this->rightName;
	rightCommand.effort = rightEffort;

	this->publisher.publish(leftCommand);
	this->publisher.publish(rightCommand);
}
