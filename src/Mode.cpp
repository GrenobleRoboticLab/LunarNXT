#include "lunarNXT/Mode.h"

using namespace Lunar_lib;

// Constructeur
Mode::Mode() : Receptor() { ; }
Mode::Mode(MoveMgr* mm) : Receptor(mm->getNameLeftMotor(), mm->getNameRightMotor()) { 
	this->mm = mm; 
	this->launched = false;
	this->initialized = false;
}

// Getters
bool Mode::isLaunched()    { return this->launched; }
bool Mode::isInitialized() { return this->initialized; }

// Setter
void Mode::setInitialized(bool init) { this->initialized = init; }

// Methode de lancement du mode
void Mode::launch() {
        this->launched = true;
        this->initialized = false;
}


// Methode d'arret du mode
// Donne l'ordre MoveMgr de stopper les moteurs
void Mode::unlaunch() {
        this->launched = false;
        this->initialized = false;
	this->mm->stop();
}

MoveMgr* Mode::getMm() { return this->mm; }
