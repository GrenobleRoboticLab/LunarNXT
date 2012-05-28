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

#ifndef MAPELEMENT_H
#define MAPELEMENT_H

#include <ros/ros.h>
#include <stdio.h>
#include "lunarNXT/Tools.h"

namespace lunar_lib {

class MapElement {
private:
	MapElement* prev;
	Tools::MVector position;
	int weight;

public:
	MapElement();
	MapElement(Tools::MVector position);
	MapElement(Tools::MVector position, MapElement* prevMapElement);
	~MapElement();

	Tools::MVector getPosition();
	MapElement* getPrevMapElement();

	float getX();
	float getY();

	void setPrevMapElement(MapElement* prevMapElement);
};

};

#endif
