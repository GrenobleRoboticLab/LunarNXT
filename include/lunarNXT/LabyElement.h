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

namespace Lunar_lib {

/**
 * LabyElement represente un etat au sein d'un labyrinthe.
 * Il est identifie et positionne par ses chemins (voisins direct)
 */
class LabyElement {
private:
    LabyElement* ways[4];
	int visited;

public:
	/**
	 * Constructeur.
	 */
	 LabyElement();
	/**
	 * Constructeur.
	 * @param: prev LabyElement precedant celui en creation dans le parcour effectue par le robot.
	 */
	LabyElement(LabyElement* prev);
	/**
	 * Destructeur.
	 */
	~LabyElement();

	/**
	 * Permet de prendre la premiere direction de gauche encore inexploree.
	 * @return: la direction à prendre par le robot
	 */
	Map::Choice getLeftChoice(LabyElement* current);

	/**
	 * Ajoute un LabyElement au tableau de chemin de l'objet.
	 * @param index represente la direction du chemin : 1 => a gauche, 2 => en face, 3 => a droite.
	 * @remark: la valeur 0 modifierait le LabyElement precedant dans l'arbre, sa modification peu entraîner fuite de memoire ou echec du mode en cours.
	 */
	void appendElement(int index);
	
	LabyElement* getElement(int index);

	/**
	 * Incremente le compteur de visite du noeud.
	 */
	void addVisit();
	/**
	 * @return: le nombre de passage sur le noeud.
	 */
	int getVisited();
};

};

#endif
