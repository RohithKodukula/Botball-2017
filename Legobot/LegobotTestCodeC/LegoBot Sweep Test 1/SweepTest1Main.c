// Created on Fri February 28 2014

#include "SweepTest1Constants.h"

int main()
{
	
	int x = 0;
	
	set_servo_position(DIPSTICK_SERVO_PORT, DIPSTICK_FLACID_POSITION);
	set_servo_position(BASKET_SERVO_PORT, BASKET_UP_POSITION);
	set_servo_position(FLICKER_SERVO_PORT, FLICKER_BACK_POSITION);
	
	enable_servos();
	
	motor(LEFT_WHEEL, LEFT_WHEEL_POWER);
	motor(RIGHT_WHEEL, RIGHT_WHEEL_POWER);
	move_at_velocity(SPINNER_MOTOR_PORT, SPINNER_MOTOR_VELOCITY);
	
	while (x < 10) {
		
		set_servo_position(DIPSTICK_SERVO_PORT, DIPSTICK_TAUGHT_POSITION);
		msleep(350);
		set_servo_position(DIPSTICK_SERVO_PORT, DIPSTICK_FLACID_POSITION);
		msleep(550);
		x++;
		
	}
	
	alloff();
	disable_servos();
	
	return 0;
}
