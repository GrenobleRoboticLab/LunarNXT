#include "lunarNXT/Navigator.h"
#include "lunarNXT/Tools.h"

#define TURN_RATIO 2 
#define PASTILLE_SIZE 2

using namespace Lunar_lib;

Navigator::Navigator() : Mode() { ; }
Navigator::Navigator(MoveMgr* mm, LineFollower* lfo) : Mode(mm) { 
	this->lfo = lfo;
	this->online = false;
}

void Navigator::treat() {
	if (Tools::is_pastille_color(colorMsg))
		this->applyChoice();
	else {
		if (this->online)
			this->lfo->updateColor(this->colorMsg);
		else if (!this->getMm()->hasGoalSet()) 
			this->startLineFollower();
	}
}

void Navigator::init(std::list<Map::Choice> choices) { 
	this->choices = choices; 
	this->setInitialized(true);
}

void Navigator::updateColor(nxt_msgs::Color msg) { 
	if (this->isLaunched() && this->isInitialized()) {
		this->colorMsg = msg;
		this->treat();
	}
}

void Navigator::startLineFollower() { 
	this->lfo->launch();
	this->online = true;
}

void Navigator::stopLineFollower() {
	this->lfo->unlaunch();
	this->online = false;
}

void Navigator::applyChoice() {
	if (checkDist(this->getMm()->getLeftPos(), this->getMm()->getRightPos())) {
		if (this->online)
			this->stopLineFollower();
		if (this->choices.size() <= 0)
			this->unlaunch();
		else {
			Map::Choice choice = this->choices.front();
	        	this->choices.pop_front();

			switch (choice) {
	       			case Map::AHEAD:
	        			this->getMm()->linearMove(BASE_EFFORT, PASTILLE_SIZE);
					break;
				case Map::BACK:
					this->getMm()->turnAround(BASE_EFFORT, 3*MPI);
					break;
				default:
					this->getMm()->turnAround(BASE_EFFORT+0.05, (choice * TURN_RATIO));
					this->lfo->setOrientation((Map::Cardinal)(choice + 2));
					break;
			}

			this->leftPos = this->getMm()->getLeftPos();
			this->rightPos = this->getMm()->getRightPos();
		}
	}
}

bool Navigator::checkDist(float a, float b) {
	if ((a - this->leftPos) > MPI 
	 || (b - this->rightPos) > MPI
	 || (a - this->leftPos) < -MPI
	 || (b - this->rightPos) < -MPI)
		return true;
	return false;
}
