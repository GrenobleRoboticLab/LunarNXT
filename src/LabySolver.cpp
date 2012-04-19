#include "lunarNXT/LabySolver.h"

// Constructeurs
LabySolver::LabySolver() : Mode() { }

LabySolver::LabySolver(MoveMgr* mm) : Mode(mm) {
	this->lf = new LineFollower(mm);
	this->map = Map();
}

LabySolver::~LabySolver() { delete this->lf; }

void LabySolver::updateColor(nxt_msgs::Color msg) {
}

void LabySolver::treat () {
	;
}
