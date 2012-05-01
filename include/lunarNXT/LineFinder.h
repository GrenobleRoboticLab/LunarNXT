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

	bool started;
	int checkCount;

	Map::Cardinal* orientation;
	Map::MapElement* cross;
	// traitement du mode
	
	void treat();	
	void record(int weight);	
public:
	// constructeurs et destructeur
	LineFinder();
	LineFinder(MoveMgr* mm);
	void updateColor(nxt_msgs::Color msg);
	void init(Map::Cardinal* orientation, Map::MapElement* cross);
};

#endif
