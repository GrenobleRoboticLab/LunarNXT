#include "lunarNXT/LineFollower.h"


LineFollower::LineFollower() { }

LineFollower::LineFollower(MoveMgr* mm) {
	this->mm = mm;
	this->launched = false;
	this->initialized = false;
	this->online = false;
	this->direction = "left";
}

void LineFollower::updateColor(nxt_msgs::Color colorMsg) {
	if (this->initialized == true) {
		this->treat(colorMsg);
	}
	else if (this->launched == true) {
		this->color[0] = (bool)colorMsg.r;
		this->color[1] = (bool)colorMsg.g;
		this->color[2] = (bool)colorMsg.b;

		this->initialized = true;
		this->online = true;
	}
}

void LineFollower::launch() {
	this->launched = true;
	this->initialized = false;
}

void LineFollower::unlaunch() {
	this->launched = false;
	this->initialized = false;
	this->mm->stop();
}

void LineFollower::treat(nxt_msgs::Color colorMsg) {

	if ((bool)colorMsg.r == this->color[0] && 
	(bool)colorMsg.g == this->color[1] && 
	(bool)colorMsg.b == this->color[2]) {
		this->mm->stop();
		this->online = true;
		this->mm->linearMove(0.8);
	}
	else {
		if (this->direction == "left") {
			if (this->online) {
				this->mm->turn(0.8, 0.5);
				this->online = false;
			}
			if (!this->mm->hasGoalSet()) {
				this->direction = "right";
				this->mm->turn(0.8, -1);
			}
		}
		else if (this->direction == "right") {
			if (this->online) {
				this->mm->turn(0.8, -0.5);
				this->online = false;
			}
			if (!this->mm->hasGoalSet()) {
				this->direction = "left";
				this->mm->turn(0.8, 1);
			}
		}
	}
}
