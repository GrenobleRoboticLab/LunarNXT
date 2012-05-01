#include "lunarNXT/LineFinder.h"

LineFinder::LineFinder() : Mode() { ; }

LineFinder::LineFinder(MoveMgr* mm) : Mode(mm) {
	this->setInitialized(false);
	this->lineColor[0] = 0;
        this->lineColor[1] = 0;
        this->lineColor[2] = 0;
}

void LineFinder::updateColor(nxt_msgs::Color msg) {
	this->colorMsg = msg;
	if (this->isInitialized() && this->isLaunched())
		this->treat();
}

void LineFinder::treat() {
	bool online = (colorMsg.r == this->lineColor[0] &&
                       colorMsg.g == this->lineColor[1] &&
                       colorMsg.b == this->lineColor[2]);
	switch(this->checkCount) {
		case 0:
			if (!this->getMm()->hasGoalSet()) {
				if (this->started) {
					this->record(-1);
					this->started = false;
				}
				else {
					this->started = true;
					this->getMm()->linearMove(0.72, 3);
				}
			}
			else if (online && this->started) {
				this->started = false;
				this->record(1);
				this->getMm()->stop();
			}
			break;
		case 1:
			if (!this->getMm()->hasGoalSet()) {
				if (this->started) {
					this->record(-1);
					this->getMm()->turn(0.72, -1.7);
					this->started = false;	
				}
				else {
					this->getMm()->turn(0.72, 1.7);
					this->started = true;
				}
			}
			else if(online && this->started){
				this->started = false;
				this->getMm()->stop();
				this->record(1);
			}
			break;
		case 2:
                        if (!this->getMm()->hasGoalSet()) {
                                if (this->started) {
                                        this->record(-1);
                                        this->getMm()->turn(0.72, 1.7);
                                        this->started = false;
                                }
                                else {
                                        this->getMm()->turn(0.72, -1.7);
                                        this->started = true;
                                }
                        }
                        else if(online && this->started){
                                this->started = false;
                                this->getMm()->stop();
                                this->record(1);
                        }
                        break;
		default:
			this->unlaunch();
			break;
	}
}

void LineFinder::init(Map::Cardinal* orientation, Map::MapElement* cross) {
	this->orientation = orientation;
	this->cross = cross;
	this->checkCount = 0;
	this->started = false;
	this->setInitialized(true);
}

void LineFinder::record(int weight) {
	switch (*this->orientation) {
		case Map::NORD:
			break;
		case Map::SUD:
			break;
		case Map::EAST:
			break;
		case Map::WEST:
			break;
	}
	this->checkCount++;
}
