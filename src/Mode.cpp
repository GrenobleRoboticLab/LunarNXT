#include "lunarNXT/Mode.h"

Mode::Mode() { ; }
Mode::Mode(MoveMgr* mm) { 
	this->mm = mm; 
	this->launched = false;
	this->initialized = false;
}

Mode::~Mode() { ; }

bool Mode::isLaunched()    { return this->launched; }
bool Mode::isInitialized() { return this->initialized; }

void Mode::setInitialized(bool init) { this->initialized = init; }

void Mode::launch() {
        this->launched = true;
        this->initialized = false;
};

void Mode::unlaunch() {
        this->launched = false;
        this->initialized = false;
	this->mm->stop();
};


