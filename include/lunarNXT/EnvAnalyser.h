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

#ifndef ENVANALYSER_H
#define ENVANALYSER_H

#include <pthread.h>
#include "sensor_msgs/JointState.h"
#include "nxt_msgs/Contact.h"
#include "nxt_msgs/Color.h"
#include "nxt_msgs/Range.h"
#include "lunarNXT/Order.h"

#include "lunarNXT/MoveMgr.h"
#include "lunarNXT/Mode.h"
#include "lunarNXT/BaseOdometry.h"

#define NB_THREADS 5

namespace lunar_lib {

/**
 * EnvAnalyser est la classe qui regroupe toute les interactions entre l'environnement, l'utilisateur et le robot.
 * Elle contient un Mode et un MoveMgr et leur transmet les informations recues.
 */
class EnvAnalyser {
private:
	/// Gestion du mode et des deplacements du robot
	MoveMgr* mm;
	Mode* mode;

// threads
/*
	pthread_t threads[NB_THREADS];

        enum cb_type {
                MOTOR,
                TOUCH_L,
				TOUCH_R,
                COLOR,
                ULTRASONIC
        };

        struct processEventArgs {
                void* msg;
                cb_type id_thread;
                Receptor* recs[2];

                processEventArgs(Receptor* r1,
                                Receptor* r2,
                                void* msg,
                                cb_type id) : msg(msg), id_thread(id)
                {
                        recs[0] = r1;
                        recs[1] = r2;
                }
        };
*/
public:
	/**
	 * Constructeur.
	 */
	EnvAnalyser();
	/**
	 * Constructeur.
	 * @param pub Pointeur vers le Publisher communiquant avec le robot.
	 */
	EnvAnalyser(ros::Publisher* pub);
	/**
	 * Destructeur.
	 */
	~EnvAnalyser();

	/**
	 * Callback des moteurs.
	 */
	void motorCallback(const sensor_msgs::JointState::ConstPtr& msg);
	/**
	 * Callback du capteurs de contact de droite.
	 */
	void rightTouchCallback(const nxt_msgs::Contact::ConstPtr& msg);
	/**
	 * Callback du capteurs de contact de gauche.
	 */
	void leftTouchCallback(const nxt_msgs::Contact::ConstPtr& msg);
	/**
	 * Callback du capteur de couleur.
	 */
	void colorCallback(const nxt_msgs::Color::ConstPtr& msg);
	/**
	 * Callback du capteur ultrasonique de distance.
	 */
	void ultrasonicCallback(const nxt_msgs::Range::ConstPtr& msg);
	/**
	 * Callback de l'application IHM
	 */
	void uiCallback(const lunarNXT::Order::ConstPtr& msg);

	// threads
	// static void* motorsT(void *msg);
};

};
#endif
