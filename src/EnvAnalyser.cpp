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
	sensor_msgs::JointState motorMsg = sensor_msgs::JointState();
	motorMsg.name = msg->name;
	motorMsg.position = msg->position;
	motorMsg.effort = msg->effort;
	motorMsg.velocity = msg->velocity;

	// update BaseOdometry
	this->bo.update(motorMsg);

	// update MoveMgr
	this->mm->updateMotors(motorMsg);
}

// Callback du capteur de contact droit
// met a jour le mode
void EnvAnalyser::rightTouchCallback(const nxt_msgs::Contact::ConstPtr& msg) {
	nxt_msgs::Contact contactMsg = nxt_msgs::Contact();
	contactMsg.contact = msg->contact;
	this->mode->updateRightTouch(contactMsg);
}

// Callback du capteur de contact gauche
// met a jour le mode
void EnvAnalyser::leftTouchCallback(const nxt_msgs::Contact::ConstPtr& msg) {
	nxt_msgs::Contact contactMsg = nxt_msgs::Contact();
	contactMsg.contact = msg->contact;
	this->mode->updateLeftTouch(contactMsg);
}


// Callback du capteur de couleur
// Met a jour le mode
void EnvAnalyser::colorCallback(const nxt_msgs::Color::ConstPtr& msg) {
	nxt_msgs::Color colorMsg =  nxt_msgs::Color();
	colorMsg.intensity = msg->intensity;
	colorMsg.r = msg->r;
	colorMsg.g = msg->g;
	colorMsg.b = msg->b;
	
	this->mode->updateColor(colorMsg);
}

// Callback du capteur a ultrason
// met a jour le MoveMgr et le mode
void EnvAnalyser::ultrasonicCallback(const nxt_msgs::Range::ConstPtr& msg) {
	nxt_msgs::Range rangeMsg = nxt_msgs::Range();
	rangeMsg.range = msg->range;
	rangeMsg.range_min = msg->range_min;
	rangeMsg.range_max = msg->range_max;
	rangeMsg.spread_angle = msg->spread_angle;

	this->mm->updateRange(rangeMsg);
	this->mode->updateRange(rangeMsg);
}

// Callback de l'interface utilisateur
// donne des ordres au mode ou au MoveMgr (contrôle manuel ou non)
void EnvAnalyser::uiCallback(const lunarNXT::Order::ConstPtr& msg) {
	// actions commandee par l'utilisateur
	// cf ${ProjectDir}/msg/Order.msg
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
