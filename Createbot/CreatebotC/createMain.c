#include "createFunctions.h"
#include "createConstants.h"
#include "createVision.h"


void lowerArmAt(int power) {
	motor(ARM_PORT, power);
}

void stopArm() {
	off(ARM_PORT);
}

void testingUtility() {
	printf("Press A to raise Arm 4990 ticks, B to lower arm by sensor, C to center, side button to exit");
	msleep(500);
	while (!side_button()) {
		if (a_button()) {
			raiseArm(4990);
		}
		
		else if (b_button()) {
			lowerArmBySensor();
		}
		
		else if (c_button()) { 
			centerCamera(0, 0);

		}
		msleep(100);
	}
}


int main() {
	
	
	printf(0);
	
	createInit();
	initActuators();
	
	cameraInitialize();
	//
	
	//rotate(90, TURN_FAST_SPEED);
	
	
	
	//createInit();
	//initActuators();
	//printf("Moving to distance with normal function...\n\n");
	//moveToDist(50 * 10, MOVE_MID_SPEED);
	

	
	
	//msleep(5000);
	//printf("Moving to distance with normal function again...\n");
	//moveToDist(50 * 10, MOVE_MID_SPEED);
	
	
	
	 //raiseArm(4990);
	 //lowerArm(-4940);
	printf("Press A to move with serial, B to enter testing utility, C to end");
	while (!c_button()) {
		if (a_button()) {
			printf("Moving to dist 50cm with serial function...\n\n");
			moveWithSerial();
		}
		
		else if (b_button()) {
			testingUtility();
		}
		msleep(100);
	}
	return 0;
}

void moveWithSerial() {
	
	create_connect();
	 
			create_write_byte(128); //initializes mode to full
			create_write_byte(132);

			create_write_byte(152); // script size
			create_write_byte(14);
	
			create_write_byte(158);
			create_write_byte(5);
	
			create_write_byte(137); //drive straight
			create_write_byte(255);
			create_write_byte(200 );
			create_write_byte(128);
			create_write_byte(0);
	
			create_write_byte(156); //wait dist 50cm
			create_write_byte(254);
			create_write_byte(10);

			create_write_byte(137); //stop
			create_write_byte(0);
			create_write_byte(0);
			create_write_byte(0);
			create_write_byte(0);
			
	create_disconnect();
	
	create_connect();
	create_write_byte(153);
	create_disconnect();
	
}

