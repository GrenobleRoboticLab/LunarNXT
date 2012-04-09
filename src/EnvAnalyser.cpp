#include "lunarNXT/EnvAnalyser.h"
#include "nxt_msgs/JointCommand.h"

#include "lunarNXT/LineFollower.h"

// Constructeurs
EnvAnalyser::EnvAnalyser() { }

EnvAnalyser::EnvAnalyser(MoveMgr* mm) {
	this->mm = mm;
	this->bo = BaseOdometry();
	this->mode = new LineFollower(this->mm);
}

// destructeur
EnvAnalyser::~EnvAnalyser() {
	delete this->mm;
	delete this->mode;
}

// Callback du topic JointState
// Met a jour le MoveMgr
void EnvAnalyser::motorCallback(const sensor_msgs::JointState::ConstPtr& msg) {
	// update BaseOdometry
	this->bo.update(msg);
	// update MoveMgr
	this->mm->updateMotors(msg);
}

// Callback du capteur de contact droit
// met a jour le mode
void EnvAnalyser::rightTouchCallback(const nxt_msgs::Contact::ConstPtr& msg) {
	this->mode->updateRightTouch(msg);
}

// Callback du capteur de contact gauche
// met a jour le mode
void EnvAnalyser::leftTouchCallback(const nxt_msgs::Contact::ConstPtr& msg) {
	this->mode->updateLeftTouch(msg);
}


// Callback du capteur de couleur
// Met a jour le mode
void EnvAnalyser::colorCallback(const nxt_msgs::Color::ConstPtr& msg) {
	this->mode->updateColor(msg);
}

// Callback du capteur a ultrason
// met a jour le MoveMgr et le mode
void EnvAnalyser::ultrasonicCallback(const nxt_msgs::Range::ConstPtr& msg) {
	this->mm->updateRange(msg);
	this->mode->updateRange(msg);
}

// Callback de l'interface utilisateur
// donne des ordres au mode ou au MoveMgr (controle manuel ou non)
void EnvAnalyser::uiCallback(const lunarNXT::Order::ConstPtr& msg) {
	if (msg->order == "go")
		this->mm->linearMove(0.8, 1);
	else if (msg->order == "back")
                this->mm->linearMove(0.8, -1);
	else if (msg->order == "stop")
                this->mm->linearMove(0);
	else if (msg->order == "turn_l")
		this->mm->turn(0.8, 0.1);
	else if (msg->order == "turn_r")
		this->mm->turn(0.8, 0.1);
	else if (msg->order == "line")
		this->mode->launch();
	else if (msg->order == "no_line")
		this->mode->unlaunch();
}
