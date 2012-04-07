#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H

#include "lunarNXT/Mode.h"
#include "lunarNXT/Receptor.h"

#include "MoveMgr.h"

#include "nxt_msgs/Color.h"
#include "nxt_msgs/Range.h"


class LineFollower : public Receptor, public Mode {
private:
	MoveMgr* mm;
<<<<<<< HEAD
	nxt_msgs::Color colorMsg;
=======
	bool launched;
	bool initialized;
>>>>>>> 2763f47c71e47f6b89cf23bd0e840426f517ab8f
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
