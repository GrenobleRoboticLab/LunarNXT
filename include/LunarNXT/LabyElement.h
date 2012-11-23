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

#ifndef LABYELEMENT_H
#define LABYELEMENT_H

#include <ros/ros.h>
#include <stdio.h>
#include "LunarNXT/Tools.h"
#include "LunarNXT/Map.h"

namespace Lunar_lib {

class LabyElement {
public:
    LabyElement();
	~LabyElement();

	Map::Choice     GetLeftChoice(LabyElement** ppCurrent);

	void            AppendElement(int index);
	void            AddVisit();
	
	void            SetPrev(LabyElement* pPrev);
	
	LabyElement*    GetElement(int index);
	int             GetVisited();
	
private:
    LabyElement*    m_pWays[4];
	int             m_nVisiteCount;
};

};

#endif
