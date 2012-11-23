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

#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include "nxt_msgs/Color.h"
#include "LunarNXT/LineFollower.h"

namespace Lunar_lib {

class Navigator : public Mode {
public:
	Navigator();
	virtual ~Navigator() { ; }

	virtual bool            SetMoveManager(MoveMgr** ppMoveManager);
	void			Init(std::list<Map::Choice> choices);
	
	virtual void		UpdateColor(nxt_msgs::Color msg);
	
	void 			SetColorLine(nxt_msgs::Color color);
	void 			SetColorPastille(nxt_msgs::Color color);

private:
	LineFollower		m_LineFollower;
	std::list<Map::Choice>	m_lChoices;
	nxt_msgs::Color		m_ColorMsg;
	bool			m_bOnline;
	float			m_fLPos,
				m_fRPos;
	
	virtual void		Treat();

	void			StartLineFollower();
	void			StopLineFollower();
	void			ApplyChoice();

	bool			CheckDist(float fA, float fB);
};

};

#endif
