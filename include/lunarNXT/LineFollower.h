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

#include "lunarNXT/Mode.h"

#include "lunarNXT/Map.h"

#include "nxt_msgs/Color.h"
#include "nxt_msgs/Range.h"

namespace lunar_lib {

/**
 * LineFollower, heritant de Mode, est une classe representant un mode du robot.
 * Cette classe permet de suivre une ligne.
 * @remark: ce Mode est independant est peut etre lance sans autre parametre d'initialisation que le MoveMgr en charge des deplacements du robot, la couleur traquée etant la première passee en parametre de updateColor une fois le Mode lance.
 */
class LineFollower : public Mode {
private:
	// Attributs
	nxt_msgs::Color colorMsg;
	nxt_msgs::Color colorLine;
	bool online;
	Map::Cardinal orientation;
	int count;
	// traitement du mode
	void treat();	
	
public:
	/**
	 * Constructeur.
	 */
	LineFollower();
	/**
	 * Constructeur.
	 * @param: mm Pointeur vers le MoveMgr en charge de gerer les deplacements.
	 */
	LineFollower(MoveMgr* mm);

	/**
	 * Methode virtuelle recevant les informations du capteur de couleur.
	 */
	void updateColor(nxt_msgs::Color msg);
	/**
	 * Permet d'indiquer la direction du robot sur la ligne.
	 */
	void setOrientation(Map::Cardinal orientation);
};

};

#endif
