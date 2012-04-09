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

	// Constructeurs & destructeur
	Receptor();
	Receptor(std::string nameLeftMotor, std::string nameRightMotor);
	virtual ~Receptor();

	// Touch sensor updaters
	virtual void updateRightTouch(const nxt_msgs::Contact::ConstPtr msg);
	virtual void updateLeftTouch(const nxt_msgs::Contact::ConstPtr msg);

	// Range sensor updater
	virtual void updateRange(const nxt_msgs::Range::ConstPtr msg);

	// Color sensor updater
	virtual void updateColor(const nxt_msgs::Color::ConstPtr msg);

	// Motors updater
	virtual void updateMotors(const sensor_msgs::JointState::ConstPtr msg);
};

#endif
