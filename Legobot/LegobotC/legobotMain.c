#include "legobotConstants.h"
#include "legobotFunctions.h"


void tribbleCollectTest() {
	printf("collecting test");
	legobotInit();
	printf("collecting test");
	motor(RIGHT_MOTOR, 40*1.05);
	motor(LEFT_MOTOR, 40);
	
	mav(SPINNER_MOTOR, 500);
	
	thread dipstickThread;
	dipstickThread = thread_create(dipstickDoesShit);
	thread_start(dipstickThread);
	
	msleep(4000);
	
	halt();
	turn(-90.0);
	
	motor(RIGHT_MOTOR, 40*1.05);
	motor(LEFT_MOTOR, 40);
	
	msleep(5000);
	
	ao();
	msleep(1000);
	thread_destroy(dipstickThread);
}

int main() {

	
	//printf("Press side button to end, A button to test dist, B button to test turn, C button to run longer test");
	while(1) {
		if (a_button()) {
			int i =0;
			for (i = 0; i < 8; i++) { 
				turn(45.0);
				msleep(500);
			}
		}
		else if (b_button()) {
			//raiseArm();
			moveToDist(NORMAL_SPEED,25);
			//printf("Moving to distance of: 25");
			//turnTest(91.2);
			//turn(90.0);
		}
		else if (c_button()) {
			
			moveToWallAlign(NORMAL_SPEED);
			moveToDist(-20, NORMAL_SPEED);
			turn(-90);
			mav(SPINNER_MOTOR, 500);
			moveToDistWithDipstick(SLOW_SPEED, 40);
			turn(-90);
			moveToDistWithDisptick(SLOW_SPEED, 60);
			turn(90);
			raiseArm();
			off(SPINNER_MOTOR);
			msleep(1000);
			ao();
		
		}
		msleep(100);
	}
	
}

