#ifndef LABYSOLVER_H
#define LABYSOLVER_H

#include "lunarNXT/LineFollower.h"
#include "lunarNXT/LineFinder.h"
#include "lunarNXT/Navigator.h"
#include "lunarNXT/Map.h"

class LabySolver : public Mode {
private:
	// gestion des déplacements
	MoveMgr* mm;

	LineFinder* lfi;
	LineFollower* lfo;
	Navigator* nav;

	Map map;
	
	// traitement du mode
	void treat();	
	
public:
	// constructeurs et destructeur
	LabySolver();
	LabySolver(MoveMgr* mm);
	~LabySolver();

	void updateColor(nxt_msgs::Color msg);
};

#endif
