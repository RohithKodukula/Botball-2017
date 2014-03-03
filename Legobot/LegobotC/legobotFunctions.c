#include "legobotConstants.h"
#include <math.h>

void legobotInit(){
	//setting all servo positions and enabling.
	set_servo_position(DUMPER_SERVO, DUMPER_UP);
	set_servo_position(DIPSTICK_SERVO, DIPSTICK_OPEN);
	set_servo_position(HANGER_SERVO, HANGER_BACK);
	set_servo_position(KICKER_SERVO, KICKER_BACK);
	enable_servos();
	//clear motor positions
	//should use the link to move the motors to initial first
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	clear_motor_position_counter(SPINNER_MOTOR);
	clear_motor_position_counter(ARM_MOTOR);
	moveArm(500);
	resetArm();
}


//Driving
void halt() {
	freeze(LEFT_MOTOR);
	freeze(RIGHT_MOTOR);
	msleep(200);
}

void rollStop() {
	off(LEFT_MOTOR);
	off(RIGHT_MOTOR);
}


void moveStraight(int power) {
	motor(LEFT_MOTOR, power);
	motor(RIGHT_MOTOR, power /* *CALIBRATION_CONSTANT*/);
}


/*
Must give positive power, distance can be negative
*/
void moveToDist(int power, int dist){
	int ticks = dist*TICKS_PER_CM;
	
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	
	power = dist > 0 ? power : -power;
	
	moveStraight(power);
	
	//all the distance calibrations are based on the left motor
	while (abs(get_motor_position_counter(LEFT_MOTOR)) < abs(ticks)) {
		msleep(10);
	}
	/*
	if(ticks >= 0){
		while(get_motor_position_counter(LEFT_MOTOR) < ticks && get_motor_position_counter(RIGHT_MOTOR) < ticks)
			msleep(10);
	}
	else if(ticks < 0){
		while(get_motor_position_counter(LEFT_MOTOR) > ticks && get_motor_position_counter(RIGHT_MOTOR) > ticks)
			msleep(10);
	}
	*/
	
	halt();
}

void turn(int speed, int degrees){	
	int ticks = degrees * TICKS_PER_CM;
	
	clear_motor_position_counter(RIGHT_MOTOR);
	clear_motor_position_counter(LEFT_MOTOR);
	
	speed = degrees > 0 ? speed : -speed;
	
	motor(RIGHT_MOTOR, speed);
	motor(LEFT_MOTOR, -speed);
	
	while((get_motor_position_counter(RIGHT_MOTOR) < ticks && ticks > 0) || (get_motor_position_counter(RIGHT_MOTOR) > ticks && ticks < 0)){
		msleep(50);
	}
	
	rollStop();
}

//The Arm 

void resetArm() {
	motor(ARM_MOTOR, -SLOW_SPEED);
	while (getArmDownSensorValue() > 100) {
		msleep(30);
	}
	off(ARM_MOTOR);
}

void moveArm(int pos) {
	clear_motor_position_counter(ARM_MOTOR);
	mtp(ARM_MOTOR, FAST_SPEED, pos);	
}

//Dipshit. *dipstick

void dipstickDoesShit(){
	while(1){
		set_servo_position(DIPSTICK_SERVO, DIPSTICK_CLOSE);
		msleep(200);
		set_servo_position(DIPSTICK_SERVO, DIPSTICK_OPEN);
		msleep(700);
	}
	set_servo_position(DIPSTICK_SERVO, DIPSTICK_CLOSE);
}

//Spinner
void spinnerStop(){
	int i;
	for(i = 0; i < 5; i++) {
		off(SPINNER_MOTOR);
	}
}

void spinner(int speed){
	mav(SPINNER_MOTOR, speed);
}


//Sensors
int getArmDownSensorValue() {
	return analog10(ARM_DOWN_SENSOR);
}
