#include "lunarNXT/MoveMgr.h"
#include "nxt_msgs/JointCommand.h"

#define MINRANGE 0.2
#define PI 3.14159265
#define WHEEL_RADIUS 7.5

MoveMgr::MoveMgr() { }

MoveMgr::MoveMgr(ros::Publisher publisher, std::string leftName, std::string rightName) {
	this->publisher = publisher;
	this->leftName = leftName;
	this->rightName = rightName;
	this->hasGoal = false;
}

MoveMgr::~MoveMgr() {
	this->publish(0, 0);	
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
	this->hasGoal = true;
	this->desiredLeftPosition = this->leftPosition + cm;
	this->desiredRightPosition = this->rightPosition + cm;
	
	if (cm >= 0) this->publish(effort, effort);
	else this->publish(-effort, -effort);
}

void MoveMgr::turn(float effort, float rad) {
	this->hasGoal = true;
	float distance_to_reach = rad * WHEEL_RADIUS;
	this->desiredRightPosition = this->rightPosition + distance_to_reach;
	this->desiredLeftPosition = this->leftPosition - distance_to_reach;
	
	if (rad >= 0) this->publish(-effort, effort);	
	else this->publish(effort, -effort);
}

void MoveMgr::updateLeft(float position, float effort) {
	this->leftPosition = position;
	this->leftEffort = effort;
	this->checkGoal();
}

void MoveMgr::updateRight(float position, float effort) {
	this->rightPosition = position;
	this->rightEffort = effort;
	this->checkGoal();
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

void MoveMgr::checkGoal() {
	if (this->hasGoal) {
		if (this->leftEffort > 0) {
			if (this->desiredLeftPosition <= this->leftPosition) 
				this->leftEffort = 0;
		}
		else if (this->leftEffort < 0) {
                        if (this->desiredLeftPosition >= this->leftPosition)
                                this->leftEffort = 0;
		}
                
		if (this->rightEffort > 0) {
                        if (this->desiredRightPosition <= this->rightPosition)
                                this->rightEffort = 0;
                }
		else if (this->rightEffort < 0) {
                        if (this->desiredRightPosition >= this->rightPosition) 
                                this->rightEffort = 0;
		}

		this->publish(this->leftEffort, this->rightEffort);
		if (this->leftEffort == 0 && this->rightEffort == 0) this->hasGoal = false;
	}
}
