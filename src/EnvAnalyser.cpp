#include "lunarNXT/EnvAnalyser.h"
#include "nxt_msgs/JointCommand.h"

#include "lunarNXT/LineFollower.h"

// Constructeurs
EnvAnalyser::EnvAnalyser() { ; }
EnvAnalyser::EnvAnalyser(ros::Publisher pub) {
	this->mm = MoveMgr(pub, "motor_l", "motor_r");
	this->bo = BaseOdometry();
	this->mode = new LineFollower(&mm);
}

// destructeur
EnvAnalyser::~EnvAnalyser() { ; }

// Callback du topic JointState
// Met a jour le MoveMgr
void EnvAnalyser::motorCallback(const sensor_msgs::JointState::ConstPtr& msg) {
	// clone des variables
	sensor_msgs::JointState _msg = sensor_msgs::JointState();
	_msg.name = msg->name;
	_msg.position = msg->position;
	_msg.effort = msg->effort;

	// update BaseOdometry
	this->bo.update(_msg);
	// update MoveMgr
	this->mm.updateMotors(_msg);
}

// Callback du capteur de contact droit
// met a jour le mode
void EnvAnalyser::rightTouchCallback(const nxt_msgs::Contact::ConstPtr& msg) {
	nxt_msgs::Contact _msg = nxt_msgs::Contact();
	_msg.contact = msg->contact;
	this->mode->updateRightTouch(_msg);
}

// Callback du capteur de contact gauche
// met a jour le mode
void EnvAnalyser::leftTouchCallback(const nxt_msgs::Contact::ConstPtr& msg) {
        nxt_msgs::Contact _msg = nxt_msgs::Contact();
        _msg.contact = msg->contact;
	this->mode->updateLeftTouch(_msg);
}


// Callback du capteur de couleur
// Met a jour le mode
void EnvAnalyser::colorCallback(const nxt_msgs::Color::ConstPtr& msg) {
	nxt_msgs::Color _msg = nxt_msgs::Color();
	_msg.r = msg->r;
	_msg.g = msg->g;
	_msg.b = msg->b;

	this->mode->updateColor(_msg);
}

// Callback du capteur a ultrason
// met a jour le MoveMgr et le mode
void EnvAnalyser::ultrasonicCallback(const nxt_msgs::Range::ConstPtr& msg) {
	nxt_msgs::Range _msg = nxt_msgs::Range();
	_msg.range = msg->range;
	_msg.range_min = msg->range_min;
	_msg.range_max = msg->range_max;
	_msg.spread_angle = msg->spread_angle;

	this->mm.updateRange(_msg);
	this->mode->updateRange(_msg);
}

// Callback de l'interface utilisateur
// donne des ordres au mode ou au MoveMgr (controle manuel ou non)
void EnvAnalyser::uiCallback(const lunarNXT::Order::ConstPtr& msg) {
	if (msg->order == "go")
		this->mm.linearMove(0.8, 1);
	else if (msg->order == "back")
                this->mm.linearMove(0.8, -1);
	else if (msg->order == "stop")
                this->mm.linearMove(0);
	else if (msg->order == "turn_l")
		this->mm.turn(0.8, 0.1);
	else if (msg->order == "turn_r")
		this->mm.turn(0.8, -0.1);
	else if (msg->order == "line")
		this->mode->launch();
	else if (msg->order == "no_line")
		this->mode->unlaunch();
}
