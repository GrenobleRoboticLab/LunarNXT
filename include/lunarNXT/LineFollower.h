#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H

#include "lunarNXT/Mode.h"

#include "lunarNXT/Map.h"

#include "nxt_msgs/Color.h"
#include "nxt_msgs/Range.h"


class LineFollower : public Mode {
private:
	// Attributs
	nxt_msgs::Color colorMsg;
	nxt_msgs::Color colorLine;
	bool online;
	Map::Cardinal orientation;

	// traitement du mode
	void treat();	
	
public:
	// constructeurs et destructeur
	LineFollower();
	LineFollower(MoveMgr* mm);
	void updateColor(nxt_msgs::Color msg);
};

#endif
