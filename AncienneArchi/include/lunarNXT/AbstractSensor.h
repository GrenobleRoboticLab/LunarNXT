#ifndef ABSTRACTSENSOR_H
#define ABSTRACTSENSOR_H

#include "ros/ros.h"

class AbstractSensor {
protected:
	ros::Subscriber subscriber;
	std::string name;
};

#endif
