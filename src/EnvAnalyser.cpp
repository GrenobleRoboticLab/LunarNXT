#include "LunarNXT/EnvAnalyser.h"
#include "LunarNXT/LineFollower.h"

using namespace Lunar_lib;

EnvAnalyser::EnvAnalyser() { 
	m_pMoveManager	= NULL;
	m_pMode		= NULL;
}

EnvAnalyser::~EnvAnalyser() 
{ 
	ReleaseMode();
	ReleaseMoveManager();
}

bool EnvAnalyser::Init(ros::Publisher* pPublisher, const std::string & sLMotorName, const std::string & sRMotorName) {
	bool bRet = false;

	m_pMoveManager	= new MoveMgr(sLMotorName, sRMotorName);
	
	if (CheckMoveManager() && pPublisher)
		bRet = m_pMoveManager->Init(pPublisher);
	else
		ReleaseMoveManager();

	return bRet;
}

void EnvAnalyser::MotorCallback(const sensor_msgs::JointState::ConstPtr& msg) {
	sensor_msgs::JointState	tempMsg;

	tempMsg.name		= msg->name;
	tempMsg.position	= msg->position;
	tempMsg.effort		= msg->effort;

	if (CheckMoveManager())
		m_pMoveManager->UpdateMotors(tempMsg);
}

void EnvAnalyser::RightTouchCallback(const nxt_msgs::Contact::ConstPtr& msg) {
	nxt_msgs::Contact	tempMsg;

	tempMsg.contact = msg->contact;

	if (CheckMode())
		m_pMode->UpdateRightTouch(tempMsg);
}

void EnvAnalyser::LeftTouchCallback(const nxt_msgs::Contact::ConstPtr& msg) {
	nxt_msgs::Contact tempMsg;
	
	tempMsg.contact = msg->contact;

	if (CheckMode())
		m_pMode->UpdateLeftTouch(tempMsg);
}


void EnvAnalyser::ColorCallback(const nxt_msgs::Color::ConstPtr& msg) {
	nxt_msgs::Color tempMsg;

	tempMsg.r = msg->r;
	tempMsg.g = msg->g;
	tempMsg.b = msg->b;

	if (CheckMode())
		m_pMode->UpdateColor(tempMsg);
}

void EnvAnalyser::UltrasonicCallback(const nxt_msgs::Range::ConstPtr& msg) {
	nxt_msgs::Range tempMsg;

	tempMsg.range			= msg->range;
	tempMsg.range_min		= msg->range_min;
	tempMsg.range_max		= msg->range_max;
	tempMsg.spread_angle	= msg->spread_angle;

	if (CheckMoveManager())
		m_pMoveManager->UpdateRange(tempMsg);

	if (CheckMode())
		m_pMode->UpdateRange(tempMsg);
}

void EnvAnalyser::UiCallback(const LunarNXT::Order::ConstPtr& msg) {
	
        if (msg->sOrder == "go")
	{
		if (CheckMoveManager())
			m_pMoveManager->LinearMove(BASE_EFFORT);
	}
	else if (msg->sOrder == "back")
	{
		if (CheckMoveManager())
			m_pMoveManager->LinearMove(-BASE_EFFORT);
	}
	else if (msg->sOrder == "stop")
        {
		if (CheckMoveManager())
			m_pMoveManager->Stop();
	}
	else if (msg->sOrder == "turn_l")
	{
		if (CheckMoveManager())
			m_pMoveManager->TurnLeft(BASE_EFFORT);
	}
	else if (msg->sOrder == "turn_r")
	{
		if (CheckMoveManager())
			m_pMoveManager->TurnRight(BASE_EFFORT);
	}
	else if (msg->sOrder == "launch")
		LaunchMode(msg->nEnum);
	else if (msg->sOrder == "unlaunch")
		KillMode();
}

void EnvAnalyser::LaunchMode(int nEnum) {
	if (CheckMode())
		ROS_ERROR("One mode is currently active. Kill it before");
	else {
		ReleaseMode();

		switch (nEnum) {
		case 0:
			ROS_ERROR("No choice have been set yet.");
		default:
			m_pMode = new LineFollower();
			break;
		};

		if (CheckMode() && CheckMoveManager())
		{
			m_pMode->SetMoveManager(&m_pMoveManager);
			m_pMode->Launch();
			ROS_INFO("Mode launched.");
		}
		else
			ReleaseMode();
	}
}

void EnvAnalyser::KillMode() {
	if (CheckMode())
		m_pMode->Unlaunch();
	ReleaseMode();

	if (CheckMode())
		ROS_ERROR("Mode still runing, you may have to try again.");
	else
		ROS_INFO("Mode killed.");
}

void EnvAnalyser::ReleaseMode() {
	if (m_pMode)
		delete m_pMode;
	m_pMode = NULL;
}

void EnvAnalyser::ReleaseMoveManager() {
	if (m_pMoveManager)
		delete m_pMoveManager;
	m_pMode = NULL;
}

bool EnvAnalyser::CheckMoveManager() {
	bool bRet = true;

	if (!m_pMoveManager) {
		ROS_ERROR("MoveManager is NULL.");
		bRet = false;
	}

	return bRet;
}

bool EnvAnalyser::CheckMode() {
	bool bRet = true;

	if (!m_pMode) {
		// ROS_ERROR("Mode is NULL.");
		bRet = false;
	}

	return bRet;
}
