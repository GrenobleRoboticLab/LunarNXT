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

#include "lunarNXT/Mode.h"
#include "lunarNXT/Map.h"

#include "nxt_msgs/Color.h"

namespace lunar_lib {

/**
 * @remark: Work In Progress
 */
class LineFinder : public Mode {
private:
	void treat();
public:
	// constructeurs et destructeur
	LineFinder();
	LineFinder(MoveMgr* mm);

};

};

#endif
