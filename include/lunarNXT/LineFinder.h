#ifndef LINEFINDER_H
#define LINEFINDER_H

#include "lunarNXT/Mode.h"
#include "lunarNXT/Map.h"

#include "nxt_msgs/Color.h"


class LineFinder : public Mode {
private:
	// Attributs
	nxt_msgs::Color colorMsg;
	float lineColor[3];
	bool online;
	Map::Cardinal* orientation;

	// traitement du mode
	void treat();	
	
public:
	// constructeurs et destructeur
	LineFinder();
	LineFinder(MoveMgr* mm, Map::Cardinal* orientation);
	void updateColor(nxt_msgs::Color msg);
};

#endif
