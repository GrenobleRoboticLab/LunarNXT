#ifndef COLORSENSOR_H
#define COLORSENSOR_H

#include "lunarNXT/AbstractSensor.h"
#include "nxt_msgs/Color.h"

class ColorSensor : public AbstractSensor {
private:
	void colorCallback(const nxt_msgs::Color::ConstPtr& msg);
	nxt_msgs::Color lastMsg;

public:
	ColorSensor(ros::NodeHandle n, std::string name);

	float getIntensity();
	float getRed();
	float getGreen();
	float getBlue();
};

#endif
