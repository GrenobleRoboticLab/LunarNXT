#ifndef ENVANALYSER_H
#define ENVANALYSER_H

#include "sensor_msgs/JointState.h"
#include "nxt_msgs/Contact.h"
#include "nxt_msgs/Color.h"
#include "nxt_msgs/Range.h"
#include "lunarNXT/Order.h"

#include "lunarNXT/MoveMgr.h"
#include "lunarNXT/Mode.h"
#include "lunarNXT/BaseOdometry.h"


class EnvAnalyser {
private:
	MoveMgr* mm;
	Mode* mode;
	BaseOdometry bo;

public:
	EnvAnalyser();
	EnvAnalyser(MoveMgr* mm);
	~EnvAnalyser();

	void motorCallback(const sensor_msgs::JointState::ConstPtr& msg);
	void rightTouchCallback(const nxt_msgs::Contact::ConstPtr& msg);
	void leftTouchCallback(const nxt_msgs::Contact::ConstPtr& msg);
	void colorCallback(const nxt_msgs::Color::ConstPtr& msg);
	void ultrasonicCallback(const nxt_msgs::Range::ConstPtr& msg);
	void uiCallback(const lunarNXT::Order::ConstPtr& msg);
};

#endif
