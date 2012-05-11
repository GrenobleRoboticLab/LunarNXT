#ifndef MODE_H
#define MODE_H

#include "lunarNXT/Receptor.h"

#include "lunarNXT/MoveMgr.h"

// Model de tout les modes.
// Un mode aura ces carracteristiques :
class Mode : public Receptor {
private:
	bool launched;
	bool initialized;
	MoveMgr* mm;

protected:
	// setter
	void setInitialized(bool init);
	
	// Fonction de traitement du mode (fonction virtuelle pure)
	virtual void treat() =0;
public:
	// constructeurs & destructeur
	Mode();
	Mode(MoveMgr* mm);
	MoveMgr* getMm();

	// methodes de lancement et d'arret du mode
	void launch();
	void unlaunch();

	 // getters
        bool isLaunched();
        bool isInitialized();
};

#endif
