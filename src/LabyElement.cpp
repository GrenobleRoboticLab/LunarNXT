#include "lunarNXT/LabyElement.h"

using namespace Lunar_lib;

LabyElement::LabyElement() { ; }

LabyElement::LabyElement(LabyElement* prev) {
	this->ways[0] = prev;
	for (int i = 1; i < 4; i++) this->ways[i] = NULL;
	this->visited = 0;
}

LabyElement::~LabyElement() {
	for (int i = 1; i < 4; i++) delete this->ways[i];
}

Map::Choice LabyElement::getLeftChoice() {
	int tempVisit = this->visited;
	int ret = 3;
	int i = 0;

	while (ret == 3) {
		if (this->ways[(this->visited+i) % 4] != NULL && this->ways[visited+i]->getVisited() == 0)
			ret -= (4-i);
		else if (ways[(this->visited+i) % 4] == NULL) tempVisit++;
		i++;
	}
	this->visited = tempVisit;
	return (Map::Choice)(-ret);
}

int LabyElement::getVisited() { return this->visited; }
void LabyElement::addVisit() { this->visited++; }

void LabyElement::appendElement(int index) { this->ways[index] = new LabyElement(this); }
LabyElement* LabyElement::getElement(int index) { return this->ways[index]; }
