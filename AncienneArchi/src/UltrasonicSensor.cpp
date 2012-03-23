#include "lunarNXT/UltrasonicSensor.h"

#include <iostream>
#include <fstream>


UltrasonicSensor::UltrasonicSensor(ros::NodeHandle n, std::string name) {
	this->name = name;
	this->lastMsg = nxt_msgs::Range();
	this->subscriber = n.subscribe(name, 5, &UltrasonicSensor::ultrasonicCallback, this);
}

void UltrasonicSensor::ultrasonicCallback (const nxt_msgs::Range::ConstPtr& msg) {
	this->lastMsg.range = msg->range;
	this->lastMsg.range_max = msg->range_max;
	this->lastMsg.range_min = msg->range_min;
	this->lastMsg.spread_angle = msg->spread_angle;
}

float UltrasonicSensor::getLastRange() { 	return this->lastMsg.range; }
float UltrasonicSensor::getRangeMax() { 	return this->lastMsg.range_max; }
float UltrasonicSensor::getRangeMin() { 	return this->lastMsg.range_min; }
float UltrasonicSensor::getSpreadAngle() { 	return this->lastMsg.spread_angle; }

