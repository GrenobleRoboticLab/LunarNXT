#include "lunarNXT/Navigator.h"
#include "lunarNXT/Tools.h"

#define TURN_RATIO 2 
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
	if (Tools::compare_color(&colorMsg, &colorPastille))
		this->applyChoice();
	else {
		ROS_INFO("not on pastille");
		if (this->online) { 
			this->lfo->updateColor(this->colorMsg);ROS_INFO("online");}
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

	if (checkDist(this->getMm()->getLeftPos(), this->getMm()->getRightPos())) {
		
		if (this->online) this->stopLineFollower();
		ROS_INFO("APPLY");
		if (this->choices.size() <= 0) this->unlaunch();

		else {
			this->getMm()->stop();
			Map::Choice choice = this->choices.front();
	        	this->choices.pop_front();
	ROS_INFO("else");
			switch (choice) {
	       			case Map::AHEAD:
	        			this->getMm()->linearMove(BASE_EFFORT, PASTILLE_SIZE);
					break;
				case Map::BACK:
					this->getMm()->turnAround(BASE_EFFORT, 3*MPI);
					break;
				default:
					this->getMm()->turnAround(BASE_EFFORT+0.05, (choice * TURN_RATIO));
					ROS_INFO("TURN, %d", (choice * TURN_RATIO));
					this->lfo->setOrientation((Map::Cardinal)(choice + 2));
					break;
			}
	
			this->leftPos = this->getMm()->getLeftPos();
			this->rightPos = this->getMm()->getRightPos();
		}
	}
}

bool Navigator::checkDist(float a, float b) {
	ROS_INFO("A = %f, B = %f", (a - this->leftPos), (b - this->rightPos));
	if ((a - this->leftPos) > MPI || (b - this->rightPos) > MPI || (a - this->leftPos) < -MPI || (b - this->rightPos) < -MPI )
		return true;
	return false;
}
