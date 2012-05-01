#ifndef LINEFINDER_H
#define LINEFINDER_H

#include "lunarNXT/Mode.h"
#include "lunarNXT/Map.h"

#include "nxt_msgs/Color.h"


class LineFinder : public Mode {
private:
	void treat();
public:
	// constructeurs et destructeur
	LineFinder();
	LineFinder(MoveMgr* mm);

};

#endif
