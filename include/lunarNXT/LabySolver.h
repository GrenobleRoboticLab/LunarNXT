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

#include "lunarNXT/LineFollower.h"
#include "lunarNXT/LineFinder.h"
#include "lunarNXT/Navigator.h"
#include "lunarNXT/Map.h"

namespace lunar_lib {

/**
 * @remark: Work In Progress
 */
class LabySolver : public Mode {
private:
	// gestion des déplacements
	MoveMgr* mm;

	LineFinder* lfi;
	LineFollower* lfo;
	Navigator* nav;

	Map map;
	
	// traitement du mode
	void treat();	
	
public:
	// constructeurs et destructeur
	LabySolver();
	LabySolver(MoveMgr* mm);
	~LabySolver();

	void updateColor(nxt_msgs::Color msg);
};

};

#endif
