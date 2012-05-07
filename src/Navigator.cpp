#include "lunarNXT/Navigator.h"

Navigator::Navigator() : Mode() { ; }
Navigator::Navigator(MoveMgr* mm, LineFollower* lfo) : Mode(mm) { this->lfo = lfo; }

void Navigator::treat() { 
	; 
}

void Navigator::init(std::list<int> choices) { this->choices = choices; }

void Navigator::updateColor(nxt_msgs::Color msg) { 
	if (this->isLaunched() && isInitialized())
		this->treat(); 
}

