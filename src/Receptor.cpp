#include "lunarNXT/Receptor.h"

using namespace lunar_lib;

// Constructeurs
Receptor::Receptor() { ; }

Receptor::Receptor(std::string nameLeftMotor, std::string nameRightMotor) {
        this->nameLeftMotor = nameLeftMotor;
	this->nameRightMotor = nameRightMotor;
}

// Getters
std::string Receptor::getNameLeftMotor() { return this->nameLeftMotor; }
std::string Receptor::getNameRightMotor() { return this->nameRightMotor; }

// Touch sensor updaters
void Receptor::updateRightTouch(nxt_msgs::Contact msg) { ; }
void Receptor::updateLeftTouch(nxt_msgs::Contact msg) { ; }

// Range sensor updater
void Receptor::updateRange(nxt_msgs::Range msg) { ; }

// Color sensor updater
void Receptor::updateColor(nxt_msgs::Color msg) { ; }

// Motors updater
void Receptor::updateMotors(sensor_msgs::JointState msg) { ; }
