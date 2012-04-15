#include "lunarNXT/Map.h"

Map::Map() { ; }
Map::~Map() { ; }

void Map::appendElement(MapElement element) {
	switch (this->orientation) {
		case NORD:
			if (this->currentLine == 0) {
				this->map.insert(this->map.begin(), std::vector<MapElement>());
				for (unsigned int i = 0; i < this->map[1].size(); i++) {
					if (i == this->currentCol)
						this->map[this->currentLine].push_back(element);
					else
						this->map[this->currentLine].push_back(UNKNOW);
				}
			}
			else {
				this->currentLine--;
				this->map[this->currentLine][this->currentCol] = element;
			}
			break;
		case SUD:
			this->currentLine++;
			if (this->currentLine == this->map.size()) {
				this->map.push_back(std::vector<MapElement>());
				for (unsigned int i = 0; i < this->map[1].size(); i++) {
                                        if (i == this->currentCol)
                                                this->map[this->currentLine].push_back(element);
                                        else
                                                this->map[this->currentLine].push_back(UNKNOW);
                                }
			}
			else {
                                this->map[this->currentLine][this->currentCol] = element;
                        }
			break;
		case EAST:
			this->currentCol++;
			if (this->currentCol == this->map[0].size()) {
				for (unsigned int i = 0; i < this->map.size(); i++) {
					if (i == this->currentLine)
						this->map[i].push_back(element);
					else
						this->map[i].push_back(UNKNOW);
				}
			}
			else {
				this->map[this->currentLine][this->currentCol] = element;
			}
			break;
		case WEST:
			if (this->currentCol == 0) {
				for (unsigned int i = 0; i < this->map.size(); i++) {
					if (i == this->currentLine)
						this->map[i].insert(this->map[i].begin(), element);
					else
						this->map[i].insert(this->map[i].begin(), UNKNOW);
				}
			}
			else {
				this->currentCol--;
				this->map[this->currentLine][this->currentCol] = element;
			}
			break;
	}
}

std::vector<std::vector<Map::MapElement> > Map::getMap() { return this->map; }
void Map::setOrientation(Cardinal orientation) { this->orientation = orientation; }
