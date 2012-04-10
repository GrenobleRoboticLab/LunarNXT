#include "lunarNXT/MoveMgr.h"
#include "nxt_msgs/JointCommand.h"

#define MINRANGE 0.2
#define PI 3.14159265
#define WHEEL_RADIUS 7.5

// Constructeur
MoveMgr::MoveMgr() { }

MoveMgr::MoveMgr(ros::Publisher publisher, std::string leftName, std::string rightName) : Receptor(leftName, rightName) {
        this->publisher = publisher;
        this->hasGoal = false;
}

// Destructeur
MoveMgr::~MoveMgr() {
        this->stop();
}

// Mouvement lineaire infini ver l'avant ou l'arriere
void MoveMgr::linearMove(float effort) {
	ROS_INFO("lmove");
        this->publish(effort, effort);
}

// Rotation infinie vers la gauche
void MoveMgr::turnLeft(float effort) {
        this->publish(-effort, effort);
}

// Rotation infinie vers la droite
void MoveMgr::turnRight(float effort) {
        this->publish(effort, -effort);
}

// Mouvement lineaire ver l'avant ou l'arriere
void MoveMgr::linearMove(float effort, int cm) {
        this->hasGoal = true;
        this->desiredLeftPosition = this->leftPosition + (cm/2);
        this->desiredRightPosition = this->rightPosition + (cm/2);
        if (cm >= 0) this->publish(effort, effort);
        else this->publish(-effort, -effort);
}


// Rotation finie vers la droite ou la gauche
void MoveMgr::turn(float effort, float rad) {
        this->hasGoal = true;
        float distance_to_reach = rad * (WHEEL_RADIUS/2);
        this->desiredRightPosition = this->rightPosition + distance_to_reach;
        this->desiredLeftPosition = this->leftPosition - distance_to_reach;

        if (rad >= 0) this->publish(-effort, effort);
        else this->publish(effort, -effort);
}

// stope tout deplacement (fini et infini) en cours
void MoveMgr::stop() {
        this->hasGoal = false;
        this->publish(0, 0);
}

// Mise a jour de la position et de l'effort actuelle des Moteurs
void MoveMgr::updateMotors(sensor_msgs::JointState msg) {
	if (this->getNameLeftMotor() == msg.name.back()) {
        	this->leftPosition = msg.position.back();
        	this->leftEffort = msg.effort.back();
	}
	else if (this->getNameRightMotor() == msg.name.back()) {
		this->rightPosition = msg.position.back();
		this->rightEffort = msg.effort.back();
	}
	this->checkGoal();
}

// Mise a jour du capteur a ultrason
// stope les moteurs en cas de proximite
void MoveMgr::updateRange(nxt_msgs::Range msg) {
        if (msg.range < MINRANGE) this->stop();
}

// publie les efforts desires aux moteurs
void MoveMgr::publish(float leftEffort, float rightEffort) {
        this->desiredLeftEffort = leftEffort;
        this->desiredRightEffort = rightEffort;

        nxt_msgs::JointCommand leftCommand = nxt_msgs::JointCommand();
        nxt_msgs::JointCommand rightCommand = nxt_msgs::JointCommand();

        leftCommand.name = this->getNameLeftMotor();
        leftCommand.effort = leftEffort;
	
        rightCommand.name = this->getNameRightMotor();
        rightCommand.effort = rightEffort;

        this->publisher.publish(leftCommand);
        this->publisher.publish(rightCommand);
}

// verifie si les moteurs ont atteint les positions desirees
void MoveMgr::checkGoal() {
        if (this->hasGoal) {
                bool left = false;
                bool right = false;
                if (this->leftEffort == this->desiredLeftEffort)
                        left = checkLeftGoal();

                if (this->rightEffort == this->desiredRightEffort)
                        right = checkRightGoal();

                if (right || left)
                        this->publish(this->desiredLeftEffort, this->desiredRightEffort);

                if (this->desiredLeftEffort == 0 && this->desiredRightEffort == 0)
                        this->hasGoal = false;
        }
}

// verifie si le moteur gauche a atteint la position desiree
bool MoveMgr::checkLeftGoal() {
        if ((this->leftEffort > 0 && this->desiredLeftPosition <= this->leftPosition) ||
            (this->leftEffort < 0 && this->desiredLeftPosition >= this->leftPosition)) {
                this->desiredLeftEffort = 0;
                return true;
        }
        return false;
}

// verifie si le moteur droit a atteint la position desiree
bool MoveMgr::checkRightGoal() {
        if ((this->rightEffort > 0 && this->desiredRightPosition <= this->rightPosition) ||
            (this->rightEffort < 0 && this->desiredRightPosition >= this->rightPosition)) {
                this->desiredRightEffort = 0;
                return true;
        }
        return false;
}

// Getters
bool MoveMgr::hasGoalSet()	{ return this->hasGoal; }
float MoveMgr::getLeftPos()	{ return this->leftPosition; }
float MoveMgr::getRightPos()	{ return this->rightPosition; }
