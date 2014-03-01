//#include "legobotFunctions.c"
#include "legobotConstants.h"

int main() {
	
	//moveStraight();
	
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	
	motor(LEFT_MOTOR, 60);
	motor(RIGHT_MOTOR, 60);
	
	while (get_motor_position_counter(LEFT_MOTOR) < 10000) {
		msleep(10);
	}
	ao();
	
	
}

void moveStraight(int power) {
	motor(LEFT_MOTOR, power);
	motor(RIGHT_MOTOR, power);
}

//void moveToDist(int speed, double dist) {
	
