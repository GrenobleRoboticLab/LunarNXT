#include "nxt_msgs/JointCommand.h"
#include "lunarNXT/LunarNXT.h"

LunarNXT::LunarNXT(ros::NodeHandle n) {
	this->mm = new MoveManager(new Motor(n,"motor_l"), new Motor(n,"motor_r"));
	this->ec = new EnvironmentController(	new TouchSensor(n, "touch_l"),
						new TouchSensor(n, "touch_r"),
						new UltrasonicSensor(n, "ultrasonic_sensor"),
						new ColorSensor(n, "color_frame"),
						new Motor(n,"motor_color"));
	this->subscriber = n.subscribe("LunarNXT", 5, &LunarNXT::receiveAction, this);
}
	
void LunarNXT::goAhead() {
	if(this->ec->faceSomething())
		this->mm->linearMove(0);
	else
		this->mm->linearMove(3);
}

void LunarNXT::goBack() {
	this->mm->linearMove(-3);
}

void LunarNXT::stop() {
	this->mm->linearMove(0);
}

void LunarNXT::turnLeft() {
	this->mm->turnLeft(3);
}

void LunarNXT::turnRight() {
	this->mm->turnRight(3);
}

void LunarNXT::boostLeft() {
	this->mm->boostLeft(3);
}

void LunarNXT::boostRight() {
	this->mm->boostRight(3);
}

void LunarNXT::test(){
	this->ec->rotateColorSensor();
};

void LunarNXT::receiveAction (const lunarNXT::Order::ConstPtr& msg) {
	std::string str = msg->order;
	if(str == "GoAhead"){
		goAhead();
	}
	else if (str == "GoBack"){
		goBack();
	}
	else if (str == "Stop"){
		stop();
	}
	else if (str == "TurnRight"){
		turnRight();
	}
	else if (str == "TurnLeft"){
		turnLeft();
	}
	else if (str == "BoostRight"){
		boostRight();
	}
	else if (str == "BoostLeft"){
		boostLeft();
	}
	else if (str == "Test"){
		test();
	}		
}
