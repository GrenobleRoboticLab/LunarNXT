#ifndef TOUCHSENSOR_H
#define TOUCHSENSOR_H

#include "lunarNXT/AbstractSensor.h"
#include "nxt_msgs/Contact.h"

using namespace std;

class TouchSensor : public AbstractSensor {
private:
	nxt_msgs::Contact lastMsg;
	void touchCallback(const nxt_msgs::Contact::ConstPtr& msg);

public:
	TouchSensor(ros::NodeHandle n,string name);
	bool getLastContact();
};

#endif
