#include "lunarNXT/LabySolver.h"
#include "lunarNXT/Tools.h"

using namespace Lunar_lib;

// Constructeurs
LabySolver::LabySolver() : Mode() { }

LabySolver::LabySolver(MoveMgr* mm) : Mode(mm) {
	this->lfo = new LineFollower(mm);
	this->lfi = new LineFinder(mm);
	this->nav = new Navigator(mm, this->lfo);
	this->currentElement = new LabyElement();
}

LabySolver::~LabySolver() { 
	delete this->lfi;
	delete this->lfo;
	delete this->nav;
	delete this->currentElement;
}

void LabySolver::updateColor(nxt_msgs::Color msg) {
	this->colorMsg = msg;
	if (this->isLaunched() && this->isInitialized())
		this->treat();
}

void LabySolver::treat () {
	;
}
