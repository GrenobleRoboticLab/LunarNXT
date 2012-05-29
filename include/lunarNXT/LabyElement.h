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
#include "lunarNXT/Tools.h"
#include "lunarNXT/Map.h"

namespace lunar_lib {

class LabyElement {
private:
        LabyElement* ways[4];
	int visited;

public:
        LabyElement(LabyElement* prev);
        LabyElement();
        ~LabyElement();

	Map::Choice getLeftChoice();

	void appendElement(int index);
	LabyElement* getElement(int index);

	void addVisit();
	int getVisited();
};

};

#endif
