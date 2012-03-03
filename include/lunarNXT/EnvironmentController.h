#ifndef ENVIRONMENTCONTROLLER_H
#define ENVIRONMENTCONTROLLER_H

#include "lunarNXT/TouchSensor.h"
#include "lunarNXT/UltrasonicSensor.h"
#include "lunarNXT/ColorSensor.h"
#include "lunarNXT/Motor.h"

#define WALLDISTANCE 0.5

using namespace std;

class EnvironmentController {
private:
	TouchSensor* leftTouchS;
	TouchSensor* rightTouchS;
	UltrasonicSensor* ultrasonicS;
	ColorSensor* colorS;
	Motor* colorMotor;
	bool colorVertical;

public:
	EnvironmentController(TouchSensor* leftTouchS, TouchSensor* rightTouchS, UltrasonicSensor* ultrasonicS, ColorSensor* colorS, Motor* colorMotor);
	bool faceSomething();
	bool touchSomething();
	float distanceToSomething();
	void rotateColorSensor();
	nxt_msgs::Color getColor();
};

#endif
