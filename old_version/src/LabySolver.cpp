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
	else if (this->isLaunched()) {
		this->currentMode = NULL;
		this->state = INIT;
	}
}

void LabySolver::treat () {
	if (Tools::is_end_color(this->colorMsg)) {
		this->currentMode->updateColor(this->colorMsg);
		if (!this->currentMode->isLaunched()) {
			switch(this->state) {
				case INIT:
					this->navLauncher(std::list<Map::Choice>());
					break;
				case NAVIGATE:
					this->lfiLauncher();
					break;
				case LINEFINDER:
					this->compute();
					break;
			}
		}
	}
	else  this->unlaunch();
}

void LabySolver::navLauncher(std::list<Map::Choice> choices) {
	this->nav->init(choices);
	this->currentMode = this->nav;
	this->currentMode->launch();
	this->state = NAVIGATE;
}

void LabySolver::lfiLauncher() {
	this->lfi->init(this->currentElement);
	this->currentMode = this->lfi;
	this->currentMode->launch();
	this->state = LINEFINDER;
}

void LabySolver::compute() {
	std::list<Map::Choice> choice = std::list<Map::Choice>();
	choice.push_back(this->currentElement->getLeftChoice(this->currentElement));
	this->navLauncher(choice);
}
