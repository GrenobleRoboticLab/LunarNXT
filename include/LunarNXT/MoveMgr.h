//=============================================================================
//
// This file is part of LunarNXT.
//
// LunarNXT is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// LunarNXT is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with LunarNXT. If not, see <http://www.gnu.org/licenses/>.
//
//=============================================================================

#ifndef MOVEMGR_H
#define MOVEMGR_H

#include "LunarNXT/Receptor.h"

#define BASE_EFFORT 0.73
#define MPI 3.14159265

namespace Lunar_lib {

class MoveMgr 
	: public Receptor
{
public:
	MoveMgr();
	MoveMgr(const std::string & sLMotorName, const std::string & sRMotorName);
	~MoveMgr();

	bool			Init(ros::Publisher* pPublisher);

	void			LinearMove(float fEffort);
	void			LinearMove(float fEffort, float fCM);
	
	void			TurnLeft(float fEffort);
	void			TurnRight(float fEffort);
	void			Turn(float fEffort, float fRad);

	void			TurnAroundLeft(float fEffort);
	void			TurnAroundRight(float fEffort);
	void			TurnAround(float fEffort, float fRad);

	void			Stop();

	void			UpdateMotors(sensor_msgs::JointState msg);
	void			UpdateRange(nxt_msgs::Range msg);
        
	float			GetLeftPos() const;
	float			GetRightPos() const;
	bool			HasGoalSet() const;

private:
	ros::Publisher*	m_pPublisher;

	bool			m_bHasGoal;
	
	float			m_fDesiredLeftPosition,
					m_fDesiredRightPosition,
					m_fDesiredLeftEffort,
					m_fDesiredRightEffort,
					m_fLeftPosition,
					m_fRightPosition,
					m_fLeftEffort,
					m_fRightEffort;

	void			Publish(float fLeftEffort, float fRightEffort);
					
	void			CheckGoal();
	bool			CheckLeftGoal();
	bool			CheckRightGoal();

	bool			CheckPublisher();
};

};

#endif
