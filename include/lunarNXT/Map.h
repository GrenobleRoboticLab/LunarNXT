#ifndef MAP_H
#define MAP_H

#include <ros/ros.h>
#include <stdio.h>

class Map {
public:
	Map();
	~Map();

	enum MapElement {
                UNKNOW,
                END,
                CROSS,
                ROAD
        };
	
	enum Cardinal {
                NORD,
                SUD,
                EAST,
                WEST
        };

	void appendElement(MapElement element);
	std::vector<std::vector<MapElement> > getMap();
	void setOrientation(Cardinal orientation);
private:
	std::vector<std::vector<MapElement> > map;
        Cardinal orientation;

        unsigned int currentLine, currentCol;
};

#endif
