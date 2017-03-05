
#include "createConstants.h"
#include "createVision.h"

int deltaAngle = 0;
int deltaDistance = 0;

int irValuesAreSketchy;

// ------------------- MISCELLANEOUS FUNCTIONS -------------------

int abs(int x) {
	if (x < 0) return (-1 * x);
	else return x;
}

int armStateToTicks(int armState) {
	if (armState == 3) return ARM_HIGH;
	else if (armState == 2) return ARM_MID;
	else if (armState == 1) return ARM_LOW;
	else return 0;
}

int elevatorStateToTicks(int elevatorState) {
	if (elevatorState == 2) return ELEVATOR_TOP;
	else if (elevatorState == 1) return ELEVATOR_MID;
	else return 0;
}

void waitByteSendInterval() {
	msleep(CREATE_BYTE_SEND_WAIT);
}

// ------------------- SENSOR FUNCTIONS -------------------

int armCherrySensorIsTriggered() {
	
	if (digital(ARM_LOWER_CHERRY) == 0) {
		return 0;
	} else return 1;
	
}

int elevatorIRSensorIsTriggered() {
	
	int irValue = analog10(ELEVATOR_IR);
	
	if (irValue < ELEVATOR_IR_MIN) {
		return 1;
	} else return 0;
	
}

int getElevatorIRSensorValue() {
	return analog10(ELEVATOR_IR);
}

int getMillimeterDistance() {
	int i;
	double sum = 0;
	int n = 10;
	for (i = 0; i < n; i++) {
		sum += analog10(0);
	}
	return distanceValueToMM(sum/n);
}

int distanceValueToMM(double y) {
	return (int) (10*(2213.1614337305136 - 20.725917486966626*y + 0.07920950330177698*y*y - 0.0001526660102098271*y*y*y 
	+ 1.4770513368970602*(pow(10,-7))*y*y*y*y - 5.725546246379343*(pow(10,-11))*y*y*y*y*y));
}

// ------------------- INITIALIZATION FUNCTIONS -------------------

void createInit() {
	
	console_clear();
	printf("The create must be turned on...");
	
	int connectionFailed = create_connect();
	
	msleep(200);
	
	if (!connectionFailed) {
		create_full();
		msleep(500);
		console_clear();
		printf("Create connection succeeded.\n\n");
		} else {
		msleep(500);
		console_clear();
		printf("Create connection failed.\n\n");
	}
	
}

void initializeQuick() {
	
	createInit();
	
	openFrontClaw();
	//openPongClaw();
	enable_servos();
	
	raiseArmPastSensor();
	raiseArm(250);
	//raiseElevator(500);
	//lowerElevatorToBottom();
	lowerArmToBottom();
	
}

void initializeFull() {
	
	createInit();
	cameraInitialize();
	
	openFrontClaw();
	//openPongClaw();
	enable_servos();
	
	raiseArmPastSensor();
	lowerArmToBottom();
	
	console_clear();
	msleep(100);
	printf("Run IR calibration utility or use default values?\n\n");
	set_a_button_text("UTILITY");
	set_b_button_text("");
	set_c_button_text("DEFAULT");
	
	int selection = 0;
	
	while (1) {
		if (a_button()) {
			selection = 1;
			break;
			} else if (c_button()) {
			selection = 2;
			break;
		} else msleep(10);
	}
	
	if (selection == 1) {
		
		runIRCalibrationUtility();
		
		console_clear();
		printf("Initialization complete.\n\n");
		
		} else {
		
		ELEVATOR_IR_MIN = ELEVATOR_IR_MIN_DEFAULT;
		ELEVATOR_IR_MAX = ELEVATOR_IR_MAX_DEFAULT;
		
		console_clear();
		printf("Elevator IR values set to %d and %d.\n\nInitialization complete.\n\n", ELEVATOR_IR_MIN, ELEVATOR_IR_MAX);
		set_a_button_text("");
		set_b_button_text("");
		set_c_button_text("");
		
	}
	
	msleep(500);
	raiseArmPastSensor();
	msleep(500);
	//raiseElevator(500);
	//lowerElevatorToBottom();
	lowerArmToBottom();
	
}

// ------------------- SERVO FUNCTIONS -------------------

void openFrontClaw() {
	set_servo_position(FRONT_CLAW, FRONT_CLAW_OPEN);
}

void closeFrontClaw() {
	set_servo_position(FRONT_CLAW, FRONT_CLAW_CLOSED);
}

void openPongClaw() {
	set_servo_position(PONG_CLAW, PONG_CLAW_OPEN);
}

void closePongClaw() {
	set_servo_position(PONG_CLAW, PONG_CLAW_CLOSED);
}

// ------------------- ARM MOVEMENT FUNCTIONS -------------------

void moveArmToPosition(int position) {
	
	int goalState = 0;
	
	if (position < ARM_HIGH + 100 && position > ARM_HIGH - 100) goalState = 3;
	else if (position < ARM_MID + 100 && position > ARM_MID - 100) goalState = 2;
	else if (position < ARM_LOW + 100 && position > ARM_LOW - 100) goalState = 1;
	
	int goalTicks = elevatorStateToTicks(goalState);
	int currentTicks = elevatorStateToTicks(ELEVATOR_STATE);
	int difference = abs(goalTicks - currentTicks);
	
	console_clear();
	printf("Current ticks: %d\nGoal ticks: %d\nDifference: %d\n\n", currentTicks, goalTicks, difference);
	printf("Current state: %d\nGoal state: %d\n\n", ELEVATOR_STATE, goalState);
	
	if (ARM_STATE != goalState && goalState != 0) {
		
		if (ARM_STATE < goalState) {
			raiseArm(difference);
			} else {
			lowerArm(difference);
		}
		
		} else if (goalState == 0 && ARM_STATE != 0) {
		lowerArmToBottom();
	}
	
	ARM_STATE = goalState;
	
}

void moveArmToPositionWithRecalibration(int position) {
	
	lowerArmToBottom();
	moveArmToPosition(position);
	
}

void raiseArmToTop() {
	moveArmToPosition(ARM_HIGH);
}

void raiseArm(int position) {
	
	if (position == ARM_HIGH) ARM_STATE = 3;
	else if (position == ARM_MID) ARM_STATE = 2;
	else ARM_STATE = 1;
	
	clear_motor_position_counter(LEFT_ARM_MOTOR);
	clear_motor_position_counter(RIGHT_ARM_MOTOR);
	
	motor(LEFT_ARM_MOTOR, 100);
	motor(RIGHT_ARM_MOTOR, 100);
	
	while(abs(get_motor_position_counter(LEFT_ARM_MOTOR)) < position) {
		msleep(25);
	}
	
	off(LEFT_ARM_MOTOR);
	off(RIGHT_ARM_MOTOR);
	
}

void lowerArm(int position) {
	
	clear_motor_position_counter(LEFT_ARM_MOTOR);
	clear_motor_position_counter(RIGHT_ARM_MOTOR);
	
	motor(LEFT_ARM_MOTOR, -70);
	motor(RIGHT_ARM_MOTOR, -70);
	
	while(abs(get_motor_position_counter(LEFT_ARM_MOTOR)) < abs(position)) {
		msleep(25);
	}
	
	off(LEFT_ARM_MOTOR);
	off(RIGHT_ARM_MOTOR);
	
}

void moveArmToTop() {
	
	moveArmToPosition(ARM_HIGH);
	
}

void moveArmToMiddle() {
	
	moveArmToPosition(ARM_MID);
	
}

void moveArmToLow() {
	
	moveArmToPosition(ARM_LOW);
	
}

void lowerArmToBottom() {
	
	clear_motor_position_counter(LEFT_ARM_MOTOR);
	
	motor(RIGHT_ARM_MOTOR, -70);
	motor(LEFT_ARM_MOTOR, -70);
	
	int targetTicks = 0;
	
	while (!armCherrySensorIsTriggered()) {
		msleep(20);
	}
	
	targetTicks = get_motor_position_counter(LEFT_ARM_MOTOR) - 650;
	
	while (get_motor_position_counter(LEFT_ARM_MOTOR) > targetTicks) {
		msleep(20);
	}
	
	off(RIGHT_ARM_MOTOR);
	off(LEFT_ARM_MOTOR);
	
	ARM_STATE = 0;
	
}

void raiseArmPastSensor() {
	
	clear_motor_position_counter(LEFT_ARM_MOTOR);
	
	motor(RIGHT_ARM_MOTOR, 100);
	motor(LEFT_ARM_MOTOR, 100);
	
	printf("raise arm past sensor\n");
	
	int x = 0;
	
	int targetTicks = 0;
	
	while (armCherrySensorIsTriggered() && x < 500) {
		msleep(25);
		x++;
	}
	
	targetTicks = get_motor_position_counter(LEFT_ARM_MOTOR) + 1000;
	
	while (get_motor_position_counter(LEFT_ARM_MOTOR) < targetTicks) {
		msleep(20);
	}
	
	off(RIGHT_ARM_MOTOR);
	off(LEFT_ARM_MOTOR);
	
}

// ------------------- ELEVATOR FUNCTIONS -------------------

void moveElevatorToPosition(int position) {
	
	int goalState = 0;
	
	if (position < ELEVATOR_TOP + 100 && position > ELEVATOR_TOP - 100) goalState = 2;
	else if (position < ELEVATOR_MID + 100 && position > ELEVATOR_MID - 100) goalState = 1;
	
	int goalTicks = elevatorStateToTicks(goalState);
	int currentTicks = elevatorStateToTicks(ELEVATOR_STATE);
	int difference = abs(goalTicks - currentTicks);
	
	console_clear();
	printf("Current ticks: %d\nGoal ticks: %d\nDifference: %d\n\n", currentTicks, goalTicks, difference);
	printf("Current state: %d\nGoal state: %d\n\n", ELEVATOR_STATE, goalState);
	
	if (ELEVATOR_STATE != goalState && goalState != 0) {
		if (ELEVATOR_STATE < goalState) {
			raiseElevator(difference);
			} else {
			lowerElevator(difference);
		}
		} else if (goalState == 0 && ELEVATOR_STATE != 0) {
		lowerElevatorToBottom();
	}
	
	ELEVATOR_STATE = goalState;
	
}

void raiseElevator(int position) {
	
	clear_motor_position_counter(ELEVATOR_MOTOR);
	
	motor(ELEVATOR_MOTOR, 100);
	
	while(abs(get_motor_position_counter(ELEVATOR_MOTOR)) < position) {
		msleep(25);
	}
	
	off(ELEVATOR_MOTOR);
	
}

void lowerElevator(int position) {
	
	clear_motor_position_counter(ELEVATOR_MOTOR);
	
	motor(ELEVATOR_MOTOR, -30);
	
	while(abs(get_motor_position_counter(ELEVATOR_MOTOR)) < position) {
		msleep(25);
	}
	
	off(ELEVATOR_MOTOR);
	
}

void moveElevatorToTop() {
	
	moveElevatorToPosition(ELEVATOR_TOP);
	
}

void moveElevatorToMiddle() {
	
	moveElevatorToPosition(ELEVATOR_MID);
	
}

void lowerElevatorToBottom() {
	
	motor(ELEVATOR_MOTOR, -15);
	
	while(getElevatorIRSensorValue() > ELEVATOR_IR_MIN) {
		msleep(10);
	}
	
	off(ELEVATOR_MOTOR);
	
	ELEVATOR_STATE = 0;
	
}

// ------------------- CREATE MOVEMENT -------------------

void moveStraight(int velocity) {
	create_drive_straight(-velocity);
}

void createStop() {
	moveStraight(0);
}

void moveToDist(int dist, int speed) { 
	set_create_distance(0); 
	
	//speed distance compensation
	if(speed >= 400){dist = dist - (22 * (dist * 0.01));} //fast speed
	else if(speed > 300 && speed < 400){dist = dist - (8 * (dist * 0.01));} //mid speed
	else if(speed <= 300){dist = dist - (6 * (dist * 0.01));} //slow speed
	
	if (dist > 0) {   
		moveStraight(speed); 
		while (-get_create_distance() < dist) { msleep(10); }
	}
	
	else if (dist < 0) { 
		moveStraight(-speed); 
		while (-get_create_distance() > dist) { msleep(10); }
	}
	
	createStop();
	
	//printf("Distance Moved: %dmm\n", -get_create_distance(0)); 
}
/*
moveToWallAlign function by Ben 2/15/15
--------------------------------------------------------------------
This function drives backwards until it times out (and hopefully hits and aligns with a wall). Is it assumed that the robot is aligned roughly with a wall.
*/
/*void moveToWallAlign(int dist, int speed, double secondTimeout) {
	set_create_distance(0); 
	
	double startTime = seconds();
	
	//speed distance compensation
	if(speed >= 400){dist = dist - (22 * (dist * 0.01));} //fast speed
	else if(speed > 300 && speed < 400){dist = dist - (8 * (dist * 0.01));} //mid speed
	else if(speed <= 300){dist = dist - (6 * (dist * 0.01));} //slow speed
	
	if (dist > 0) {   
		moveStraight(speed); 
		while (-get_create_distance() < dist && seconds() - startTime < secondTimeout) { msleep(10); }
	}
	
	else if (dist < 0) { 
		moveStraight(-speed); 
		while (-get_create_distance() > dist && seconds() - startTime < secondTimeout) { msleep(10); }
	}
	
	createStop();
	
	printf("Distance Moved: %dmm\n", -get_create_distance(0)); 
}/*

//FOR DOCUMENTATION:

/*
moveToWallAlign function by Ben 2/15/15
--------------------------------------------------------------------
This function drives backwards until it times out (and hopefully hits and aligns with a wall). Is it assumed that the robot is aligned roughly with a wall.
*/

void moveToWallAlign(int dist, int speed, double secondTimeout) {
	
	double startTime = seconds();
	
	if (dist > 0) {   
		moveStraight(speed); 
		while (seconds() - startTime < secondTimeout) { msleep(10); }
		} else if (dist < 0) { 
		moveStraight(speed); 
		while (seconds() - startTime < secondTimeout) { msleep(10); }
	}
	
	createStop();
	
	printf("Distance Moved: %dmm\n", -get_create_distance(0)); 
	
}

void moveWithSerial(int speed, int distance) {
	
	int dist1, dist2, speed1, speed2;
	
	if (distance < 0) {
		distance *= -1;
		speed *= -1;
	}
	
	if (speed < 0) {
		
		speed1 = 0;
		speed2 = speed * -1;
		distance *= -1;
		
		while (speed2 > 255) {
			speed1++;
			speed2 -= 255;
		}
		
		} else {
		speed1 = 255;
		speed2 = speed;
		while (speed2 > 255) {
			speed1--;
			speed2 -= 255;
		}
		speed2 = 255 - speed2;
	}
	
	if (distance < 0) {
		
		dist1 = 0;
		dist2 = distance * -1;
		
		while (dist2 > 255) {
			dist1++;
			dist2 -= 255;
		}
		
		} else {
		dist1 = 255;
		dist2 = distance;
		while (dist2 > 255) {
			dist1--;
			dist2 -= 255;
		}
		dist2 = 255 - dist2;
	}
	
	create_clear_serial_buffer();
	msleep(300);
	
	create_write_byte(128); //initializes mode to full
	waitByteSendInterval();
	create_write_byte(132);
	waitByteSendInterval();
	
	create_write_byte(152); // script size
	waitByteSendInterval();
	create_write_byte(13);
	waitByteSendInterval();
	
	create_write_byte(137); //drive straight
	waitByteSendInterval();
	create_write_byte(speed1);
	waitByteSendInterval();
	create_write_byte(speed2);
	waitByteSendInterval();
	create_write_byte(128);
	waitByteSendInterval();
	create_write_byte(0);
	waitByteSendInterval();
	
	create_write_byte(156); //wait specified distance
	waitByteSendInterval();
	create_write_byte(dist1);
	waitByteSendInterval();
	create_write_byte(dist2);
	waitByteSendInterval();
	
	create_write_byte(137); //stop
	waitByteSendInterval();
	create_write_byte(0);
	waitByteSendInterval();
	create_write_byte(0);
	waitByteSendInterval();
	create_write_byte(0);
	waitByteSendInterval();
	create_write_byte(0);
	waitByteSendInterval();
	create_write_byte(153);
	
}

void turnWithSerial(int speed, int degrees) {
	
	speed = abs(speed);
	int angle1, angle2, speed1, speed2;
	
	if (degrees < 0) {
		
		speed1 = 0;
		speed2 = speed;
		
		while (speed2 > 255) {
			speed1++;
			speed2 -= 255;
		}
		
		} else {
		
		speed1 = 255;
		speed2 = speed;
		
		while (speed2 > 255) {
			speed1--;
			speed2 -= 255;
		}
		
		speed2 = 255 - speed2;
		
	}
	
	if (degrees < 0) {
		
		angle1 = 0;
		angle2 = degrees * -1;
		
		while (angle2 > 255) {
			angle1++;
			angle2 -= 255;
		}
		
		} else {
		
		angle1 = 255;
		angle2 = degrees;
		
		while (angle2 > 255) {
			angle1--;
			angle2 -= 255;
		}
		
		angle2 = 255 - angle2; 
		
	}
	
	if (degrees == 0) {
		angle1 = 0;
		angle2 = 0;
		speed1 = 0;
		speed2 = 0;
	}
	
	if (speed == 0) {
		angle1 = 0;
		angle2 = 0;
		speed1 = 0;
		speed2 = 0;
	}
	
	create_clear_serial_buffer();
	msleep(300);
	
	create_write_byte(128); //initializes mode to full
	waitByteSendInterval();
	create_write_byte(132);
	waitByteSendInterval();
	
	create_write_byte(152); //script size
	waitByteSendInterval();
	create_write_byte(13);
	waitByteSendInterval();
	
	create_write_byte(137); //spin
	waitByteSendInterval();
	create_write_byte(speed1);
	waitByteSendInterval();
	create_write_byte(speed2);
	waitByteSendInterval();
	create_write_byte(0);
	waitByteSendInterval();
	create_write_byte(0);
	waitByteSendInterval();
	
	create_write_byte(157); //wait angle
	waitByteSendInterval();
	create_write_byte(angle1);
	waitByteSendInterval();
	create_write_byte(angle2);
	waitByteSendInterval();
	
	create_write_byte(137); //stop
	waitByteSendInterval();
	create_write_byte(0);
	waitByteSendInterval();
	create_write_byte(0);
	waitByteSendInterval();
	create_write_byte(0);
	waitByteSendInterval();
	create_write_byte(0);
	waitByteSendInterval();
	create_write_byte(153);
	
}

void runIRCalibrationUtility() { // THIS HAS BEEN FIXED TO WORK WITH JUST ELEVATOR SENSOR
	
	int calibrationSuccessful = 0;
	
	while (!calibrationSuccessful) {
		
		int min, max, range;
		int sum, currentValue;
		int n = 30;
		int i;
		
		// START OF GETTING FIRST VALUES
		
		console_clear();
		printf("Please lift the elevator until the IR sensor is uninterrupted, then press \"Ready\"...\n\n");
		set_a_button_text("");
		set_b_button_text("Ready");
		set_c_button_text("");
		
		while (!b_button()) msleep(10);
		
		console_clear();
		printf("---- GETTING ELEVATOR_RAISED VALUES ----\n\n");
		set_a_button_text("");
		set_b_button_text("");
		set_c_button_text("");
		
		sum = 0;
		
		for (i = 0; i < n; i++) {
			currentValue = analog10(ELEVATOR_IR);
			printf("Value %d: %d\n", i + 1, currentValue);
			sum += currentValue;
			msleep(50);
		}
		
		max = sum / n;
		
		// START OF GETTING SECOND VALUES
		
		console_clear();
		printf("\n\n\nThe average value recieved was %d.\n", max);
		printf("\nPlease release the elevator and let it settle all the way to the ground, then press \"Ready\"...\n\n");
		set_a_button_text("");
		set_b_button_text("Ready");
		set_c_button_text("");
		
		while (!b_button()) msleep(10);
		
		console_clear();
		printf("---- GETTING ELEVATOR_LOWERED VALUES ----\n\n");
		set_a_button_text("");
		set_b_button_text("");
		set_c_button_text("");
		
		sum = 0;
		
		for (i = 0; i < n; i++) {
			currentValue = analog10(ELEVATOR_IR);
			printf("Value %d: %d\n", i + 1, currentValue);
			sum += currentValue;
			msleep(50);
		}
		
		min = sum / n;
		
		// DONE GETTING VALUES
		
		console_clear();
		printf("\n\nValues: %d, %d\n\n", min, max);
		printf("Are these values acceptable? If values make sense but are too extreme, press \"normalize\".");
		set_a_button_text("YES");
		set_b_button_text("NORMALIZE");
		set_c_button_text("NO");
		
		int normalize = 0;
		
		while (1) {
			msleep(10);
			if (a_button()) {
				calibrationSuccessful = 1;
				break;
			} else if (b_button()) {
				calibrationSuccessful = 1;
				normalize = 1;
				break;
			} else if (c_button()) {
				calibrationSuccessful = 0;
				break;
			}
		}
		
		console_clear();
		
		if (!calibrationSuccessful) {
			
			continue; //Restart loop if bad values....
			
			} else if (normalize) {
			
			printf("Normalizing values...\n\n");
			
			setNormalizedIRValues(min, max);
			
			printf("Normalized values:\ %d, %d\n\n", ELEVATOR_IR_MIN, ELEVATOR_IR_MAX);
			printf("Are these values acceptable?");
			set_a_button_text("YES");
			set_b_button_text("");
			set_c_button_text("NO");
			
			while (1) {
				
				msleep(10);
				
				if (a_button()) {
					calibrationSuccessful = 1;
					break;
					} else if (c_button()) {
					calibrationSuccessful = 0;
					break;
				}
				
			}
			
			msleep(250);
			
			if (calibrationSuccessful && irValuesAreSketchy) {
				
				console_clear();
				printf("NOTE: These values have a range that is below the specified acceptable limit.");
				printf("Are you sure you want to accept?");
				set_a_button_text("YES");
				set_b_button_text("");
				set_c_button_text("NO");
				
				while (1) {
					
					msleep(10);
					
					if (a_button()) {
						calibrationSuccessful = 1;
						break;
						} else if (c_button()) {
						calibrationSuccessful = 0;
						break;
					}
					
				}
				
			} 
			
			if (!calibrationSuccessful)	{
				console_clear();
				printf("Would you like to try to run the IR calibration utility again, or simply use the default values?");
				set_a_button_text("RESTART");
				set_b_button_text("");
				set_c_button_text("DEFAULT");
				while (1) {
					msleep(10);
					if (a_button()) {
						calibrationSuccessful = 0;
						break;
						} else if (c_button()) {
						ELEVATOR_IR_MIN = ELEVATOR_IR_MIN_DEFAULT;
						ELEVATOR_IR_MAX = ELEVATOR_IR_MAX_DEFAULT;
						calibrationSuccessful = 1;
						break;
					}
				}
			}
			
		}
		
	}
	
}

void setNormalizedIRValues(int min, int max) {
	
	irValuesAreSketchy = 0;
	
	int range = abs(max - min);
	
	double rangeAsDouble = (double) range;
	
	int smallDelta = (int) (rangeAsDouble * 0.0500);
	int midDelta = (int) (rangeAsDouble * 0.1000);
	int largeDelta = (int) (rangeAsDouble * 0.2500);
	
	if ((max - largeDelta > min + largeDelta) 
	&& (range - 2 * largeDelta > IR_RANGE_MIN_REASONABLE) ) {
		max -= largeDelta;
		min += largeDelta;
	} else if ((max - midDelta > min + midDelta) 
	&& (range - 2 * midDelta > IR_RANGE_MIN_REASONABLE) ) {
		max -= midDelta;
		min += midDelta;
	} else if ((max - smallDelta > min + smallDelta) 
	&& (range - 2 * smallDelta > IR_RANGE_MIN_REASONABLE) ) {
		max -= smallDelta;
		min += smallDelta;
	}
	
	ELEVATOR_IR_MIN = min;
	ELEVATOR_IR_MAX = max;
	
}
