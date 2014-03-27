#include "legobotConstants.h"
#include <math.h>

void legobotInit(){
	//setting all servo positions and enabling.
	set_servo_position(DUMPER_SERVO, DUMPER_UP);
	set_servo_position(POM_ALIGNER_SERVO, POM_ALIGNER_OPEN);
	set_servo_position(HANGER_SERVO, HANGER_BACK);
	set_servo_position(KICKER_SERVO, KICKER_BACK);
	enable_servos();
	//clear motor positions
	//should use the link to move the motors to initial first
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	clear_motor_position_counter(SPINNER_MOTOR);
	clear_motor_position_counter(ARM_MOTOR);
	moveArm(600);
	lowerArmBySensor();
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

void runPomAligner(){
	while(1){
		set_servo_position(POM_ALIGNER_SERVO, POM_ALIGNER_CLOSE);
		msleep(200);
		set_servo_position(POM_ALIGNER_SERVO, POM_ALIGNER_OPEN);
		msleep(1000);
	}
	set_servo_position(POM_ALIGNER_SERVO, POM_ALIGNER_OPEN);
}


void moveToDistWithPomAligner(int power, int dist) {
	int ticks = dist*TICKS_PER_CM;
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	
	power = dist > 0 ? power : -power;
	
	thread pomAlignerThread1;
	pomAlignerThread1 = thread_create(runPomAligner);
	thread_start(pomAlignerThread1);
	
	moveStraight(power);
	
	while (abs(get_motor_position_counter(LEFT_MOTOR)) < abs(ticks)) {
		msleep(10);
	}
	
	halt();
	
	thread_destroy(pomAlignerThread1);
	set_servo_position(POM_ALIGNER_SERVO, POM_ALIGNER_OPEN);
	
}



//----------WALL ALIGN FUNCTIONS----------

void moveToWallAlign(int power) {
	motor(LEFT_MOTOR, power);
	motor(RIGHT_MOTOR, power*R_WHEEL_CALIBRATION_CONSTANT);
	//set the left touch sensor to be parallel to 
	set_servo_position(POM_ALIGNER_SERVO, POM_ALIGNER_PARALLEL); //860 is when its parallel
	
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

void moveToTouch(int power) {
	motor(LEFT_MOTOR, power);
	motor(RIGHT_MOTOR, power*R_WHEEL_CALIBRATION_CONSTANT);
	//set the left touch sensor to be parallel to 
	set_servo_position(POM_ALIGNER_SERVO, POM_ALIGNER_PARALLEL); //860 is when its parallel
	
	//variables to track which side has been activated
	while (1) {
		if (getLeftTouchSensor()) {
			break;
		}
		if (getRightTouchSensor()) {
			break;
		}
		msleep(30);
	}
	halt();
	
}


void moveUntilMaxDist(int power) {
	int num = 10;
	
	//averaging
	
	int valsOld[num];
	int totalOld = 0;
	int valsNew[num];
	int totalNew = 0;
	
	int position = 0;
	
	int i;
	for (i = 0; i < num; i++) {
		valsOld[i] = getDistance();
		totalOld += valsOld[i];
		printf("---%d\n",totalOld);
	}
	
	for (i = 0; i < num; i++) {
		valsNew[i] = getDistance();
		totalNew += valsNew[i];
	}
	printf("totalNew: %d, totalOld: %d\n", totalNew, totalOld);
	
	moveStraight(power);
	
	while(totalNew + 200 > totalOld ) {
		totalOld -= valsOld[position];
		valsOld[position] = valsNew[position];
		totalOld += valsOld[position];
		
		totalNew -= valsNew[position];
		valsNew[position] = getDistance();
		totalNew += valsNew[position];
		
		printf("new val: %d, totalNew: %d,\n\t totalOld %d, pos: %d\n", valsNew[position], totalNew, totalOld, position);
		
		position = (position + 1)%num;
	}	
	halt();
}

//arcLeft is a boolean
//extremeArc is a boolean that says whether or not to increase the difference (more arc)
void arcToWallAlign(int power, int arcLeft, int extremeArc) {
	int leftPower;
	int rightPower;
	if (extremeArc) {
		leftPower = arcLeft ? power/3.2 : power*1.35; //give left wheel more power, necessary somehow
		rightPower = arcLeft ? power*1.35 : power/3.5;
	}
	else {
		leftPower = arcLeft ? power/2 : power;
		rightPower = arcLeft ? power : power/2;
	}
	motor(LEFT_MOTOR, leftPower);
	motor(RIGHT_MOTOR, rightPower * R_WHEEL_CALIBRATION_CONSTANT);	//calibration constant kept
	//set the left touch sensor to be parallel to 
	set_servo_position(POM_ALIGNER_SERVO, POM_ALIGNER_PARALLEL); //860 is when its parallel
	
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
			break;
		}
		msleep(30);
	}
}

void arcToTouch(int power, int arcLeft, int extremeArc) {
	int leftPower;
	int rightPower;
	if (extremeArc) {
		leftPower = arcLeft ? power/3.2 : power*1.35; //give left wheel more power, necessary somehow
		rightPower = arcLeft ? power*1.35 : power/3.5;
	}
	else {
		leftPower = arcLeft ? power/2 : power;
		rightPower = arcLeft ? power : power/2;
	}
	printf("Right wheel power: %d", rightPower);
	motor(LEFT_MOTOR, leftPower);
	motor(RIGHT_MOTOR, rightPower * R_WHEEL_CALIBRATION_CONSTANT);	//calibration constant kept
	//set the left touch sensor to be parallel to 
	set_servo_position(POM_ALIGNER_SERVO, POM_ALIGNER_PARALLEL); //860 is when its parallel
	
	while (!getLeftTouchSensor() && !getRightTouchSensor()) {
		msleep(30);
	}
	printf("\nFreezing");
	freeze(LEFT_MOTOR);
	freeze(RIGHT_MOTOR);
}

//----------END WALL ALIGN FUNCTIONS----------



//----------TURNING FUNCTIONS----------

void rotate(double degrees) {
	
	clear_motor_position_counter(LEFT_MOTOR);
	
	double ticks = degrees * TICKS_PER_DEGREE;
	
	//everything is calibrated around left wheel
	if (ticks < 0) {
		motor(LEFT_MOTOR, -1 * NORMAL_SPEED);
		motor(RIGHT_MOTOR, NORMAL_SPEED);
		while (get_motor_position_counter(LEFT_MOTOR) > ticks) {
			msleep(20);
		}
	}
	else {
		motor(LEFT_MOTOR, NORMAL_SPEED);
		motor(RIGHT_MOTOR, -1 * NORMAL_SPEED);
		while (get_motor_position_counter(LEFT_MOTOR) < ticks) {
			msleep(20);
		}
	}
	
	halt();
	
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

void pivotOnLeft(int power, int degrees) {
	clear_motor_position_counter(RIGHT_MOTOR);
	freeze(LEFT_MOTOR);
	int ticks = degrees * TICKS_PER_DEGREE * 2 * 0.945;	//last one is calibration
	//all ticks to cm is calibrated on left wheel
	
	power = degrees < 0 ? -power : power;
	motor(RIGHT_MOTOR, power);
	if (degrees < 0) {
		while (get_motor_position_counter(RIGHT_MOTOR) > ticks) {
			msleep(10);
		}
	}
	else {
		while (get_motor_position_counter(RIGHT_MOTOR) < ticks) {
			msleep(10);
		}
	}
	freeze(RIGHT_MOTOR);
}

void pivotOnRight(int power, int degrees) {
	clear_motor_position_counter(LEFT_MOTOR);
	freeze(RIGHT_MOTOR);
	int ticks = degrees * TICKS_PER_DEGREE * 2;
	
	power = degrees < 0 ? -power : power;
	motor(LEFT_MOTOR, power);
	if (degrees < 0) {
		while (get_motor_position_counter(LEFT_MOTOR) > ticks) {
			msleep(10);
		}
	}
	else {
		while (get_motor_position_counter(LEFT_MOTOR) < ticks) {
			msleep(10);
		}
	}
	freeze(LEFT_MOTOR);
}

void pivotOnRightTillLeftTouch(int power, int slightReverse) {
	clear_motor_position_counter(LEFT_MOTOR);
	freeze(RIGHT_MOTOR);
	motor(LEFT_MOTOR, power);
	if (slightReverse) {
		motor(RIGHT_MOTOR, -2);
	}
	while (!getLeftTouchSensor()) {
		msleep(30);
	}
	freeze(RIGHT_MOTOR);
	freeze(LEFT_MOTOR);
}

//----------END TURNING FUNCTIONS----------



//----------ARM FUNCTIONS----------

void lowerArmBySensor() {
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
	//msleep(100);
	//off(ARM_MOTOR);
}

void raiseArm() {
	motor(ARM_MOTOR, FAST_SPEED);
	while (getArmUpSensorValue() > 280) {
		msleep(30);
	}
	msleep(10);
	motor(ARM_MOTOR, ARM_HOLDING_POWER);
}

void moveArm(int pos) {
	clear_motor_position_counter(ARM_MOTOR);
	mtp(ARM_MOTOR, NORMAL_SPEED, pos);
	msleep(500);
	motor(ARM_MOTOR, ARM_HOLDING_POWER);
	
}


//----------SPINNER FUNCTIONS----------

void spinnerStop(){
	off(SPINNER_MOTOR);
}

void spinnerStart(){
	motor(SPINNER_MOTOR, 45);
}

//----------END SPINNER FUNCTIONS----------


//----------SERVO FUNCTIONS----------

void setHangerClawPosition(int position){
	set_servo_position(HANGER_SERVO, position);
}

void kick() {
	set_servo_position(KICKER_SERVO, KICKER_KICKED);
	freeze(SPINNER_MOTOR);
	msleep(1000);
	spinnerStart();
	//not necessary, only 1 pink tribble
	/*msleep(300);
	set_servo_position(KICKER_SERVO, KICKER_BACK);*/
}

//----------END SERVO FUNCTIONS----------


//----------SENSOR FUNCTIONS----------

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

int getDistance() {
	return analog_et(DISTANCE_SENSOR);
}

