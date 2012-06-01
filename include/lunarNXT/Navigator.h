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
#include "lunarNXT/LineFollower.h"

namespace Lunar_lib {

/**
 * Navigator, heritant de Mode, est une classe representant un mode du robot.
 * Cette classe permet a partir d'une liste de choix de se deplacer d'un noeud a un autre sur une carte ou un labyrinthe.
 * @remark Les noeuds doivent etre relies par une ligne, ceci permettant d'aller de l'un a l'autre en utilisant le mode LineFollower.
 */
class Navigator : public Mode {
private:
	LineFollower* lfo;

	void treat();
	std::list<Map::Choice> choices;
	
	nxt_msgs::Color colorMsg;

	bool online;
	
	float leftPos;
	float rightPos;

	void startLineFollower();
	void stopLineFollower();
	void applyChoice();

	bool checkDist(float a, float b);

public:
	/**
	 * Constructeur.
	 */
	Navigator();
	/**
	 * Constructeur.
	 * @param mm Pointeur vers le MoveMgr en charge de gerer les deplacements.
	 * @param lfo Pointeur vers le LineFollower en charge des deplacement de noeud a noeud
	 */
	Navigator(MoveMgr* mm, LineFollower* lfo);
	
	/**
	 * Initialise le mode.
	 * @param choices Liste des choix a prendre a chaque noeud
	 */
	void init(std::list<Map::Choice> choices);
	
	/**
	 * Methode virtuelle recevant les informations du capteur de couleur.
	 */
	void updateColor(nxt_msgs::Color msg);
	
	/**
	 * Fixe la couleur de la ligne.
	 */
	void setColorLine(nxt_msgs::Color color);
	/**
	 * Fixe la couleur de la pastille.
	 */
    void setColorPastille(nxt_msgs::Color color);
};

};

#endif
