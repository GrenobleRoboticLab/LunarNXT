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

#ifndef MOVEMGR_H
#define MOVEMGR_H

/// INCLUDE FILES
#include "lunarNXT/Receptor.h"

#define BASE_EFFORT 0.73
#define MPI 3.14159265

/**
 * MoveMgr est la classe permettant la gestion des déplacements du LunarNXT.
 * Elle hérite de la classe Receptor contenant les méthodes virtuelles permettant de recevoir les informations des capteurs.
 */
class MoveMgr : public Receptor {
private:
        /// "publisher" permet l'envoi d'ordre aux moteurs.
        ros::Publisher* publisher;

        /// "hasGoal" permet de déterminer si le robot est en train d'executer une action finie.
        bool hasGoal;
	/// Les attributs "desired" permettent de définir et stocker les objectifs d'un mouvement fini.
        float desiredLeftPosition, desiredRightPosition;
        float desiredLeftEffort, desiredRightEffort;

        /// Les attributs "left" et "right" permettent de stocker les dernières informations connues des moteurs.
        float leftPosition, rightPosition;
        float leftEffort, rightEffort;

        /// "publish" permet la publication d'ordre aux moteurs.
        void publish(float leftEffort, float rightEffort);
        
        /**
	 * Les méthodes "check" effectuent des tests sur la position et l'effort de chaque moteur.
	 * Elles permettent de déterminer si un déplacement fini est terminé.
	 */
        void checkGoal();
        bool checkLeftGoal();
        bool checkRightGoal();

public:
        /**
	 * Constructeur.
	 */
        MoveMgr();
        /**
	 * Constructeur.
	 * @param pub Pointeur vers le Publisher communiquant avec le robot.
	 * @param leftName String permettant d'identifier le moteur de gauche.
	 * @param rightName String permettant d'identifier le moteur de droite.
	 */
        MoveMgr(ros::Publisher* pub, std::string leftName, std::string rightName);
        /**
	 * Destructeur.
	 */
		~MoveMgr();

        /**
	 * "linearMove" permet de définir un mouvement simple (avancer ou reculer) infini.
	 * @param effort Float indiquant l'effort à transmettre aux moteurs.
	 */
        void linearMove(float effort);
	/**
	 * "linearMove" permet de définir un mouvement simple (avancer ou reculer) fini.
	 * @param effort Float indiquant l'effort à transmettre aux moteurs.
	 * @param cm Int indiquant la distance (théoriquement en centimetre) à parcourir avant de finir le déplacement.
	 */
        void linearMove(float effort, int cm);

	/**
	 * Definit une rotation infinie vers la gauche autour du centre du robot.
	 * @param effort Float indiquant l'effort à transmettre aux moteurs.
	 */
        void turnLeft(float effort);
	/**
	 * Definit une rotation infinie vers la droite autour du centre du robot.
	 * @param effort Float indiquant l'effort à transmettre aux moteurs.
	 */
        void turnRight(float effort);
	/**
	 * Definit une rotation finie autour du centre du robot.
	 * @param effort Float indiquant l'effort à transmettre aux moteurs.
	 * @param rad Float indiquant l'angle (théoriquement en radiant) de la rotation.
	 */
        void turn(float effort, float rad);
	/**
	 * Definit une rotation finie autour d'une chenille (chenille gauche pour un angle >0) du robot.
	 * @param effort Float indiquant l'effort à transmettre aux moteurs.
	 * @param rad Float indiquant l'angle (théoriquement en radiant) de la rotation.
	 */
	void turnAround(float effort, float rad);

        /**
	 * Permet de stoper les moteurs.
	 */
        void stop();

        void updateMotors(sensor_msgs::JointState msg);
        void updateRange(nxt_msgs::Range msg);
        
	/**
	 * Retourne la dernière position connue du moteur de gauche.
	 */
        float getLeftPos();
	/**
	 * Retourne la dernière position connue du moteur de droite.
	 */
        float getRightPos();
	/**
	 * Indique si le robot est en cours de déplacement fini.
	 */
        bool hasGoalSet();
};

#endif

