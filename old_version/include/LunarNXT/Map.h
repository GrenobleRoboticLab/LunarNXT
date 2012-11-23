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

#ifndef MAP_H
#define MAP_H

#include <ros/ros.h>
#include <stdio.h>

namespace Lunar_lib {

/**
 * Classe représentant une carte, servant à localiser le robot
 * @remark: Work In Progress
 */
class Map {
public:
	Map();
	~Map();

	/**
	 * Choice représente un choix possible à un noeud de la carte
	 */
	enum Choice {
		RIGHT = -1,
		AHEAD = 0,
		LEFT = 1,
		BACK = 2
	};

	/**
	 * Cardinal : points cardinaux
	 */
	enum Cardinal {
                NORTH = 0,
		WEST = 1,
                SOUTH = 2,
                EAST = 3
	};

	/**
	 * Structure représentant un élément de la carte
	 * @deprecated
	 */
	struct MapElement {
                int ways[4];
		int weight;

                MapElement(Cardinal c) {
			weight = 0;
			for (int i = 0; i < 4; i++) { ways[i] = -1; }
			switch(c) {
				case NORTH:
					ways[SOUTH] = 0;
					break;
				case SOUTH:
					ways[NORTH] = 0;
					break;
				case EAST:
					ways[WEST] = 0;
					break;
				case WEST:
					ways[EAST] = 0;
					break;
			}
		}

		int countO() { return (ways[NORTH] + ways[WEST] + ways[SOUTH] + ways[EAST]); }
	};
	
	
	bool appendElement();
	bool appendElement(unsigned int line, unsigned int col);
	
	/**
	 * @return le chemin le plus a gauche (left = 1, ahead = 0, right = -1)
	 */
	Choice getLeftWay();
	
	/**
	 * @return une liste contennant les directions a prendre jusqu'au dernier noeud
	 */
	std::list<Choice> waysToLastNode();
	
	/**
	 * @return la carte dans son ensemble
	 */
	std::vector<std::vector<MapElement *> > getMap();
	
	/**
	 * Change l'orientation du robot
	 * @param orientation : la nouvelle orientation du robot
	 */
	void setOrientation(Cardinal orientation);

private:
	std::vector<std::vector<MapElement *> > map;
        Cardinal orientation;

        unsigned int currentLine, currentCol;

	void col_push_back();
	void line_push_back();
	void col_push_front();
	void line_push_front();
};

};

#endif
