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
#include "lunarNXT/LabyElement.h"

namespace Lunar_lib {

/**
 * LabySolver est un Mode permettant au robot de resoudre un labyrinthe.
 * @remark: Work In Progress
 */
class LabySolver : public Mode {
private:
	enum State {
		INIT,
		NAVIGATE,
		LINEFINDER,
		COMPUTE
	};

	LineFinder* lfi;
	LineFollower* lfo;
	Navigator* nav;
	
	Mode* currentMode;
	LabyElement* currentElement;
	
	State state;

	nxt_msgs::Color colorMsg;

	// traitement du mode
	void treat();
	
	void navLauncher(std::list<Map::Choice> choices);
	void lfiLauncher();
	void computeLauncher();

public:
	/**
	 * Constructeur.
	 */
	LabySolver();
	/**
	 * Constructeur.
	 * @param: mm Pointeur vers le MoveMgr en charge de gerer les deplacements.
	 */
	LabySolver(MoveMgr* mm);
	/**
	 * Destructeur.
	 */
	~LabySolver();

	/**
	 * Methode virtuelle recevant les informations du capteur de couleur.
	 */
	void updateColor(nxt_msgs::Color msg);
};

};

#endif
