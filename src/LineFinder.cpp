#include "lunarNXT/LineFinder.h"

LineFinder::LineFinder() : Mode() { ; }

LineFinder::LineFinder(MoveMgr* mm, Map::Cardinal* orientation) : Mode(mm) {
	this->orientation = orientation;
}

void LineFinder::updateColor(nxt_msgs::Color msg) {
	this->colorMsg = msg;
	this->treat();
}

void LineFinder::treat() {
	;
}
