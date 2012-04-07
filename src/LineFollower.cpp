#include "lunarNXT/LineFollower.h"


LineFollower::LineFollower() { }

LineFollower::LineFollower(MoveMgr* mm) :
				Receptor(mm->getNameLeftMotor(), mm->getNameRightMotor()),
				Mode(mm)
{
	this->online = false;
	this->direction = "left";
}

void LineFollower::updateColor(nxt_msgs::Color msg) {
	this->colorMsg = msg;
	if (this->isInitialized()) {
		this->treat();
	}
<<<<<<< HEAD
	else if (this->isLaunched()) {
=======
	else if (this->launched == true) {
>>>>>>> 2763f47c71e47f6b89cf23bd0e840426f517ab8f
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
			if (this->online == true) {
				this->mm->turn(0.8, 0.5);
				this->online = false;
			}
			if(!this->mm->hasGoalSet()) {
				this->direction = "right";
				this->mm->turn(0.8, -1);
				if(this->mm->hasGoalSet() == false) {
					this->unlaunch();
				}
			}
		}
		else if(this->direction == "right") {
			if (this->online == true) {
				this->mm->turn(0.8, -0.5);
				this->online = false;
			}
			if(!this->mm->hasGoalSet()) {
				this->direction = "left";
				this->mm->turn(0.8, 1);
				if(this->mm->hasGoalSet() == false) {
					this->unlaunch();
				}
			}
		}
	}
}
