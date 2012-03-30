#include "lunarNXT/LineFollower.h"


LineFollower::LineFollower() { }

LineFollower::LineFollower(MoveMgr* mm) {
	this->mm = mm;
	this->initialyzed = false;
	this->launched = false;
}

void LineFollower::updateColor(nxt_msgs::Color colorMsg) {
	if(this->launched) {
		if (this->initialyzed)
			this->treat(colorMsg);
		else {
			this->colorTracked = nxt_msgs::Color(colorMsg);
			this->initialyzed = true;
		}
	}
}

void LineFollower::launch() {
	this->launched = true;
}

void LineFollower::unLaunch() {
	this->launched = false;
	this->initialyzed = false;
}

void LineFollower::treat(nxt_msgs::Color color) {
	if (color.r == this->colorTracked.r && 
	    color.g == this->colorTracked.g && 
	    color.b == this->colorTracked.b)
		this->mm->linearMove(0.8, 0.1);
	else
		this->mm->turn(0.8, -0.8);
}

bool LineFollower::isLaunch() { return this->launched; }
