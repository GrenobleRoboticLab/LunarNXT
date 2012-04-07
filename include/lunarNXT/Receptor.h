#ifndef RECEPTOR_H
#define RECEPTOR_H

#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "nxt_msgs/Color.h"
#include "nxt_msgs/Range.h"
#include "nxt_msgs/Contact.h"


class Receptor {
private:
	// Motors name
	std::string nameLeftMotor;
	std::string nameRightMotor;

public:
	// getters
	std::string getNameLeftMotor();
	std::string getNameRightMotor();

	Receptor();
	Receptor(std::string nameLeftMotor, std::string nameRightMotor);
	virtual ~Receptor();

	// Touch sensor updaters
	virtual void updateRightTouch(nxt_msgs::Contact msg);
	virtual void updateLeftTouch(nxt_msgs::Contact msg);

	// Range sensor updater
	virtual void updateRange(nxt_msgs::Range msg);

	// Color sensor updater
	virtual void updateColor(nxt_msgs::Color msg);

	// Motors updater
	virtual void updateMotors(sensor_msgs::JointState msg);
};

#endif
