#include "lunarNXT/TouchSensor.h"

using namespace std;

TouchSensor::TouchSensor(ros::NodeHandle n, string name) { 
	this->name = name;
	this->lastMsg = nxt_msgs::Contact();
	this->subscriber = n.subscribe(name, 5, &TouchSensor::touchCallback, this);
}

void TouchSensor::touchCallback(const nxt_msgs::Contact::ConstPtr& msg) { 
	this->lastMsg.contact = msg->contact; 
}

bool TouchSensor::getLastContact() { return this->lastMsg.contact; }
