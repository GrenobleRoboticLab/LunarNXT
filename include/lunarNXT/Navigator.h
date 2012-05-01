#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include "lunarNXT/Mode.h"

class Navigator : public Mode {
private:
	void treat();

public:
	Navigator();
	Navigator(MoveMgr* mm);

};

#endif
