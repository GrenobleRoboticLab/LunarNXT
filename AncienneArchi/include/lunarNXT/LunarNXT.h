#ifndef LUNARNXT_H
#define LUNARNXT_H

#include "lunarNXT/Order.h"
#include "lunarNXT/Motor.h"
#include "lunarNXT/TouchSensor.h"
#include "lunarNXT/UltrasonicSensor.h"
#include "lunarNXT/MoveManager.h"
#include "lunarNXT/EnvironmentController.h"
#include "ros/ros.h"

class LunarNXT {
private:
	ros::Subscriber subscriber;
	MoveManager* mm;
	EnvironmentController* ec;

	void receiveAction(const lunarNXT::Order::ConstPtr& msg);
	
	void goAhead();
	void goBack();
	void stop();
	void turnLeft();
	void turnRight();
	void boostLeft();
	void boostRight();
	void test();


public:
	enum Actions {
		GoAhead,
		GoBack,
		Stop,
		TurnRight,
		TurnLeft,
		BoostRight,
		BoostLeft,
		Test  	
	};
	
	LunarNXT(ros::NodeHandle n);

};

#endif
