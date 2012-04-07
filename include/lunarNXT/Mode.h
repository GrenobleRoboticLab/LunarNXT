#ifndef MODE_H
#define MODE_H

#include "lunarNXT/MoveMgr.h"

// Model de tout les modes.
// Un mode aura ces carracteristiques
class Mode {
private:
	bool launched;
	bool initialized;

protected:
	MoveMgr* mm;
	bool isLaunched();
	bool isInitialized();
	void setInitialized(bool init);
	virtual void treat() =0;
public:
	Mode();
	Mode(MoveMgr* mm);
	virtual ~Mode();

	void launch();
	void unlaunch();
};

#endif
