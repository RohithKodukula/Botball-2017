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
	motor(RIGHT_MOTOR, power*R_WHEEL_CALIBRATION_CONSTANT);
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
	if (dist < 0) {
		while (get_motor_position_counter(LEFT_MOTOR) > ticks) {
			msleep(10);
		}
	}
	else {
		while (get_motor_position_counter(LEFT_MOTOR) < ticks) {
			msleep(10);
		}
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


//Dipshit. *dipstick

void dipstickDoesShit(){
	while(1){
		set_servo_position(DIPSTICK_SERVO, DIPSTICK_CLOSE);
		msleep(200);
		set_servo_position(DIPSTICK_SERVO, DIPSTICK_OPEN);
		msleep(2000);
	}
	set_servo_position(DIPSTICK_SERVO, DIPSTICK_CLOSE);
}


void moveToDistWithDipstick(int power, int dist) {
	int ticks = dist*TICKS_PER_CM;
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	
	power = dist > 0 ? power : -power;
	
	thread dipstickThread;
	dipstickThread = thread_create(dipstickDoesShit);
	thread_start(dipstickThread);
	
	moveStraight(power);
	
	while (abs(get_motor_position_counter(LEFT_MOTOR)) < abs(ticks)) {
		msleep(10);
	}
	halt();
	thread_destroy(dipstickThread);

}

void moveToWallAlign(int power) {
	motor(LEFT_MOTOR, power);
	motor(RIGHT_MOTOR, power*1.05);
	enable_servos();
	//set the left touch sensor to be parallel to 
	set_servo_position(DIPSTICK_SERVO, DIPSTICK_PARALLEL); //860 is when its parallel
	
	//variables to track which side has been activated
	int rightTriggered = 0;
	int leftTriggered = 0;
	while (1) {
		if (getLeftTouchSensor()) {
			freeze(LEFT_MOTOR);
			leftTriggered = 1;
			//if we don't set anything then the touch sensors could un-trigger
			//we might never escape loop
		}
		if (getRightTouchSensor()) {
			freeze(RIGHT_MOTOR);
			rightTriggered = 1;
		}
		if (rightTriggered && leftTriggered) {
			//halt the motors
			freeze(LEFT_MOTOR);
			freeze(RIGHT_MOTOR);
			printf("should be breaking out now...");
			break;
		}
		msleep(30);
	}
	
}

//arcLeft is a boolean
void arcToWallAlign(int power, int arcLeft) {
	

}


void turn(double degrees) {
	clear_motor_position_counter(LEFT_MOTOR);
	
	if (degrees > 0) {
		degrees = -5.4 + 1.1*degrees - (0.000296296*(degrees*degrees));
	}
	else {
		degrees = 3.57339 + 1.01722*degrees - (0.000017767*(degrees*degrees));
	}
	printf("corrected degrees: %f\n", degrees);

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

//based on last year's... that's why it's based on RIGHT_MOTOR for the counter
void turn_OLD(int speed, int degrees){	
	
	if (degrees < 0) {
		double compensatedDegrees = 3.57339 + 1.01722 * degrees - 0.000017767  * (degrees*degrees);
	}
	else {
		double compensatedDegrees = -5.4 + 1.1*degrees - (0.000296296*(degrees*degrees));
	}
	
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
	clear_motor_position_counter(ARM_MOTOR);
	motor(ARM_MOTOR, -1);
	int pwr = 0;
	int increased = 0;
	while (getArmDownSensorValue() > 100) {
		if (get_motor_position_counter(ARM_MOTOR) < -200 && !increased) {
			motor(ARM_MOTOR, 0);
		}
		msleep(30);
	}
	freeze(ARM_MOTOR);
	msleep(100);
	off(ARM_MOTOR);
}

void raiseArm() {
	motor(ARM_MOTOR, FAST_SPEED);
	while (getArmUpSensorValue() > 100) {
		msleep(30);
	}
	motor(ARM_MOTOR, ARM_HOLDING_POWER);
}
	

void moveArm(int pos) {
	clear_motor_position_counter(ARM_MOTOR);
	mtp(ARM_MOTOR, FAST_SPEED, pos);	
}




//Spinner
void spinnerStop(){
	off(SPINNER_MOTOR);
}

void spinner(int speed){
	mav(SPINNER_MOTOR, speed);
}


//Sensors
int getArmDownSensorValue() {
	return analog10(ARM_DOWN_SENSOR);
}

int getArmUpSensorValue() {
	return analog10(ARM_UP_SENSOR);
}

int getLeftTouchSensor() {
	return digital(LEFT_TOUCH_SENSOR);
}

int getRightTouchSensor() {
	return digital(RIGHT_TOUCH_SENSOR);
}
