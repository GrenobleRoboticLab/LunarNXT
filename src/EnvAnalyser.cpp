#include "lunarNXT/EnvAnalyser.h"
#include "lunarNXT/LineFollower.h"
#include "lunarNXT/LabySolver.h"

// Constructeurs
EnvAnalyser::EnvAnalyser() { ; }
EnvAnalyser::EnvAnalyser(ros::NodeHandle pub) {
	this->mm = new MoveMgr(pub, "motor_l", "motor_r");
	this->mode = new LineFollower(mm);
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

	// update MoveMgr
	this->mm->updateMotors(_msg);

	/// pure test
	// pthread_create(&threads[0], NULL, &EnvAnalyser::motorsT, new EnvAnalyser::processEventArgs(this->mode, this->mm, &_msg, MOTOR));
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

	this->mm->updateRange(_msg);
	this->mode->updateRange(_msg);
}

// Callback de l'interface utilisateur
// donne des ordres au mode ou au MoveMgr (controle manuel ou non)
void EnvAnalyser::uiCallback(const lunarNXT::Order::ConstPtr& msg) {
	if (msg->order == "go")
		this->mm->linearMove(0.8);
	else if (msg->order == "back")
                this->mm->linearMove(-0.8);
	else if (msg->order == "stop")
                this->mm->stop();
	else if (msg->order == "turn_l")
		this->mm->turnLeft(0.8);
	else if (msg->order == "turn_r")
		this->mm->turnRight(0.8);
	else if (msg->order == "line")
		this->mode->launch();
	else if (msg->order == "no_line")
		this->mode->unlaunch();
}

void *EnvAnalyser::motorsT(void* msg) {
	EnvAnalyser::processEventArgs* arg =  (EnvAnalyser::processEventArgs*)msg;
	
	switch (arg->id_thread) {
		case MOTOR:
			arg->recs[0]->updateMotors(*(sensor_msgs::JointState*)arg->msg);
			arg->recs[1]->updateMotors(*(sensor_msgs::JointState*)arg->msg);
			break;
		case COLOR:
			arg->recs[0]->updateColor(*(nxt_msgs::Color*)arg->msg);
                        arg->recs[1]->updateColor(*(nxt_msgs::Color*)arg->msg);
			break;
		case TOUCH_L:
			arg->recs[0]->updateLeftTouch(*(nxt_msgs::Contact*)arg->msg);
                        arg->recs[1]->updateLeftTouch(*(nxt_msgs::Contact*)arg->msg);
			break;
		case TOUCH_R:
			arg->recs[0]->updateRightTouch(*(nxt_msgs::Contact*)arg->msg);
                        arg->recs[1]->updateRightTouch(*(nxt_msgs::Contact*)arg->msg);
			break;
		case ULTRASONIC:
			arg->recs[0]->updateRange(*(nxt_msgs::Range*)arg->msg);
                        arg->recs[1]->updateRange(*(nxt_msgs::Range*)arg->msg);
			break;
		default: break;
	}
	
	pthread_exit(NULL);
}
