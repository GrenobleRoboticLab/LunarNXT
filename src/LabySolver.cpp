#include "lunarNXT/LabySolver.h"

// Constructeurs
LabySolver::LabySolver() : Mode() { }

LabySolver::LabySolver(MoveMgr* mm) : Mode(mm) {
	this->lfo = new LineFollower(mm);
	this->lfi = new LineFinder(mm);
	this->nav = new Navigator(mm, this->lfo);
}

LabySolver::~LabySolver() { 
	delete this->lfi;
	delete this->lfo;
	delete this->nav;
}

void LabySolver::updateColor(nxt_msgs::Color msg) {
}

void LabySolver::treat () {
	;
}
