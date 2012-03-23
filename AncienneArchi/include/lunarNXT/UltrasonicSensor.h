#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

#include "ros/ros.h"
#include "nxt_msgs/Range.h"
#include "AbstractSensor.h"

class UltrasonicSensor : public AbstractSensor {
private:
	nxt_msgs::Range lastMsg;
	void ultrasonicCallback(const nxt_msgs::Range::ConstPtr& msg);

public:
	
	UltrasonicSensor(ros::NodeHandle n, std::string name);
	float getLastRange();
	float getRangeMax();
	float getRangeMin();
	float getSpreadAngle();

};

#endif
