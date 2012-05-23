#include "lunarNXT/Navigator.h"
#include "lunarNXT/Tools.h"

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
	if (Tools::compare_color(&colorMsg, &colorLine)) {
		ROS_INFO("Line");
		if (this->online)
			this->lfo->updateColor(this->colorMsg);
		else
			this->startLineFollower();
	}
	else if (Tools::compare_color(&colorMsg, &colorPastille)) {
		ROS_INFO("Pastille");
		if (this->online) {
			this->stopLineFollower();
			this->applyChoice();
		}
	}
        else if (!this->getMm()->hasGoalSet() && !this->online) {
		this->startLineFollower();
	}
	else if (!this->getMm()->hasGoalSet()) { 
		ROS_INFO("uc");
		this->lfo->updateColor(this->colorMsg);
	}
}

void Navigator::init(std::list<int> choices) { 
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
	ROS_INFO("choix restant %d", this->choices.size());
	if (this->choices.size() <= 0) this->unlaunch();
	else {
		int choice = this->choices.front();
	        this->choices.pop_front();
	
	       	if (choice == 0)
	        	this->getMm()->linearMove(0.72, 2);
		else { 
			this->getMm()->turn(0.72, (choice * 0.41));
			this->lfo->setOrientation((Map::Cardinal)(choice + 2));
		}
	}
}
