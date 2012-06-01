#include "lunarNXT/LineFinder.h"
#include "lunarNXT/Tools.h"

using namespace Lunar_lib;

LineFinder::LineFinder() : Mode() { ; }

LineFinder::LineFinder(MoveMgr* mm) : Mode(mm) {
	this->state = 0;
}

void LineFinder::updateColor(nxt_msgs::Color msg) { 
	this->colorMsg = msg;
	if (this->isLaunched()) {
		this->treat();
	}
}

void LineFinder::treat() {
	if (Tools::is_line_color(colorMsg)) {
		if(this->state < 3) {
			this->element->appendElement(this->state+1);	
			switch(this->state) {
			case 0:
				this->getMm()->turnLeft(BASE_EFFORT);
				this->state = 3;
				break;
			case 1:
				this->getMm()->linearMove(BASE_EFFORT);
				this->state = 3;
				break;
			case 2:
				this->getMm()->turnRight(BASE_EFFORT);
				this->state = 3;
				break;	
			}
		}
	}
	else if(Tools::is_pastille_color(colorMsg)) {
		this->lineNotFound = false;
		switch(this->state) {
		case 0:
			this->leftPosition = this->getMm()->getLeftPos();
			this->rightPosition = this->getMm()->getRightPos();
			this->getMm()->turnLeft(BASE_EFFORT);
			break;
		case 1:
			this->leftPosition = this->getMm()->getLeftPos();
			this->rightPosition = this->getMm()->getRightPos();
			this->getMm()->linearMove(BASE_EFFORT);
			break;
		case 2:
			this->leftPosition = this->getMm()->getLeftPos();
			this->rightPosition = this->getMm()->getRightPos();
			this->getMm()->turnRight(BASE_EFFORT);
			break;
		case 3:
			this->unlaunch();
			break;

		default: break;
		}
	}
	else if(Tools::is_ground_color(colorMsg) && !lineNotFound && checkDist(1)){
		switch(this->state) {
		case 0:
			this->state++;
			//on pourra supprimer la ligne ci dessous en faisant le test de Linenotfound sur element state[i];	
			this->lineNotFound = true;
			this->getMm()->turnRight(BASE_EFFORT);
			break;
		case 1:
			this->state++;			
			this->lineNotFound = true;
			this->getMm()->linearMove(-BASE_EFFORT);
			break;
		case 2:
			this->state++;
			this->lineNotFound = true;
			this->getMm()->turnLeft(BASE_EFFORT);
			break;
		default: 
			break;
		}
	}

}

bool LineFinder::checkDist(int dist) {
	if (	(this->getMm()->getLeftPos() - this->leftPosition > dist) || 
		(this->getMm()->getRightPos() - this->rightPosition > dist)) {
		return true;
	}
	return false;
}

void LineFinder::init(LabyElement* element) { 
	this->element = element;
	this->setInitialized(true);
}
