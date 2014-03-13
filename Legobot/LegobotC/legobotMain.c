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
			
			arcToWallAlign(NORMAL_SPEED, 1,1);
			
			//pivotOnLeft(NORMAL_SPEED, 45);
			//pivotOnRight(NORMAL_SPEED, 45);
			//pivotOnLeft(NORMAL_SPEED, -45);
			//pivotOnRight(NORMAL_SPEED, -45);
		}
		else if (b_button()) {
			int i;
			for (i = 0; i < 8; i++) {
				turnTest(42.2);
			}

		}
		else if (c_button()) {
			thread spinnerThread = thread_create(spinnerStart);
			thread_start(spinnerThread);
			arcToWallAlign(NORMAL_SPEED, 1, 1);
			pivotOnLeft(NORMAL_SPEED, -60);
			pivotOnRight(NORMAL_SPEED, -55);
			moveToDist(NORMAL_SPEED,-9.5);
			turnTest(-86.4);
			
			moveToDistWithDipstick(SLOW_SPEED, 50);
			turnTest(-86.4);
			moveToDistWithDipstick(SLOW_SPEED, 60);
			turnTest(88.36);
			msleep(1000);
			raiseArm();
			setHangerClawPosition(HANGER_FORWARD);
			moveToDist(NORMAL_SPEED, 20);
			thread_destroy(spinnerThread);
			off(SPINNER_MOTOR);
			
		
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
