#include "legobotConstants.h"

void legoBotInit(){
	//setting all servo positions and enabling.
	set_servo_position(DUMPER_SERVO, DUMPER_UP);
	set_servo_position(DIPSTICK_SERVO, DIPSTICK_OPEN);
	set_servo_position(HANGER_SERVO, HANGER_START);
	enable_sevos();
	//clear motor positions
	//should use the link to move the motors to initial first
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	clear_motor_position_counter(SPIN_MOTOR);
	clear_motor_position_counter(ARM_MOTOR);
	resetArm();
}


//Driving
void halt() {
	freeze(LEFT_MOTOR);
	freeze(RIGHT_MOTOR);
}

void rollStop() {
	off(LEFT_MOTOR);
	off(RIGHT_MOTOR);
}


void moveStraight(int power)
{
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
	
	if(ticks >= 0){
		while(get_motor_position_counter(LEFT_MOTOR) < ticks && get_motor_position_counter(RIGHT_MOTOR) < ticks)
			msleep(10);
	}
	else if(ticks < 0){
		while(get_motor_position_counter(LEFT_MOTOR) > ticks && get_motor_position_counter(RIGHT_MOTOR) > ticks)
			msleep(10);
	}
	
	downerbotStop();
}

void turn(int speed, int degrees){	
	int ticks = degrees * DEGREES_TO_TICKS;
	
	clear_motor_position_counter(RIGHT_MOTOR);
	clear_motor_position_counter(LEFT_MOTOR);
	
	speed = degrees > 0 ? speed : -speed;
	
	mav(RIGHT_MOTOR, speed);
	mav(LEFT_MOTOR, -speed);
	
	while((get_motor_position_counter(RIGHT_MOTOR) < ticks && ticks > 0) || (get_motor_position_counter(RIGHT_MOTOR) > ticks && ticks < 0)){
		msleep(50);
	}
	
	legobotStop();
}

//The Arm 

void resetArm() {
	motor(ARM_MOTOR, -SLOW_SPEED);
	while (getArmDownSensorValue > 100) {
		msleep(30);
	}
	off(ARM_MOTOR);
}

void moveArm(int pos) {
	mtp(ARM_MOTOR, FAST_SPEED, pos);	
}

//Dipshit. *dipstick

void dipstickDoesShit(){
	while(1){
		set_servo_position(DIPSTICK_SERVO,DIPSTICK_CLOSE);
		msleep(200);
		set_servo_position(DIPSTICK_SERVO,DIPSTICK_OPEN);
		msleep(200);
	}
	set_servo_position(DIPSTICK_SERVO,DIPSTICK_CLOSE);
}

//Spinner
void spinnerStop(){
	int i;
	for(int i = 0; i < 5; i++) {
		freeze(SPINNER_MOTOR);
	}
}

void spinner(speed){
	mav(SPINNER_MOTOR, speed);
}


//Sensors
int getArmDownSensorValue() {
	return analog10(ARM_DOWN_SENSOR);
}
