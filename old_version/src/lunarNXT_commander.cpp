#include <ros/ros.h>
#include <signal.h>
#include <termios.h>
#include <stdio.h>

#include "lunarNXT/Order.h"

#define KEYCODE_A 'a'
#define KEYCODE_D 'd'
#define KEYCODE_Q 'q'
#define KEYCODE_S 's'
#define KEYCODE_X 'x'
#define KEYCODE_Z 'z'
#define KEYCODE_L 'l'
#define KEYCODE_M 'm'

class Commander {
public:
	Commander();
	void keyLoop();

private:
	ros::NodeHandle n;
	ros::Publisher commander_pub;
};

Commander::Commander() {
	commander_pub = n.advertise<lunarNXT::Order>("ui_publish", 5);
}

int kfd = 0;
struct termios cooked, raw;

void quit(int sig) {
	tcsetattr(kfd, TCSANOW, &cooked);
	ros::shutdown();
	exit(0);
}

void Commander::keyLoop() {
	char c;

	// get the console in raw mode                                                              
	tcgetattr(kfd, &cooked);
	memcpy(&raw, &cooked, sizeof(struct termios));
	raw.c_lflag &=~ (ICANON | ECHO);
	// Setting a new line, then end of file                         
	raw.c_cc[VEOL] = 1;
	raw.c_cc[VEOF] = 2;
	tcsetattr(kfd, TCSANOW, &raw);

	puts("Reading from keyboard");
	puts("---------------------------");
	puts("Use arrow keys to move the ROBOT.");


	for(;;) {
		// get the next event from the keyboard  
		lunarNXT::Order msg = lunarNXT::Order();
  	
		if(read(kfd, &c, 1) < 0) {
			perror("read():");
			exit(-1);
		}

		ROS_DEBUG("value: 0x%02X\n", c);
  
		switch(c) {
			case KEYCODE_Q:
				ROS_INFO("Turn Left !");
				msg.order = "turn_l";
			        break;
			case KEYCODE_D:
				ROS_INFO("Turn Right !");
				msg.order = "turn_r";
				break;
			case KEYCODE_Z:
				ROS_INFO("Go !");
				msg.order = "go";
			        break;
			case KEYCODE_S:
				ROS_INFO("Back !");
				msg.order = "back";
				break;
			case KEYCODE_A:
				ROS_INFO("Stop !");
				msg.order = "stop";
				break;
			case KEYCODE_L:
				ROS_INFO("LineLauncher");
				msg.order = "line";
				break;
			case KEYCODE_M:
				ROS_INFO("LineUnLauncher");
				msg.order = "no_line";
				break;
		}

		this->commander_pub.publish(msg);
	}
	return;
}

int main(int argc, char** argv) {
        ros::init(argc, argv, "lunarNXT_commander");
        Commander commander;

        signal(SIGINT,quit);

        commander.keyLoop();

        return(0);
}
