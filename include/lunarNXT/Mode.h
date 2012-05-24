//=============================================================================
//
// This file is part of LunarNXT.
//
// LunarNXT is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// LunarNXT is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with LunarNXT. If not, see <http://www.gnu.org/licenses/>.
//
//=============================================================================

#ifndef MODE_H
#define MODE_H

#include "lunarNXT/Receptor.h"

#include "lunarNXT/MoveMgr.h"

namespace lunar_lib {

/**
 * Mode, herite de Receptor, représente un mode d'action pour le robot.
 * Un mode reçois les informations des capteurs de la part d'un EnvAnalyser, les traites et commande au MoveMgr.
 */
class Mode : public Receptor {
private:
	bool launched;
	bool initialized;
	MoveMgr* mm;

protected:
	/**
	 * Fixe la variable initialized permettant d'indiquer si le Mode a toutes les informations dont il a besoin pour fonctionner.
	 */
	void setInitialized(bool init);
	
	/**
	 * Methode principale du Mode, elle effectue tous les traitements d'informations.
	 */
	virtual void treat() =0;

public:
	/**
	 * Constructeur.
	 */
	Mode();
	/**
	 * Constructeur.
	 * @param mm Pointeur vers le MoveMgr en charge de gerer les deplacements.
	 */
	Mode(MoveMgr* mm);

	/**
	 * Retourne le pointeur vers le MoveMgr en charge de gerer les deplacements du mode.
	 */
	MoveMgr* getMm();

	/**
	 * Lance le fonctionnement du Mode.
	 */
	void launch();
	/**
	 * Arrete le fonctionnement du Mode.
	 */
	void unlaunch();

	/**
	 * Indique si le Mode est lance.
	 */
	bool isLaunched();
	/**
	 * Indique si le Mode a toutes les informations dont il a besoin pour fonctionner.
	 */
    bool isInitialized();
};

};

#endif
