#ifndef MOVEMGR_H
#define MOVEMGR_H

#include <string>
#include "ros/ros.h"

class MoveMgr {
private:
	ros::Publisher publisher;
	std::string leftName, rightName;
	
	bool hasGoal;
	float desiredLeftPosition, desiredRightPosition;
	float desiredLeftEffort, desiredRightEffort;

	float leftPosition, rightPosition;
	float leftEffort, rightEffort;
	
	void publish(float leftEffort, float rightEffort);
	void checkGoal();
	bool checkLeftGoal();
	bool checkRightGoal();

public:
	MoveMgr();
	MoveMgr(ros::Publisher publisher, std::string leftName, std::string rightName);
	~MoveMgr();
	bool hasGoalSet();

	// Deplacement infinit /!\ doit etre stope manuellement
	void linearMove(float effort);
	void turnLeft(float effort);
	void turnRight(float effort);

	// deplacement finit avec une marge d'erreur
	void linearMove(float effort, int cm);
	void turn(float effort, float rad);

	void stop();

	void updateLeft(float position, float effort);
	void updateRight(float position, float effort);
	void updateRange(float range);
};

#endif
