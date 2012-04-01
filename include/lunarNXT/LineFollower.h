#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H

#include "nxt_msgs/Color.h"
#include "nxt_msgs/Range.h"
#include "lunarNXT/MoveMgr.h"

class LineFollower {
private:
	MoveMgr* mm;
	bool launched;
	bool initialized;
	float color[3];
	bool online;
	std::string direction;
	
	
public:
	LineFollower();
	LineFollower(MoveMgr* mm);
	void updateColor(nxt_msgs::Color colorMsg);
	void launch();
	void unlaunch();
	void treat(nxt_msgs::Color colorMsg);
};

#endif
