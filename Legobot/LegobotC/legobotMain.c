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
	turnTest(-90.0);
	
	motor(RIGHT_MOTOR, 40*1.05);
	motor(LEFT_MOTOR, 40);
	
	msleep(5000);
	
	ao();
	msleep(1000);
	thread_destroy(dipstickThread);
}

int main() {
	/*
	//Tribble collecting/drive straight test!
	legobotInit();
	motor(RIGHT_MOTOR, 40*1.05);
	motor(LEFT_MOTOR, 40);
	
	mav(SPINNER_MOTOR, 500);
	
	thread dipstickThread;
	dipstickThread = thread_create(dipstickDoesShit);
	thread_start(dipstickThread);
	
	msleep(10000);
	
	ao();
	msleep(1000);
	thread_destroy(dipstickThread);
	
	*/
	
	printf("Press side button to end, A button to test dist, B button to test turn, C button to run longer test");
	while(1) {
		if (a_button()) {
			int i =0;
			for (i = 0; i < 8; i++) { 
				turnTest(43.5);
				msleep(500);
			}
		}
		else if (b_button()) {
			//raiseArm();
			//moveToDist(NORMAL_SPEED,25);
			//printf("Moving to distance of: 25");
			turnTest(91.2);
		}
		else if (c_button()) {
			moveToDistWithTribbleGrabbing(SLOW_SPEED, 35);
			turnTest(-89.5);
			moveToDistWithTribbleGrabbing(SLOW_SPEED, 50);
		}
		msleep(100);
	}
	
}


void turnTest(double degrees) {
	clear_motor_position_counter(LEFT_MOTOR);

	double ticks = degrees * TICKS_PER_DEGREE;
	printf("degrees: %f\n", degrees);
	printf("degrees: %f\n", TICKS_PER_DEGREE);
	printf("target ticks: %f\n", degrees * TICKS_PER_DEGREE);
	//everything is calibrated around left wheel
	if (ticks < 0) {
		motor(LEFT_MOTOR, -1*NORMAL_SPEED);
		motor(RIGHT_MOTOR, NORMAL_SPEED);
		while (get_motor_position_counter(LEFT_MOTOR) > ticks) {
			msleep(30);
		}
	}
	else {
		motor(LEFT_MOTOR, NORMAL_SPEED);
		motor(RIGHT_MOTOR, -1*NORMAL_SPEED);
		while (get_motor_position_counter(LEFT_MOTOR) < ticks) {
			msleep(30);
		}
	}
	
	halt();
	
}
