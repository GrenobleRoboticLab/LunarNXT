#include "lunarNXT/LineFinder.h"

LineFinder::LineFinder() : Mode() { ; }

LineFinder::LineFinder(MoveMgr* mm) : Mode(mm) {
	this->setInitialized(false);
}

void LineFinder::treat() {
	;
}
