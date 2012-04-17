#include "lunarNXT/LineFollower.h"

// Constructeurs
LineFollower::LineFollower() : Mode() { }

LineFollower::LineFollower(MoveMgr* mm) : Mode(mm) {
	this->online = false;
	this->direction = "left";

}

// Mise a jour du capteur de couleurs
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

// Traitement du mode
void LineFollower::treat() {
	if(colorMsg.r == this->color[0] && 
		colorMsg.g == this->color[1] && 
		colorMsg.b == this->color[2]) 
	{
		this->getMm()->stop();
		this->online = true;
		this->getMm()->linearMove(0.8);
	}
	else {
		if(this->direction == "left") {
			if (this->online) {
				this->getMm()->turn(0.72, 0.5);
				this->online = false;	
			}
			if(!this->getMm()->hasGoalSet()) {
				this->direction = "right";
				this->getMm()->turn(0.72, -1);
			}
		}
		else if(this->direction == "right") {
			if (this->online) {
				this->getMm()->turn(0.72, -0.5);
				this->online = false;
			}
			if(!this->getMm()->hasGoalSet()) {
				this->direction = "left";
				this->getMm()->turn(0.72, 1);	
			}
		}
	}
}
