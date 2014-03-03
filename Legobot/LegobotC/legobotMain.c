#include "legobotConstants.h"
#include "legobotFunctions.h"
#include <math.h>

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
	
	printf("Press side button to end, A button to test turn, B button to raise arm by sensor, C button to reset arm by sensor");
	while(1) {
		if (a_button()) {
			turnTest(-180.0);
		}
		else if (b_button()) {
			raiseArm();
		}
		else if (c_button()) {
			resetArm();
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
