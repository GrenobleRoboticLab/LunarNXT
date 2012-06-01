#include "lunarNXT/Tools.h"

using namespace Tools;

bool Tools::compare_color(const nxt_msgs::Color &c1, const nxt_msgs::Color &c2) {
	return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b);
}


bool Tools::is_line_color(const nxt_msgs::Color &c) {
	return (c.r == 0 && c.g == 0 && c.b == 0);
}

bool Tools::is_pastille_color(const nxt_msgs::Color &c) {
	return (c.r == 1 && c.g == 0 && c.b == 1);
}

bool Tools::is_ground_color(const nxt_msgs::Color &c) {
	return (c.r == 1 && c.g == 1 && c.b == 1);
}


MVector::MVector() : x(.0f), y(.0f) {}
MVector::MVector(float x, float y) : x(x), y(y) {}

float MVector::getX()             { return this->x; }
float MVector::getY()             { return this->y; }

void MVector::setX(float x)             { this->x = x; }
void MVector::setY(float y)             { this->y = y; }
void MVector::setVector(float x, float y) {
        this->setX(x);
        this->setY(y);
}
