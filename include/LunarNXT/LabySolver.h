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

#ifndef LABYSOLVER_H
#define LABYSOLVER_H

#include "LunarNXT/LineFollower.h"
#include "LunarNXT/LineFinder.h"
#include "LunarNXT/Navigator.h"
#include "LunarNXT/LabyElement.h"

namespace Lunar_lib {

class LabySolver : public Mode {
public:
	LabySolver();
	virtual ~LabySolver();

	virtual void    UpdateColor(nxt_msgs::Color msg);
	virtual bool	SetMoveManager(MoveMgr** ppMoveManager);
	
private:
	enum State {
		INIT,
		NAVIGATE,
		LINEFINDER
	};

	LineFinder      m_LineFinder;
	Navigator       m_Navigator;
	
	Mode*           m_pCurrentMode;
	LabyElement*    m_pCurrentElement;
	
	State           m_State;

	nxt_msgs::Color m_ColorMsg;

	virtual void    Treat();
	
	void            NavLauncher(std::list<Map::Choice> choices);
	void            LineFinderLauncher();
	void            Compute();
};

};

#endif
