#include "createConstants.h"

void createInit() {
	int connect = create_connect();
	enable_servos();
	if(connect == 0) {
		printf("Connection success.\n");
	}
	else {
		printf("Connection failed.\n");
	}
	create_full();
	msleep(500);
}

//----- ARM ------
void raiseArm(int position) {
	clear_motor_position_counter(ARM_PORT);
	while(get_motor_position_counter(ARM_PORT) < position) {
		printf("Motor position = %d\n", get_motor_position_counter(ARM_PORT));
		motor(ARM_PORT, 70);
		msleep(100);
	}
}
void lowerArm(int position) {
	clear_motor_position_counter(ARM_PORT);
	while(get_motor_position_counter(ARM_PORT) > position) {
		printf("Motor position = %d\n", get_motor_position_counter(ARM_PORT));
		motor(ARM_PORT, -70);
		msleep(100);
	}
}

//------ CREATE MOVEMENT-----
void moveStraight(int vel) {
	create_drive_straight(-vel);
}
void createStop() {
	moveStraight(0);
}
void moveToDist(int dist, int speed) { 
	set_create_distance(0); 

	if (dist > 0) {   
		moveStraight(speed); 
		while (-get_create_distance() < dist) { msleep(50); }
	}
	
	else if (dist < 0) { 
		moveStraight(-speed); 
		while (-get_create_distance() > dist) { msleep(50); }
	}
	
	createStop();
	
	printf("Distance Moved: %dmm\n", -get_create_distance(0)); 
}

