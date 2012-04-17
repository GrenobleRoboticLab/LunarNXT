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

class EnvAnalyser {
private:
	// Gestion du mode et des deplacements du robot
	MoveMgr* mm;
	Mode* mode;

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

public:
	// Construsteurs et destructeur
	EnvAnalyser();
	EnvAnalyser(ros::NodeHandle pub);
	~EnvAnalyser();

	// Callbacks des capteurs
	void motorCallback(const sensor_msgs::JointState::ConstPtr& msg);
	void rightTouchCallback(const nxt_msgs::Contact::ConstPtr& msg);
	void leftTouchCallback(const nxt_msgs::Contact::ConstPtr& msg);
	void colorCallback(const nxt_msgs::Color::ConstPtr& msg);
	void ultrasonicCallback(const nxt_msgs::Range::ConstPtr& msg);
	void uiCallback(const lunarNXT::Order::ConstPtr& msg);

	static void* motorsT(void *msg);
};

#endif
