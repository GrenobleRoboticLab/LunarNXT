#include "lunarNXT/MoveManager.h"
#include "nxt_msgs/JointCommand.h"

MoveManager::MoveManager(Motor* leftMotor, Motor* rightMotor) { 
	this->leftMotor = leftMotor;
	this->rightMotor = rightMotor;
}

void MoveManager::linearMove(float effort) {
	this->effortDispatcher(effort, effort);
}

void MoveManager::turnLeft(float effort) {  
	this->effortDispatcher(-effort, effort);
}

void MoveManager::turnRight(float effort) {   
	this->effortDispatcher(effort, -effort);
}

void MoveManager::boostLeft(float effort) {
	float leftEffort = this->leftMotor->getLastEffort() + effort;
	float rightEffort = this->rightMotor->getLastEffort();
	
	this->effortDispatcher(leftEffort, rightEffort);
}

void MoveManager::boostRight(float effort) {  
	float leftEffort = this->leftMotor->getLastEffort();
	float rightEffort = this->rightMotor->getLastEffort() + effort;
	
	this->effortDispatcher(leftEffort, rightEffort);
}

void MoveManager::effortDispatcher(float leftEffort, float rightEffort) {
	this->leftMotor->motorManager(leftEffort);
	this->rightMotor->motorManager(rightEffort);
}
