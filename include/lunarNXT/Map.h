#ifndef MAP_H
#define MAP_H

#include <ros/ros.h>
#include <stdio.h>

class Map {
public:
	Map();
	~Map();
	
	enum Cardinal {
                NORD = 0,
		WEST = 1,
                SUD = 2,
                EAST = 3
        };

	struct MapElement {
                int ways[4];
		int weight;
                MapElement(Cardinal c) {
			weight = 0;
			for (int i = 0; i < 4; i++) { ways[i] = -1; }
			switch(c) {
				case NORD:
					ways[SUD] = 0;
					break;
				case SUD:
					ways[NORD] = 0;
					break;
				case EAST:
					ways[WEST] = 0;
					break;
				case WEST:
					ways[EAST] = 0;
					break;
			}
        	}
		int countO() { return (ways[NORD] + ways[WEST] + ways[SUD] + ways[EAST]); }
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
