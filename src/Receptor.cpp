#include "lunarNXT/Receptor.h"

// Constructeurs
Receptor::Receptor() { ; }

Receptor::Receptor(std::string nameLeftMotor, std::string nameRightMotor) {
        this->nameLeftMotor = nameLeftMotor;
	this->nameRightMotor = nameRightMotor;
}

// destructeur
Receptor::~Receptor() { ROS_INFO("Receptor deleted"); }

// Getters
std::string Receptor::getNameLeftMotor() { return this->nameLeftMotor; }
std::string Receptor::getNameRightMotor() { return this->nameRightMotor; }

// Touch sensor updaters
void Receptor::updateRightTouch(const nxt_msgs::Contact::ConstPtr msg) { ; }
void Receptor::updateLeftTouch(const nxt_msgs::Contact::ConstPtr msg) { ; }

// Range sensor updater
void Receptor::updateRange(const nxt_msgs::Range::ConstPtr msg) { ; }

// Color sensor updater
void Receptor::updateColor(const nxt_msgs::Color::ConstPtr msg) { ; }

// Motors updater
void Receptor::updateMotors(const sensor_msgs::JointState::ConstPtr msg) { ; }
