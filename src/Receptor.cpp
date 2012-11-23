#include "LunarNXT/Receptor.h"

using namespace Lunar_lib;

Receptor::Receptor() { ; }

Receptor::Receptor(const std::string & sLMotorName, const std::string & sRMotorName) {
	m_sLMotorName	= sLMotorName;
	m_sRMotorName	= sRMotorName;
}

const std::string& Receptor::GetNameLeftMotor()	{ return m_sLMotorName; }
const std::string& Receptor::GetNameRightMotor()	{ return m_sRMotorName; }

void Receptor::UpdateRightTouch(nxt_msgs::Contact msg)		{ ; }
void Receptor::UpdateLeftTouch(nxt_msgs::Contact msg)		{ ; }
void Receptor::UpdateRange(nxt_msgs::Range msg)				{ ; }
void Receptor::UpdateColor(nxt_msgs::Color msg)				{ ; }
void Receptor::UpdateMotors(sensor_msgs::JointState msg)	{ ; }

void Receptor::SetMotorsName(const std::string & sLMotorName, const std::string & sRMotorName) {
	SetLMotorName(sLMotorName);
	SetRMotorName(sRMotorName);
}

void Receptor::SetLMotorName(const std::string & sLMotorName) { m_sLMotorName = sLMotorName; }
void Receptor::SetRMotorName(const std::string & sRMotorName) { m_sRMotorName = sRMotorName; }
