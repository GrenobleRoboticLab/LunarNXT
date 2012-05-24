#include "lunarNXT/LineFinder.h"

using namespace lunar_lib;

LineFinder::LineFinder() : Mode() { ; }

LineFinder::LineFinder(MoveMgr* mm) : Mode(mm) {
	this->setInitialized(false);
}

void LineFinder::treat() {
	;
}
