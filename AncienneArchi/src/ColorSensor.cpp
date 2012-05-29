#include "lunarNXT/ColorSensor.h"

ColorSensor::ColorSensor(ros::NodeHandle n, std::string name) {
	this->name = name;
	this->subscriber = n.subscribe(name, 5, &ColorSensor::colorCallback, this);
	this->lastMsg = nxt_msgs::Color();
}

void ColorSensor::colorCallback(const nxt_msgs::Color::ConstPtr& msg) {
	this->lastMsg.intensity = msg->intensity;
	this->lastMsg.r = msg->r;
	this->lastMsg.g = msg->g;
	this->lastMsg.b = msg->b;
}

float ColorSensor::getIntensity() { return this->lastMsg.intensity; }
float ColorSensor::getRed() { 		return this->lastMsg.r; }
float ColorSensor::getGreen() { 	return this->lastMsg.g; }
float ColorSensor::getBlue() { 		return this->lastMsg.b; }
