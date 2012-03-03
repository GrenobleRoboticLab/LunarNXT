#ifndef MOVEMANAGER_H
#define MOVEMANAGER_H

#include "lunarNXT/Motor.h"

using namespace std;

class MoveManager {
private:
	Motor* leftMotor;
	Motor* rightMotor;

public:
	MoveManager(Motor* leftMotor, Motor* rightMotor);
	void linearMove(float effort);
	void turnLeft(float effort);
	void turnRight(float effort);
	void boostLeft(float effort);
	void boostRight(float effort);
	void effortDispatcher(float leftEffort, float rightEffort);
};

#endif
