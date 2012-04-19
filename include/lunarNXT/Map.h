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

	bool appendElement(MapElement element);
	bool appendElement(MapElement element, unsigned int line, unsigned int col);
	
	std::vector<std::vector<MapElement> > getMap();
	void setOrientation(Cardinal orientation);
private:
	std::vector<std::vector<MapElement> > map;
        Cardinal orientation;

        unsigned int currentLine, currentCol;

	void col_push_back();
	void line_push_back();
	void col_push_front();
	void line_push_front();
};

#endif
