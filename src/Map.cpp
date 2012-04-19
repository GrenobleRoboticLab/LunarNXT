#include "lunarNXT/Map.h"

Map::Map() { ; }
Map::~Map() { ; }

bool Map::appendElement(MapElement element) {
	switch (this->orientation) {
		case NORD:
			if (this->currentLine == 0)
				this->line_push_front();
			else 
				this->currentLine--;
			break;
		case SUD:
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
	return this->appendElement(element, this->currentLine, this->currentCol);
}

bool Map::appendElement(MapElement element, unsigned int line, unsigned int col) {
	if (this->map[line][col] == UNKNOW) {
		this->map[line][col] = element;
		return true;
	}
	return false;
}

std::vector<std::vector<Map::MapElement> > Map::getMap() { return this->map; }
void Map::setOrientation(Cardinal orientation) { this->orientation = orientation; }

void Map::col_push_back() {
	for (unsigned int i = 0; i < this->map.size(); i++)
		this->map[i].push_back(UNKNOW);
}

void Map::line_push_back() {
	this->map.push_back(std::vector<Map::MapElement>());
        for (unsigned int i = 0; i < this->map[0].size(); i++) 
                this->map.back().push_back(UNKNOW);
}

void Map::col_push_front() {
        for (unsigned int i = 0; i < this->map.size(); i++) 
                this->map[i].insert(this->map[i].begin(), UNKNOW);
}

void Map::line_push_front() {
        this->map.insert(this->map.begin(), std::vector<Map::MapElement>());
        for (unsigned int i = 0; i < this->map[1].size(); i++)
                this->map.front().push_back(UNKNOW);

}

