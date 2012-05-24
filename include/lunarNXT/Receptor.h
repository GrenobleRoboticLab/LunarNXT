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

#ifndef RECEPTOR_H
#define RECEPTOR_H

#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "nxt_msgs/Color.h"
#include "nxt_msgs/Range.h"
#include "nxt_msgs/Contact.h"

namespace lunar_lib {

/**
 * Receptor est une classe abstraite declarant les methodes de reception d'information de la part des capteurs.
 * Les informations recues sont prealablement traitees par l'EnvAnalyser.
 */
class Receptor {
private:
	/// Motors name
	std::string nameLeftMotor;
	std::string nameRightMotor;

public:
	/**
	 * Constructeur.
	 */
	Receptor();
	/*
	 * Constructeur.
	 * @param nameLeftMotor String permettant d'identifier le moteur de gauche.
	 * @param nameRightMotor String permettant d'identifier le moteur de droite.
	 */
	Receptor(std::string nameLeftMotor, std::string nameRightMotor);

	/**
	 * Retourne le nom du moteur de gauche.
	 */
	std::string getNameLeftMotor();
	/**
	 * Retourne le nom du moteur de droite.
	 */
	std::string getNameRightMotor();

	/**
	 * Methode virtuelle recevant les informations du capteur de contact de droite.
	 */
	virtual void updateRightTouch(nxt_msgs::Contact msg);
	/**
	 * Methode virtuelle recevant les informations du capteur de contact de gauche.
	 */
	virtual void updateLeftTouch(nxt_msgs::Contact msg);
	
	/**
	 * Methode virtuelle recevant les informations du capteur ultrasonique de distance.
	 */
	virtual void updateRange(nxt_msgs::Range msg);
	
	/**
	 * Methode virtuelle recevant les informations du capteur de couleur.
	 */
	virtual void updateColor(nxt_msgs::Color msg);
	
	/**
	 * Methode virtuelle recevant les informations des moteurs.
	 */
	virtual void updateMotors(sensor_msgs::JointState msg);
};

};

#endif
