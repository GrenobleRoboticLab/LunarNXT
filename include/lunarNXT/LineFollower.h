#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H

#include "lunarNXT/Mode.h"

#include "MoveMgr.h"

#include "nxt_msgs/Color.h"
#include "nxt_msgs/Range.h"


class LineFollower : public Mode {
private:
	MoveMgr* mm;

	nxt_msgs::Color colorMsg;
	float color[3];
	bool online;
	std::string direction;

	void treat();	
	
public:
	LineFollower();
	LineFollower(MoveMgr* mm);
	void updateColor(nxt_msgs::Color msg);
};

#endif
