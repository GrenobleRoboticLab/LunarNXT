#include "lunarNXT/MapElement.h"

using namespace lunar_lib;

MapElement::MapElement() { ; }

MapElement::MapElement(Tools::MVector position) { 
	this->position = position; 
}

MapElement::MapElement(Tools::MVector position, MapElement* prevMapElement) { 
	this->position = position;
	this->prev = prevMapElement;
}

MapElement::~MapElement() { ; }

Tools::MVector MapElement::getPosition() { return this->position; }
MapElement* MapElement::getPrevMapElement() { return this->prev; }
float MapElement::getX() { return this->position.getX(); }
float MapElement::getY() { return this->position.getY(); }


void MapElement::setPrevMapElement(MapElement* prevMapElement) { this->prev = prevMapElement; }

