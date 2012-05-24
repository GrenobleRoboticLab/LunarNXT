#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include "nxt_msgs/Color.h"
#include "lunarNXT/LineFollower.h"

// Mode de deplacement sur un environement connu
class Navigator : public Mode {
private:

	LineFollower* lfo;
	void treat();
	std::list<Map::Choice> choices;
	
	nxt_msgs::Color colorMsg;
	nxt_msgs::Color colorLine;
	nxt_msgs::Color colorPastille;
	bool online;
	
	float leftPos;
	float rightPos;

	void startLineFollower();
	void stopLineFollower();
	void applyChoice();

	bool checkDist(float a, float b);

public:
	Navigator();
	Navigator(MoveMgr* mm, LineFollower* lfo);
	void init(std::list<Map::Choice> choices);
	void updateColor(nxt_msgs::Color msg);
	void setColorLine(nxt_msgs::Color color);
        void setColorPastille(nxt_msgs::Color color);
};

#endif
