#include <ros/ros.h>
#include <stdio.h>

#include "lunarNXT/MoveMgr.h"
#include "lunarNXT/EnvAnalyser.h"
#include "nxt_msgs/JointCommand.h"

class LunarNXT {
private:
	ros::NodeHandle n;
	std::vector<ros::Subscriber> subs;
	EnvAnalyser ea;

public:
	LunarNXT();
};

LunarNXT::LunarNXT() {
        ros::Publisher pub = this->n.advertise<nxt_msgs::JointCommand>("joint_command", 5);
	this->ea = EnvAnalyser(pub);

        this->subs.push_back(n.subscribe("ultrasonic_sensor", 5, &EnvAnalyser::ultrasonicCallback, &this->ea));
        this->subs.push_back(n.subscribe("joint_state", 5, &EnvAnalyser::motorCallback, &this->ea));
        this->subs.push_back(n.subscribe("color_frame", 5, &EnvAnalyser::colorCallback, &this->ea));
        this->subs.push_back(n.subscribe("touch_l", 5, &EnvAnalyser::leftTouchCallback, &this->ea));
        this->subs.push_back(n.subscribe("touch_r", 5, &EnvAnalyser::rightTouchCallback, &this->ea));
        this->subs.push_back(n.subscribe("ui_publish", 5, &EnvAnalyser::uiCallback, &this->ea));

}

int main(int argc, char** argv) {
	ros::init(argc, argv, "lunarNXT");
	ros::NodeHandle n;
	
	LunarNXT myRobot = LunarNXT();
	
	ros::spin();
	
	return(0);
}
