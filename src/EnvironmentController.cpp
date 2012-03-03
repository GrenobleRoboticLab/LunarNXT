#include "lunarNXT/EnvironmentController.h"
#include "nxt_msgs/JointCommand.h"


EnvironmentController::EnvironmentController(TouchSensor* leftTS, TouchSensor* rightTS, UltrasonicSensor* ultrasonicS, ColorSensor* colorS, Motor* colorMotor) { 
	this->leftTouchS = leftTS;
	this->rightTouchS = rightTS;
	this->ultrasonicS = ultrasonicS;
	this->colorS = colorS;
	this->colorMotor = colorMotor;
	this->colorVertical =true;
}

bool EnvironmentController::faceSomething() {
	float range = this->ultrasonicS->getLastRange();
	if(range <= WALLDISTANCE)
		return true;
	return false;
}

bool EnvironmentController::touchSomething() {
	if(this->leftTouchS->getLastContact() || this->rightTouchS->getLastContact())
		return true;	
	return false;
}

float EnvironmentController::distanceToSomething() {
	return this->ultrasonicS->getLastRange();
}

void EnvironmentController::rotateColorSensor(){
	if(colorVertical){
		this->colorMotor->motorManager(0.7);
		ros::Duration turn(1.0);
		turn.sleep();
		this->colorMotor->motorManager(0);
		colorVertical = false;
	}
	else{
		this->colorMotor->motorManager(-0.7);
		ros::Duration turn(1.0);
		turn.sleep();
		this->colorMotor->motorManager(0);
		colorVertical = true;
	}
}

nxt_msgs::Color EnvironmentController::getColor(){
	nxt_msgs::Color color = nxt_msgs::Color();
	color.intensity = this->colorS->getIntensity();
	color.r = this->colorS->getRed();
	color.g = this->colorS->getGreen();
	color.b = this->colorS->getBlue();

	return color;
}


