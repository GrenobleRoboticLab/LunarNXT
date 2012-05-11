#include "lunarNXT/LineFollower.h"
#include "lunarNXT/Tools.h"

// Constructeurs
LineFollower::LineFollower() : Mode() { }

LineFollower::LineFollower(MoveMgr* mm) : Mode(mm) {
	this->online = false;
	this->orientation = Map::WEST;

}

// Mise a jour du capteur de couleurs
void LineFollower::updateColor(nxt_msgs::Color msg) {
	this->colorMsg = msg;
	if (this->isInitialized()) {
		this->treat();
	}
	else if (this->isLaunched()) {
		this->colorLine.r = colorMsg.r;
		this->colorLine.g = colorMsg.g;
		this->colorLine.b = colorMsg.b;

		this->setInitialized(true);
		this->online = true;
	}
}

// Traitement du mode
void LineFollower::treat() {
	if(Tools::compare_color(&colorMsg, &colorLine)) {
		this->getMm()->stop();
		this->online = true;
		this->getMm()->linearMove(0.8);
	}
	else {
		switch(this->orientation) {
			case Map::WEST:
	                        if (this->online) {
        	                        this->getMm()->turn(0.72, 0.5);
                	                this->online = false;
                        	}
                        	if(!this->getMm()->hasGoalSet()) {
                       		        this->orientation = Map::EAST;
                        	        this->getMm()->turn(0.72, -1);
                        	}
				break;
			case Map::EAST:
                        	if (this->online) {
                       		        this->getMm()->turn(0.72, -0.5);
                        		this->online = false;
                        	}
                       		if(!this->getMm()->hasGoalSet()) {
                        	        this->orientation = Map::WEST;
                        		this->getMm()->turn(0.72, 1);
                        	}
				break;
			default: break;
		}
	}
}
