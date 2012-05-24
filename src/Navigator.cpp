#include "lunarNXT/Navigator.h"
#include "lunarNXT/Tools.h"

#define TURN_RATIO 0.4
#define PASTILLE_SIZE 2

Navigator::Navigator() : Mode() { ; }
Navigator::Navigator(MoveMgr* mm, LineFollower* lfo) : Mode(mm) { 
	this->lfo = lfo;
	this->online = false;

//  /!\ test
	this->colorLine = nxt_msgs::Color();
	this->colorPastille = nxt_msgs::Color();
	this->colorLine.r = 0;
        this->colorLine.g = 0;
        this->colorLine.b = 0;
        this->colorPastille.r = 1;
        this->colorPastille.g = 0;
        this->colorPastille.b = 1;
}

void Navigator::treat() {
	if (Tools::compare_color(&colorMsg, &colorPastille)) {
		//if (this->online)
		//	this->stopLineFollower();
		this->applyChoice();
	}
	else {
		if (this->online) this->lfo->updateColor(this->colorMsg);
		else if (!this->getMm()->hasGoalSet() && !this->lfo->isLaunched()) { startLineFollower(); }
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

void Navigator::setColorLine(nxt_msgs::Color color) 	{ this->colorLine = color; }
void Navigator::setColorPastille(nxt_msgs::Color color) { this->colorPastille = color; }

void Navigator::startLineFollower() { 
	this->lfo->launch();
	this->lfo->updateColor(this->colorLine);
	this->online = true;
}

void Navigator::stopLineFollower() {
	this->lfo->unlaunch();
	this->online = false;
}

void Navigator::applyChoice() {
	ROS_INFO("CHOIX RESTANT = %d", this->choices.size());
	if (this->choices.size() <= 0) this->unlaunch();
	else if (checkDist(this->getMm()->getLeftPos(), this->getMm()->getRightPos())) {
		ROS_INFO("APPLY");
		Map::Choice choice = this->choices.front();
	        this->choices.pop_front();
	
		switch (choice) {
	       	case Map::AHEAD:
	        	this->getMm()->linearMove(BASE_EFFORT, PASTILLE_SIZE);
			break;
		case Map::BACK:
			this->getMm()->turn(BASE_EFFORT, MPI);
			break;
		default:
			this->getMm()->turn(BASE_EFFORT, (choice * TURN_RATIO));
			this->lfo->setOrientation((Map::Cardinal)(choice + 2));
			break;
		}
		this->leftPos = this->getMm()->getLeftPos();
		this->rightPos = this->getMm()->getRightPos();
	}
	else this->lfo->updateColor(this->colorMsg);
}

bool Navigator::checkDist(float a, float b) {
ROS_INFO("A = %f, B = %f", (a - this->leftPos), (b - this->rightPos));

	if ((a - this->leftPos) > 7 || (b - this->rightPos) > 3)
		return true;
	return false;
}
