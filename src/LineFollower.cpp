#include "lunarNXT/LineFollower.h"


LineFollower::LineFollower() : Mode(NULL) { }

LineFollower::LineFollower(MoveMgr* mm) : Mode(mm) {
	this->online = false;
	this->direction = "left";
}

void LineFollower::updateColor(nxt_msgs::Color msg) {
	this->colorMsg = msg;
	if (this->isInitialized()) {
		this->treat();
	}
	else if (this->isLaunched()) {
		this->color[0] = colorMsg.r;
		this->color[1] = colorMsg.g;
		this->color[2] = colorMsg.b;

		this->setInitialized(true);
		this->online = true;
	}
}

void LineFollower::treat() {

	if(colorMsg.r == this->color[0] && 
	colorMsg.g == this->color[1] && 
	colorMsg.b == this->color[2]) {
		this->mm->stop();
		this->online = true;
		this->mm->linearMove(0.8);
	}
	else {
		if(this->direction == "left") {
			if (this->online) {
				this->mm->turn(0.8, 0.5);
				this->online = false;
			}
			if(!this->mm->hasGoalSet()) {
				this->direction = "right";
				this->mm->turn(0.8, -1);
				if(!this->mm->hasGoalSet()) {
					this->unlaunch();
				}
			}
		}
		else if(this->direction == "right") {
			if (this->online) {
				this->mm->turn(0.8, -0.5);
				this->online = false;
			}
			if(!this->mm->hasGoalSet()) {
				this->direction = "left";
				this->mm->turn(0.8, 1);
				if(!this->mm->hasGoalSet()) {
					this->unlaunch();
				}
			}
		}
	}
}
