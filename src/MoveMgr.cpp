#include <math.h>
#include "LunarNXT/MoveMgr.h"
#include "nxt_msgs/JointCommand.h"

#define MINRANGE 0.2
#define WHEEL_RADIUS 7.5

using namespace Lunar_lib;

MoveMgr::MoveMgr() {
	m_pPublisher	= NULL;
	m_bHasGoal	= false;
}

MoveMgr::MoveMgr(const std::string & sLMotorName, const std::string & sRMotorName)
	: Receptor(sLMotorName, sRMotorName)
{
	m_pPublisher	= NULL;
	m_bHasGoal		= false;
}

MoveMgr::~MoveMgr() { ; }

bool MoveMgr::Init(ros::Publisher* pPublisher) {
	bool bRet = false;

	if (pPublisher)
        {
	    m_pPublisher = pPublisher;
            bRet = true;
        }

	return bRet;
}

void MoveMgr::LinearMove(float fEffort) {
	Publish(fEffort, fEffort);
}

void MoveMgr::LinearMove(float fEffort, float fCm) {
	m_bHasGoal				= true;

	m_fDesiredLeftPosition	= m_fLeftPosition + (fCm / 2);
	m_fDesiredRightPosition = m_fRightPosition + (fCm / 2);
        
	if (fCm >= 0.0f)
		Publish(fEffort, fEffort);
	else 
		Publish(-fEffort, -fEffort);
}

void MoveMgr::TurnLeft(float fEffort) {
	Publish(-fEffort, fEffort);
}

void MoveMgr::TurnRight(float fEffort) {
	Publish(fEffort, -fEffort);
}

void MoveMgr::Turn(float fEffort, float rad) {
	float fDistance_to_reach	= rad * (WHEEL_RADIUS/2);
	m_bHasGoal					= true;

	m_fDesiredLeftPosition		= m_fLeftPosition - fDistance_to_reach;
	m_fDesiredRightPosition		= m_fRightPosition + fDistance_to_reach;

	if (rad >= 0)
		Publish(-fEffort, fEffort);
	else 
		Publish(fEffort, -fEffort);
}

void MoveMgr::TurnAroundLeft(float fEffort) {
	Publish(-0.5f, fEffort);
}

void MoveMgr::TurnAroundRight(float fEffort) {
	Publish(-0.5f, -fEffort);
}

void MoveMgr::TurnAround(float fEffort, float fRad) {
	float fDistance_to_reach	= std::fabs(fRad * WHEEL_RADIUS);
	m_bHasGoal					= true;
	
	if (fRad >= 0) {
		m_fDesiredLeftPosition		= m_fLeftPosition+0.1;
		m_fDesiredRightPosition		= m_fRightPosition + fDistance_to_reach;
		Publish(-0.5f, fEffort);
	}
	else {
		m_fDesiredLeftPosition		= m_fLeftPosition+0.1;
		m_fDesiredRightPosition		= m_fRightPosition + fDistance_to_reach;
		Publish(fEffort, -0.5f);
	}
}

void MoveMgr::Stop() {
        m_bHasGoal = false;
        Publish(0.0f, 0.0f);
}

void MoveMgr::UpdateMotors(sensor_msgs::JointState msg) {
	if (GetNameLeftMotor() == msg.name.back()) {
		m_fLeftPosition	= msg.position.back();
		m_fLeftEffort	= msg.effort.back();
	}
	else if (GetNameRightMotor() == msg.name.back()) {
		m_fRightPosition	= msg.position.back();
		m_fRightEffort		= msg.effort.back();
	}

	CheckGoal();
}

void MoveMgr::UpdateRange(nxt_msgs::Range msg) {
        if (msg.range < MINRANGE)
			Stop();
}

bool	MoveMgr::HasGoalSet()	const { return m_bHasGoal;		}
float	MoveMgr::GetLeftPos()	const { return m_fLeftPosition;		}
float	MoveMgr::GetRightPos()	const { return m_fRightPosition;	}

void MoveMgr::Publish(float fLeftEffort, float fRightEffort) {
        m_fDesiredLeftEffort	= fLeftEffort;
        m_fDesiredRightEffort	= fRightEffort;

        nxt_msgs::JointCommand leftCommand = nxt_msgs::JointCommand();
        nxt_msgs::JointCommand rightCommand = nxt_msgs::JointCommand();

        leftCommand.name	= GetNameLeftMotor();
        leftCommand.effort	= fLeftEffort;

        rightCommand.name	= GetNameRightMotor();
        rightCommand.effort	= fRightEffort;

		if (CheckPublisher())
		{
			m_pPublisher->publish(leftCommand);
			m_pPublisher->publish(rightCommand);
		}
}

void MoveMgr::CheckGoal() {
	if (m_bHasGoal) {
		bool bLeft = false;
		bool bRight = false;
	
		if (m_fLeftEffort == m_fDesiredLeftEffort)
			bLeft = CheckLeftGoal();
		
		if (m_fRightEffort == m_fDesiredRightEffort)
			bRight = CheckRightGoal();

		if (bRight || bLeft)
			Publish(m_fDesiredLeftEffort, m_fDesiredRightEffort);

		if (m_fDesiredLeftEffort == 0.0f && m_fDesiredRightEffort == 0.0f)
			m_bHasGoal = false;
	}
}

bool MoveMgr::CheckLeftGoal() {
	bool bRet = false;

	if (
		(
			(m_fLeftEffort > 0)							&& 
			(m_fDesiredLeftPosition <= m_fLeftPosition))
			||
		(
			(m_fLeftEffort < 0)							&&
			(m_fDesiredLeftPosition >= m_fLeftPosition)
		)
		) 
	{
		m_fDesiredLeftEffort = 0.0f;
		bRet = true;
	}
	
	return bRet;
}

bool MoveMgr::CheckRightGoal() {
	bool bRet = false;

	if (
		(
			(m_fRightEffort > 0)							&& 
			(m_fDesiredRightPosition <= m_fRightPosition))
			||
		(
			(m_fRightEffort < 0)							&&
			(m_fDesiredRightPosition >= m_fRightPosition)
		)
		) 
	{
		m_fDesiredRightEffort = 0.0f;
		bRet = true;
	}
	
	return bRet;
}

bool MoveMgr::CheckPublisher() {
	bool bRet = true;

	if (!m_pPublisher) {
		ROS_ERROR("Publisher is NULL.");
		bRet = false;
	}

	return bRet;
}
