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

#ifndef LINEFINDER_H
#define LINEFINDER_H

#include "LunarNXT/Mode.h"
#include "LunarNXT/LabyElement.h"

#include "nxt_msgs/Color.h"

namespace Lunar_lib {

class LineFinder : public Mode {
public:
	LineFinder();
	virtual ~LineFinder() { ; }

   	virtual void	UpdateColor(nxt_msgs::Color msg);
    	void 		Init(LabyElement* element);

private:
	LabyElement*	m_pLabyElement;
	nxt_msgs::Color	m_ColorMsg;

	int		m_nState;
	bool		m_bLineNotFound;
	float		m_fLPos,
			m_fRPos;

	virtual void	Treat();
	bool		CheckDist(int nDist);
	bool		CheckLabyElement();
};

};

#endif
