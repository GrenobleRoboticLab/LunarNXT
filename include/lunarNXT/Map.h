#ifndef MAP_H
#define MAP_H

#include <ros/ros.h>
#include <stdio.h>

class Map {
public:
	Map();
	~Map();
	
	enum Cardinal {
                NORD,
                SUD,
                EAST,
                WEST
        };

	struct MapElement {
                int nord_weight, sud_weight, east_weight, west_weight;
                MapElement(Cardinal c) {
			nord_weight = sud_weight = east_weight = west_weight = -1;
			switch(c) {
				case NORD:
					sud_weight = 0;
					break;
				case SUD:
					nord_weight = 0;
					break;
				case EAST:
					west_weight = 0;
					break;
				case WEST:
					east_weight = 0;
					break;
			}
        	}
        };


	bool appendElement();
	bool appendElement(unsigned int line, unsigned int col);
	
	// retourne le chemin le plus a gauche (left = 1, ahead = 0, right = -1)
	int getLeftChoice();
	
	// retourne une liste contennant les directions a prendre jusqu'au dernier noeud
	std::list<int> choicesToLastNode();
	
	std::vector<std::vector<MapElement *> > getMap();
	void setOrientation(Cardinal orientation);
private:
	std::vector<std::vector<MapElement *> > map;
        Cardinal orientation;

        unsigned int currentLine, currentCol;

	void col_push_back();
	void line_push_back();
	void col_push_front();
	void line_push_front();

	void getLastEntryToNode(int line, int col, std::list<int>* ret, Cardinal card);
};

#endif
