#include "lunarNXT/Motor.h"

Motor::Motor(ros::NodeHandle n, std::string name){
	this->name = name;
	this->publisher = n.advertise<nxt_msgs::JointCommand>("joint_command", 5);
	this->subscriber = n.subscribe("joint_state", 15, &Motor::motorCallback, this);
	this->lastMsg = sensor_msgs::JointState();
	this->asOrder = false;		
}

void Motor::motorCallback(const sensor_msgs::JointState::ConstPtr& msg) {
	if (msg->name.back() == this->name) {
	
		// on stock les informations
		this->lastMsg.name.push_back(msg->name.back());
		this->lastMsg.position.push_back(msg->position.back());
		this->lastMsg.velocity.push_back(msg->velocity.back());
		this->lastMsg.effort.push_back(msg->effort.back());
		
		if (this->asOrder) {
			ROS_INFO("AS ORDER, POS ACT = %f", this->getLastPos());
			ROS_INFO("END POS = %f", this->endPos);
			if (this->getLastEffort() >= 0) {
				ROS_INFO("EFORT  >0 = %f", this->getLastEffort());
				if (this->getLastPos() >= this->endPos) {
					this->motorManager(0);
					this->asOrder = false;
				}
			}
			else if (this->getLastPos() <= this->endPos) {
                                ROS_INFO("EFORT  >0 = %f", this->getLastEffort());
				this->motorManager(0);
				this->asOrder = false;
			
			}
		}
	}
}

void Motor::motorManager(float effort) {
	nxt_msgs::JointCommand jc = nxt_msgs::JointCommand();
	jc.name = this->name;
	jc.effort = effort;
	this->publisher.publish(jc);
}

void Motor::giveOrder(float effort, float endPos) {
	this->asOrder = true;
	this->motorManager(effort);
	this->endPos = endPos;
}

sensor_msgs::JointState Motor::getLastMsg() { return this->lastMsg; }

float Motor::getLastPos() { 	return this->lastMsg.position.back(); }
float Motor::getLastVel() { 	return this->lastMsg.velocity.back(); }
float Motor::getLastEffort() { 	return this->lastMsg.effort.back(); }
