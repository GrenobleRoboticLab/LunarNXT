#include <ros/ros.h>
#include <stdio.h>

#include "LunarNXT/MoveMgr.h"
#include "LunarNXT/EnvAnalyser.h"
#include "nxt_msgs/JointCommand.h"

using namespace Lunar_lib;

class NodeLunarNXT {
private:
	ros::NodeHandle			m_NodeHandle;
	std::vector<ros::Subscriber>	m_vSubscriber;
	ros::Publisher			m_Publisher;
	EnvAnalyser			m_EnvAnalyser;

public:
	NodeLunarNXT();
	bool				Init();
};

NodeLunarNXT::NodeLunarNXT() { ; }

bool NodeLunarNXT::Init() {
    m_vSubscriber.push_back(m_NodeHandle.subscribe("ultrasonic_sensor",	        5, &EnvAnalyser::UltrasonicCallback,	&m_EnvAnalyser));
    m_vSubscriber.push_back(m_NodeHandle.subscribe("joint_state",		5, &EnvAnalyser::MotorCallback,			&m_EnvAnalyser));
    m_vSubscriber.push_back(m_NodeHandle.subscribe("color_frame",		5, &EnvAnalyser::ColorCallback,			&m_EnvAnalyser));
    m_vSubscriber.push_back(m_NodeHandle.subscribe("touch_l",			5, &EnvAnalyser::LeftTouchCallback,		&m_EnvAnalyser));
    m_vSubscriber.push_back(m_NodeHandle.subscribe("touch_r",			5, &EnvAnalyser::RightTouchCallback,	&m_EnvAnalyser));
    m_vSubscriber.push_back(m_NodeHandle.subscribe("ui_publish",		5, &EnvAnalyser::UiCallback,			&m_EnvAnalyser));

    m_Publisher = m_NodeHandle.advertise<nxt_msgs::JointCommand>("joint_command", 5);

    return m_EnvAnalyser.Init(&m_Publisher, "motor_l", "motor_r");
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "lunarNXT");

    NodeLunarNXT    myRobot;
    int             nReturn = 0;

    if (myRobot.Init())
	ros::spin();
    else {
	nReturn = 1;
	ROS_ERROR("Something bad happened :'(");
    }
	
    return nReturn;
}
