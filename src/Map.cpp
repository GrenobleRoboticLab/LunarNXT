#include "lunarNXT/Map.h"

Map::Map() { 
	this->orientation = EAST;
	this->map = std::vector<std::vector<MapElement *> >();
}
Map::~Map() { ; }

bool Map::appendElement() {
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
	return this->appendElement(this->currentLine, this->currentCol);
}

bool Map::appendElement(unsigned int line, unsigned int col) {
	if (this->map[line][col] == NULL) {
		this->map[line][col] = new MapElement(this->orientation);
		return true;
	}
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

int Map::getLeftChoice() {
	MapElement* current = this->map[this->currentLine][this->currentCol];
	int ret = 0;
	switch (this->orientation) {
		case NORD:
			if (current->west_weight == 1) ret = 1;
			else if (current->nord_weight == 1) ret = 0;
			else if (current->east_weight == 1) ret = -1;
			else ret = 2;
			break;
		case SUD:
                        if (current->east_weight == 1) ret = 1;
                        else if (current->sud_weight == 1) ret = 0;
                        else if (current->west_weight == 1) ret = -1;
                        else ret = 2;
			break;
		case EAST:
                        if (current->nord_weight == 1) ret = 1;
                        else if (current->east_weight == 1) ret = 0;
                        else if (current->sud_weight == 1) ret = -1;
                        else ret = 2;
			break;
		case WEST:
                        if (current->sud_weight == 1) ret = 1;
                        else if (current->west_weight == 1) ret = 0;
                        else if (current->nord_weight == 1) ret = -1;
                        else ret = 2;
			break;
	}
	return ret;
}

std::list<int> Map::choicesToLastNode() {
	std::list<int> ret = std::list<int>();
	// MapElement* current = this->map[this->currentLine][this->currentCol];
	return ret;
}

void Map::getLastEntryToNode(int line, int col, std::list<int>* ret, Cardinal card) {

}
