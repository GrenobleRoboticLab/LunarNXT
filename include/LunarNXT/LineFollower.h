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

#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H

#include "LunarNXT/Mode.h"

#include "LunarNXT/Map.h"

#include "nxt_msgs/Color.h"
#include "nxt_msgs/Range.h"

namespace Lunar_lib {

class LineFollower : public Mode {	
public:
	LineFollower();
	LineFollower(MoveMgr* mm);
	
	virtual void	UpdateColor(nxt_msgs::Color msg);
	void 		SetOrientation(Map::Cardinal orientation);
	
private:
	nxt_msgs::Color m_ColorMsg;
	bool		m_bOnline;
	Map::Cardinal	m_wOrientation;
	int		m_nCount;
	
	virtual void	Treat();
};

};

#endif
