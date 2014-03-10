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
	legobotInit();
	
	//printf("Press side button to end, A button to test dist, B button to test turn, C button to run longer test");
	while(1) {
		if (a_button()) {
			mav(SPINNER_MOTOR, 500);
			msleep(2000);
			ao();
			
		}
		else if (b_button()) {
			//raiseArm();
			//turnTest(-88.3);
			//printf("Moving to distance of: 25");
			//turnTest(91.2);
			//turn(90.0);
		}
		else if (c_button()) {
			thread spinnerThread = thread_create(spinnerStart);
			thread_start(spinnerThread);
			motor(SPINNER_MOTOR, 50);
			arcToWallAlign(NORMAL_SPEED, 1);
			moveToDist(NORMAL_SPEED,-30);
			turnTest(-87.75);
			
			moveToDistWithDipstick(SLOW_SPEED, 40);
			turnTest(-87.75);
			moveToDistWithDipstick(SLOW_SPEED, 60);
			turnTest(88.4);
			thread_destroy(spinnerThread);
			off(SPINNER_MOTOR);
			msleep(1000);
			ao();
		
		}
		msleep(100);
	}
	
}

void turnTest(double degrees) {
	clear_motor_position_counter(LEFT_MOTOR);
	
	double ticks = degrees * TICKS_PER_DEGREE;
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
