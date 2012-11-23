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

#ifndef RECEPTOR_H
#define RECEPTOR_H

#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "nxt_msgs/Color.h"
#include "nxt_msgs/Range.h"
#include "nxt_msgs/Contact.h"

namespace Lunar_lib {

class Receptor {
public:
	Receptor();
	Receptor(const std::string & sLMotorName, const std::string & sRMotorName);

	virtual ~Receptor() { ; }

	const std::string&		GetNameLeftMotor();
	const std::string&		GetNameRightMotor();
	
	virtual void			UpdateRightTouch(nxt_msgs::Contact msg);
	virtual void			UpdateLeftTouch(nxt_msgs::Contact msg);
	virtual void			UpdateRange(nxt_msgs::Range msg);
	virtual void			UpdateColor(nxt_msgs::Color msg);
	virtual void			UpdateMotors(sensor_msgs::JointState msg);

protected:
	void					SetMotorsName(const std::string & sLMotorName, const std::string & sRMotorName);
	void					SetLMotorName(const std::string & sLMotorName);
	void					SetRMotorName(const std::string & sRMotorName);

private:
	std::string				m_sLMotorName,
							m_sRMotorName;
};

};

#endif
