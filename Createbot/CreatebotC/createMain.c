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
	 
	console_clear();
	printf("Press A to move with serial, B to turn with serial, C to enter testing utility, or the side button to exit the program.");
	
	while (!side_button()) {
		if (a_button()) {
			printf("\n\nMoving to distance 100cm at speed 350 mm/s with serial function...\n\n");
			moveWithSerial(350, 100);
		}
		
		else if (b_button()) {
			printf("\n\nTurning 90 degrees at speed 350 mm/s with serial function...\n\n");
			turnWithSerial(350, 90);
		}
		
		else if (c_button()) {
			testingUtility();
		}
		msleep(100);
	}
	return 0;
}
