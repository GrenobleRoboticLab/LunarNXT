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
	
	nxt_msgs::Color colorMsg;
	nxt_msgs::Color colorLine;
	nxt_msgs::Color colorPastille;
	bool online;

	void startLineFollower();
	void stopLineFollower();

public:
	Navigator();
	Navigator(MoveMgr* mm, LineFollower* lfo);
	void init(std::list<int> choices);
	void updateColor(nxt_msgs::Color msg);
	void setColorLine(nxt_msgs::Color color);
        void setColorPastille(nxt_msgs::Color color);
};

#endif
