#include "lunarNXT/EnvAnalyser.h"
#include "nxt_msgs/JointCommand.h"


EnvAnalyser::EnvAnalyser() { }

EnvAnalyser::EnvAnalyser(MoveMgr* mm) {
	this->mm = mm;
	this->bo = BaseOdometry();
	this->lf = LineFollower(this->mm);
}

EnvAnalyser::~EnvAnalyser() {
	this->mm = NULL;
}

void EnvAnalyser::motorCallback(const sensor_msgs::JointState::ConstPtr& msg) {
	// update BaseOdometry
	sensor_msgs::JointState tmsg = sensor_msgs::JointState();
	tmsg.name = msg->name;
	tmsg.position = msg->position;
	tmsg.velocity = msg->velocity;
	tmsg.effort = msg->effort;
	this->bo.update(tmsg);
        
	// Update MoveMgr
	if (msg->name.back() == "motor_l") {
                this->mm->updateLeft(msg->position.back(), msg->effort.back());
        }
	else if (msg->name.back() == "motor_r") {
                this->mm->updateRight(msg->position.back(), msg->effort.back());
        }
	else  if (msg->name.back() == "motor_color") {

        }
}

void EnvAnalyser::rightTouchCallback(const nxt_msgs::Contact::ConstPtr& msg) {
	// TODO: what do we do ?
}

void EnvAnalyser::leftTouchCallback(const nxt_msgs::Contact::ConstPtr& msg) {
	// TODO: what do we do ?
}

void EnvAnalyser::colorCallback(const nxt_msgs::Color::ConstPtr& msg) {
	// update LineFollower
	nxt_msgs::Color colorMsg =  nxt_msgs::Color();
	colorMsg.intensity = msg->intensity;
	colorMsg.r = msg->r;
	colorMsg.g = msg->g;
	colorMsg.b = msg->b;
	this->lf.updateColor(colorMsg);
}

void EnvAnalyser::ultrasonicCallback(const nxt_msgs::Range::ConstPtr& msg) {
	// update MoveMgr
	this->mm->updateRange(msg->range);
}

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
		this->lf.launch();
	else if (msg->order == "no_line")
		this->lf.unlaunch();
}
