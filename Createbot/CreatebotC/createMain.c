#include "createFunctions.h"
#include "createConstants.h"



void lowerArmAt(int power) {
	motor(ARM_PORT, power);
}

void stopArm() {
	off(ARM_PORT);
}

void testingUtility() {
	printf("Press A to raise Arm 4990 ticks, B to lower Arm [C to stop lowering], C to lower by sensor side button to exit");
	msleep(500);
	while (!side_button()) {
		if (a_button()) {
			raiseArm(4990);
		}
		
		else if (b_button()) {
			lowerArmAt(-30);
			while(!c_button()) {
				msleep(50);
			}
			off(ARM_PORT);
		}
		
		else if (c_button()) { 
			lowerArmBySensor();
		}
		msleep(100);
	}
}


int main() {
	printf(0);
	
	createInit();
	initActuators();
	
	printf("rotating\n");
	rotate(-90, TURN_SLOW_SPEED);
	rotate(90, TURN_MID_SPEED);
	//rotate(-90, TURN_FAST_SPEED);
	
	 //raiseArm(4990);
	 //lowerArm(-4940);
	/*printf("Press A to move, B to enter testing utility, C to end");
	while (!c_button()) {
		if (a_button()) {
			moveToDist(10,400);
		}
		
		else if (b_button()) {
			testingUtility();
		}
		msleep(100);
	}*/
	
	return 0;
}

