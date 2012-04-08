#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H

#include "lunarNXT/Mode.h"

#include "MoveMgr.h"

#include "nxt_msgs/Color.h"
#include "nxt_msgs/Range.h"


class LineFollower : public Mode {
private:
	// gestion des déplacements
	MoveMgr* mm;

	// Attributs
	nxt_msgs::Color colorMsg;
	float color[3];
	bool online;
	std::string direction;

	// traitement du mode
	void treat();	
	
public:
	// constructeurs et destructeur
	LineFollower();
	LineFollower(MoveMgr* mm);
	void updateColor(nxt_msgs::Color msg);
};

#endif
