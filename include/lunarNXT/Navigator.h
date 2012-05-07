#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include "nxt_msgs/Color.h"
#include "lunarNXT/LineFollower.h"

// Mode de deplacement sur un environement connu
class Navigator : public Mode {
private:

	LineFollower* lfo;
	void treat();
	std::list<int> choices;

public:
	Navigator();
	Navigator(MoveMgr* mm, LineFollower* lfo);
	void init(std::list<int> choices);
	void updateColor(nxt_msgs::Color msg);
};

#endif
