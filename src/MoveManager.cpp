#include "lunarNXT/MoveManager.h"
#include "nxt_msgs/JointCommand.h"

#define PI 3.14
#define R 1.5

MoveManager::MoveManager(Motor* leftMotor, Motor* rightMotor) { 
	this->leftMotor = leftMotor;
	this->rightMotor = rightMotor;
}

void MoveManager::linearMove(float effort) {
	this->effortDispatcher(effort, effort);
}

void MoveManager::linearMove(float effort, int cm) {
	float P = 2 * PI * R;
	float rate = P / cm;
	
	float endPosLeft, endPosRight;
	
	if (effort > 0) {
		endPosLeft = this->leftMotor->getLastPos() + (360 * rate);
		endPosRight = this->rightMotor->getLastPos() + (360 * rate);
	}
	else {
		endPosLeft = this->leftMotor->getLastPos() - (360 * rate);
		endPosRight = this->rightMotor->getLastPos() - (360 * rate);	
	}
	
	this->leftMotor->giveOrder(effort, endPosLeft);
	this->rightMotor->giveOrder(effort, endPosRight);
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
