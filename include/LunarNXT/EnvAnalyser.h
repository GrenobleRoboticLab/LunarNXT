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

#ifndef ENVANALYSER_H
#define ENVANALYSER_H

#include "sensor_msgs/JointState.h"
#include "nxt_msgs/Contact.h"
#include "nxt_msgs/Color.h"
#include "nxt_msgs/Range.h"

#include "LunarNXT/Order.h"

#include "LunarNXT/MoveMgr.h"
#include "LunarNXT/Mode.h"

namespace Lunar_lib {

class EnvAnalyser {
public:
	EnvAnalyser();
	~EnvAnalyser();

	bool		Init(ros::Publisher* pPublisher, const std::string & sLMotorName, const std::string & sRMotorName);
	
	void		MotorCallback(const sensor_msgs::JointState::ConstPtr& msg);
	void		RightTouchCallback(const nxt_msgs::Contact::ConstPtr& msg);
	void		LeftTouchCallback(const nxt_msgs::Contact::ConstPtr& msg);
	void		ColorCallback(const nxt_msgs::Color::ConstPtr& msg);
	void		UltrasonicCallback(const nxt_msgs::Range::ConstPtr& msg);
	void		UiCallback(const LunarNXT::Order::ConstPtr& msg);

private:
	MoveMgr*	m_pMoveManager;
	Mode*		m_pMode;

	void		LaunchMode(int nEnum);
	void		KillMode();

	void		ReleaseMode();
	void		ReleaseMoveManager();

	bool		CheckMoveManager();
	bool		CheckMode();
};

};
#endif
