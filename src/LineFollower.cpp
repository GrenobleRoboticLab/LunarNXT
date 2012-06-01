#include "lunarNXT/LineFollower.h"
#include "lunarNXT/Tools.h"

using namespace Lunar_lib;

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
		this->count = 0;
		this->setInitialized(true);
		this->online = true;
	}
}

// Traitement du mode
void LineFollower::treat() {
	if(Tools::is_line_color(this->colorMsg)) {
		this->getMm()->stop();
		this->online = true;
		this->getMm()->linearMove(0.8);
	}
	else {
		if (this->online) {
        		this->getMm()->turn(BASE_EFFORT, ((this->orientation-2)*0.4));
                        this->count++;
                	this->online = false;
		}
                else if(!this->getMm()->hasGoalSet()) {
                        this->getMm()->turn(BASE_EFFORT, -(this->orientation-2)*0.8);
			this->count++;
			this->orientation = (Map::Cardinal)((this->orientation+2)%4);
		}
		if (count > 2) {
			this->getMm()->linearMove(BASE_EFFORT, 1);
			this->count = 0;
		}
	}
}

void LineFollower::setOrientation(Map::Cardinal orientation) { this->orientation = orientation; }
