#include "lunarNXT/Map.h"

Map::Map() { 
	this->orientation = EAST;
	this->map = std::vector<std::vector<MapElement *> >();
}
Map::~Map() { ; }

bool Map::appendElement() {
	switch (this->orientation) {
		case NORTH:
			if (this->currentLine == 0)
				this->line_push_front();
			else 
				this->currentLine--;
			break;
		case SOUTH:
			this->currentLine++;
			if (this->currentLine == this->map.size())
				this->line_push_back();
			break;
		case EAST:
			this->currentCol++;
			if (this->currentCol == this->map[0].size())
				this->col_push_back();
			break;
		case WEST:
			if (this->currentCol == 0)
				this->col_push_front();
			else
				this->currentCol--;
			break;
	}
	return this->appendElement(this->currentLine, this->currentCol);
}

bool Map::appendElement(unsigned int line, unsigned int col) {
	if (this->map[line][col] == NULL) {
		this->map[line][col] = new MapElement(this->orientation);
		return true;
	}
	else this->map[line][col]->ways[(this->orientation + 2) %4] = 0;
	return false;
}

std::vector<std::vector<Map::MapElement *> > Map::getMap() { return this->map; }

void Map::setOrientation(Cardinal orientation) { this->orientation = orientation; }

void Map::col_push_back() {
	for (unsigned int i = 0; i < this->map.size(); i++)
		this->map[i].push_back(NULL);
}

void Map::line_push_back() {
	this->map.push_back(std::vector<MapElement *>());
        for (unsigned int i = 0; i < this->map[0].size(); i++) 
                this->map.back().push_back(NULL);
}

void Map::col_push_front() {
        for (unsigned int i = 0; i < this->map.size(); i++) 
                this->map[i].insert(this->map[i].begin(), NULL);
}

void Map::line_push_front() {
        this->map.insert(this->map.begin(), std::vector<MapElement *>());
        for (unsigned int i = 0; i < this->map[1].size(); i++)
                this->map.front().push_back(NULL);

}

int Map::getLeftWay() {
	MapElement* current = this->map[this->currentLine][this->currentCol];
	int ret = 2;
	int i = this->orientation + 1;
	
	while (ret == 2 || i < this->orientation + 4) {
        	if (current->ways[i%4] == 1) ret = -(i - this->orientation - 2);
        	i++;
    	}
		
	return ret;
}

std::list<int> Map::waysToLastNode() {
	std::list<int> ret = std::list<int>();
	
	unsigned int tempLine = this->currentLine;
        unsigned int tempCol = this->currentCol;

	Cardinal tempOrientation = this->orientation;
	MapElement* tempElement = this->map[tempLine][tempCol];
		
	while (tempElement->countO() <= 0) {
		for (int i = tempOrientation + 1; i < tempOrientation + 4; i++)
			if (tempElement->ways[i%4] == 0)
				ret.push_back(i - tempOrientation - 2);
		
		tempElement->ways[(tempOrientation + 2) % 4] = -1;
		tempOrientation = (Cardinal)((tempOrientation - ret.back()) % 4);
	
		switch (tempOrientation) {
			case NORTH:
				tempLine--;
				break;
			case WEST:
				tempCol--;
				break;
			case SOUTH:
				tempLine++;
				break;
			case EAST:
				tempCol++;
				break;
		}
		tempElement = this->map[tempLine][tempCol];
	}

	return ret;
}
