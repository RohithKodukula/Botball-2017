
#include "legobotConstants.h"
//#include <math.h>

//----------MISC FUNCTIONS----------

int abs (int x) {
	if (x < 0) return (-1 * x);
	else return x;
}

int sign (int x) {
	if (x < 0) return -1;
	else return 1;
}

void legobotInitialize() {
	
	initializeCamera();
	
	set_servo_position(CLAW_BASE_SERVO, CLAW_RAISED);
	set_servo_position(CLAW_MICRO_SERVO, CLAW_OPEN);
	set_servo_position(POM_SORTING_SERVO, POM_SORTING_NEUTRAL);
	set_servo_position(BASKET_SERVO, BASKET_NEUTRAL);
	
	enable_servos();
	
	clear_motor_position_counter(0);
	clear_motor_position_counter(1);
	clear_motor_position_counter(2);
	clear_motor_position_counter(3);
	
	
}

//----------END MISC FUNCTIONS----------



//----------DRIVING FUNCTIONS----------


void stop() {
	
	freeze(LEFT_MOTOR);
	freeze(RIGHT_MOTOR);
	msleep(200);
	
}


void rollStop() {
	
	off(LEFT_MOTOR);
	off(RIGHT_MOTOR);
	
}


//make dist negative to go backwards
void moveToDist(int speed, double dist) { // Speed should be a percentage, dist in cm always
	
	double ticksAsDouble = (dist * TICKS_PER_CM);
	
	int ticks = (int) ticksAsDouble;
	int direction = sign((int)dist);
	int power = abs(speed) * direction;
	
	double leftMotorComp = 1.08;
	
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	
	int leftMotorPower = (int) (power * leftMotorComp);
	
	motor(RIGHT_MOTOR, power);
	motor(LEFT_MOTOR, leftMotorPower);
	
	printf("Running for %d ticks, left power is %d...\n", ticks, leftMotorPower);
	
	while (abs(get_motor_position_counter(LEFT_MOTOR)) < abs(ticks)) {
		msleep(10);
	}
	
	stop();
	
}

void jiggleEntireRobot() {
	
	console_clear();
	
	int i = 0;
	
	for (i = 0; i < 5; i++) {
		
		printf("jiggling entire robot...\n");
		
		motor(LEFT_MOTOR, 100);
		motor(RIGHT_MOTOR, -100);
		msleep(100);
		motor(LEFT_MOTOR, -100);
		motor(RIGHT_MOTOR, 100);
		msleep(100);
		
	}
	
	stop();
	
}

//----------END DRIVING FUNCTIONS----------



//----------TURNING FUNCTIONS----------

void rotate(double degrees) {
	
	stop();
	
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	
	double ticks = degrees * TICKS_PER_DEGREE;
	
	if (ticks < 0) {
		
		motor(LEFT_MOTOR, -1 * MID_SPEED);
		motor(RIGHT_MOTOR, MID_SPEED);
		
		while (get_motor_position_counter(LEFT_MOTOR) > ticks) {
			msleep(10);
		}
		
	} 
	else {
		
		motor(LEFT_MOTOR, MID_SPEED);
		motor(RIGHT_MOTOR, -1 * MID_SPEED);
		
		while (get_motor_position_counter(LEFT_MOTOR) < ticks) {
			msleep(10);
		}
		
	}
	
	stop();
	
}

void pivotOnLeft(double degrees) {
	
	stop();
	
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	
	int ticks = (int) (degrees * TICKS_PER_DEGREE_LEFT);
	
	motor(RIGHT_MOTOR, MID_POWER * sign(degrees));
	
	while (abs(get_motor_position_counter(LEFT_MOTOR)) < abs(ticks)) {
		msleep(10);
	}
	
	stop();
	
}

void pivotOnRight(double degrees) {
	
	stop();
	
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	
	int ticks = (int) (degrees * TICKS_PER_DEGREE_RIGHT);
	
	motor(LEFT_MOTOR, MID_POWER * sign(degrees));
	
	while (abs(get_motor_position_counter(LEFT_MOTOR)) < abs(ticks)) {
		msleep(10);
	}
	
	stop();
	
}

//----------END TURNING FUNCTIONS----------



//----------SERVO FUNCTIONS----------
void smoothMove(int SERVO, int CUR,int VAL){
	int POS = CUR;
	int i = 0;
	for(i = 0;i<10;i++){
		set_servo_position(SERVO,POS);
		POS = POS + (VAL-POS)/5;
		msleep(200);
	}
}//670
void scoopPoms(){
	//set_servo_position(POM_SORTING_SERVO,POM_SORT_R);
	//msleep(500);
	smoothMove(CLAW_MICRO_SERVO,CLAW_OPEN,CLAW_CLOSED);
	msleep(1000);
	set_servo_position(CLAW_BASE_SERVO,CLAW_POM_DEPOSIT);
	msleep(2000);
	scooperJiggle();
	msleep(800);
	smoothMove(CLAW_BASE_SERVO,CLAW_POM_DEPOSIT,CLAW_DOWN);
	//set_servo_position(CLAW_BASE_SERVO,CLAW_DOWN);
	set_servo_position(CLAW_MICRO_SERVO,CLAW_OPEN);
	msleep(500);
	//set_servo_position(POM_SORTING_SERVO,POM_SORTING_NEUTRAL);
}

void scooperJiggle(){
	int i = 0;
	for(i=0;i<2;i++){
		set_servo_position(CLAW_BASE_SERVO,CLAW_RAISED);
		msleep(800);
		set_servo_position(CLAW_BASE_SERVO,CLAW_POM_DEPOSIT);
		msleep(800);
	}
}

void checkerJiggle(){
	int i = 0;
	/*for(i=0;i<1;i++){
		set_servo_position(POM_SORTING_SERVO,POM_JIGG_L);
		msleep(800);
		set_servo_position(POM_SORTING_SERVO,POM_JIGG_R);
		msleep(800);
		set_servo_position(POM_SORTING_SERVO,POM_SORTING_NEUTRAL);
		msleep(800);
	}*/
}


void depositPomInBasket() {
	
	set_servo_position(POM_SORTING_SERVO, POM_SORTING_BASKET);
	msleep(POM_DEPOSIT_BASKET_DURATION);
	set_servo_position(POM_SORTING_SERVO, POM_SORTING_NEUTRAL);
	jiggleBasket(3);
	
}

void depositPomOnTable() {
	
	set_servo_position(POM_SORTING_SERVO, POM_SORTING_TABLE);
	msleep(POM_DEPOSIT_TABLE_DURATION);
	set_servo_position(POM_SORTING_SERVO, POM_SORTING_NEUTRAL);
}

void dumpBasket() {
	
	int i;
	
	for (i = 0; i < 3; i++) {
		set_servo_position(BASKET_SERVO, BASKET_DUMP);
		msleep(800);
		set_servo_position(BASKET_SERVO, BASKET_NEUTRAL);
		msleep(800);
	}
	
}

void jiggleBasket(int numTimes) {
	
	int i;
	
	for(i = 0; i < numTimes; i++) {
		
		msleep(200);
		set_servo_position(BASKET_SERVO, BASKET_NEUTRAL); //inwards
		msleep(200);
		set_servo_position(BASKET_SERVO, BASKET_JIGGLE); //outwards
		
	}
	
	msleep(800);
	
	set_servo_position(BASKET_SERVO, BASKET_NEUTRAL);
	
}

void jiggleBasketMore(int numTimes) {
	
	int i;
	
	for(i = 0; i < numTimes; i++) {
		
		msleep(200);
		set_servo_position(BASKET_SERVO, BASKET_NEUTRAL); //inwards
		msleep(200);
		set_servo_position(BASKET_SERVO, BASKET_BIG_JIGGLE); //outwards
		
	}
	
	msleep(800);
	
	set_servo_position(BASKET_SERVO, BASKET_NEUTRAL);
	
}

//----------END SERVO FUNCTIONS----------



//----------SORTING FUNCTIONS----------


void sortSinglePom() {
	
	while (!cameraSeesGreenPom() && !cameraSeesRedPom()) {
		console_clear;
		printf("I still don't see any poms...");
		msleep(500);
	}
	
	console_clear;
	
	msleep(300);
	camera_update();
	msleep(300);
	camera_update();
	msleep(300);
	camera_update();
	
	
	if (cameraSeesGreenPom()) {
		
		printf("I see a green pom.\n\nDepositing in basket...");
		
		depositPomInBasket();
		
		} else {
		
		printf("I see a red pom.\n\nDepositing on table...");
		
		depositPomOnTable();
		msleep(1500);
		
	}
	
}

void sortSixPoms() {
	
	int i;
	
	for (i = 0; i < 6; i++) {
		sortSinglePom();
		//checkerJiggle();
	}
	
}

void sortAllPoms() {
	
	int greenPomsSorted = 0, redPomsSorted = 0;
	
	while (greenPomsSorted < 6 && redPomsSorted < 6) {
		
		while (!cameraSeesGreenPom() && !cameraSeesRedPom()) {
			printf("I still don't see any poms...\n\n");
			msleep(500);
		}
		
		if (cameraSeesGreenPom()) {
			printf("I see a green pom. Depositing in basket...\n\n");
			depositPomInBasket();
			greenPomsSorted++;
			} else {
			printf("I see a red pom. Depositing on table...\n\n");
			depositPomOnTable();
			redPomsSorted++;
		}
		
	}
	
	if (greenPomsSorted < 6) {
		
		while (greenPomsSorted < 6) {
			depositPomInBasket();
			greenPomsSorted++;
		}
		
		} else {
		
		while (redPomsSorted < 6) {
			depositPomOnTable();
			redPomsSorted++;
		}
		
	}
	
}

void sortMorePoms() {
	
	int greenPomsSorted = 0, redPomsSorted = 0;
	
	while (1) {
		
		while (!cameraSeesGreenPom() && !cameraSeesRedPom()) {
			printf("I still don't see any poms...\n\n");
			msleep(500);
		}
		
		if (cameraSeesGreenPom()) {
			printf("I see a green pom. Depositing in basket...\n\n");
			depositPomInBasket();
			greenPomsSorted++;
			} else {
			printf("I see a red pom. Depositing on table...\n\n");
			depositPomOnTable();
			redPomsSorted++;
		}
		
	}
	
	if (greenPomsSorted < 6) {
		
		while (greenPomsSorted < 6) {
			depositPomInBasket();
			greenPomsSorted++;
		}
		
		} else {
		
		while (redPomsSorted < 6) {
			depositPomOnTable();
			redPomsSorted++;
		}
		
	}
	
}

//----------END SORTING FUNCTIONS----------


