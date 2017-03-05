
#include "createFunctions.h"
#include "createConstants.h"
#include "createVision.h"

//NEW CUBE POSITION!!!!!

int main() {
	
	/*
	clear_motor_position_counter(LEFT_ARM_MOTOR);
	printf("Press b to continue\n");
	while(!b_button()){msleep(10);}
	lowerArmToBottom();
	msleep(1000);
	raiseArm(ARM_SUPER_HIGH);
	msleep(1000);
	int i;
	for(i = 0; i < 20; i++){
		raiseArm(200);
		printf("Current arm position: %d\n", get_motor_position_counter(LEFT_ARM_MOTOR));
		msleep(1000);
	}
	msleep(5000);*/
	/*
	Cubes:
	Close corner: ?cm from pipe
	Far corner: ?cm from pipe
	
	*/
	/*
	raiseArmPastSensor();
	msleep(1000);
	lowerArmToBottom();
	msleep(500);
	raiseArm(ARM_CUBE_LOW);
	printf(" CUBE LOW Right: %d, Left: %d\n", get_motor_position_counter(RIGHT_ARM_MOTOR), get_motor_position_counter(LEFT_ARM_MOTOR));
	msleep(5000);
	raiseArm(ARM_LOW);
	printf(" LOW Right: %d, Left: %d\n", get_motor_position_counter(RIGHT_ARM_MOTOR), get_motor_position_counter(LEFT_ARM_MOTOR));
	msleep(5000);
	lowerArmToBottom();
	msleep(500);
	raiseArm(ARM_MID);
	printf("MID Right: %d, Left: %d\n", get_motor_position_counter(RIGHT_ARM_MOTOR), get_motor_position_counter(LEFT_ARM_MOTOR));
	msleep(5000);
	lowerArmToBottom();
	msleep(500);
	raiseArm(ARM_HIGH);
	printf("HIGH Right: %d, Left: %d\n", get_motor_position_counter(RIGHT_ARM_MOTOR), get_motor_position_counter(LEFT_ARM_MOTOR));
	msleep(5000);
	lowerArmToBottom();
	msleep(500);
	raiseArm(ARM_SUPER_HIGH);
	printf("SUPER HIGH Right: %d, Left: %d\n", get_motor_position_counter(RIGHT_ARM_MOTOR), get_motor_position_counter(LEFT_ARM_MOTOR));
	msleep(5000);
	lowerArmToBottom();
	msleep(500);
	
	
	*/
	/*
	Cubes:
	Close corner: 7m from pipe
	Far corner: 9cm from pipe
	
	*/
	
	routine();
	return 0;
	
}

//            ---------------------- ROUTINE START ----------------------

void routine() {
	
	//ELEVATOR_IR_MIN = ELEVATOR_IR_MIN_DEFAULT;
	//ELEVATOR_IR_MAX = ELEVATOR_IR_MAX_DEFAULT;
	
	int distToSecondPost = 275;
	int distToThirdPost = 296;
	
	createInit();
	enable_servos();
	
	closeFrontClaw();
	//openPongClaw();
	raiseArmPastSensor();
	msleep(500);
	lowerArmToBottom();
	msleep(500);
	//raiseElevator(200);
	//lowerElevatorToBottom();
	//msleep(500);
	//raiseElevator(ELEVATOR_TOP - 350);
	//msleep(500);
	
	/*
	int calibrated = 0;
	int lightLevel = 0;
	double lightLevelAsDouble = 0.0;
	int z;
	
	while (!calibrated) {
		
		console_clear();
		printf("Press \"Ready\" when the light intensity bar reaches top two bars.\n\nLight level:\n");
		
		lightLevelAsDouble = (1.0000 - ( (double) analog10(LIGHT_SENSOR) / 1024.0000 )) * 8.0000;
		lightLevel = (int) lightLevelAsDouble;
		
		
		for (z = 0; z < lightLevel; z++) {
			
		}
		
		
		printf("current lightlevel: %d\n", lightLevel);
		
		msleep(50);
		
	}
	*/
	
	printf("Flash light to continue\n");
	while(analog10(LIGHT_SENSOR)>200){msleep(10);}
	msleep(200);
	while(analog10(LIGHT_SENSOR)>200){msleep(10);} //double check
	shut_down_in(119);
	msleep(3000);
	//lowerElevatorToBottom();
	//msleep(2000);
	
	//closePongClaw();
	raiseArm(ARM_CUBE_LOW);
	msleep(500);
	turnWithSerial(150, -33);
	msleep(3000);
	openFrontClaw();
	msleep(500);
	
	//move to cubes
	moveWithSerial(MOVE_MID_SPEED,220);
	msleep(1600);
	
	//grab cubes
	closeFrontClaw();
	msleep(300);
	
	//turn to face bin
	turnWithSerial(150, -32);
	msleep(2000);
	raiseArm(ARM_SUPER_HIGH - ARM_CUBE_LOW);
	msleep(500);
	moveWithSerial(MOVE_MID_SPEED, 640);
	msleep(5000);
	
	/*
	int i;
	for(i = 0; i < 2; i++){
		moveWithSerial(MOVE_FAST_SPEED, 5);
	}
	*/
	//msleep(2600);
		
	//raiseArm(15);
	//drop cubes in caldera
	
	openFrontClaw();
	//openPongClaw();
	msleep(500);
	
	// ---------- HERE IS EXPERIMENTAL STUFF -------------
	
	moveWithSerial(MOVE_MID_SPEED, -100);
	msleep(2000);
	lowerArm(300);
	turnWithSerial(150, -10);
	msleep(2000);
	moveWithSerial(MOVE_MID_SPEED, 100);
	msleep(500);
	closeFrontClaw();
	turnWithSerial(150, 10);
	msleep(2000);
	openFrontClaw();
	
	// ---------- END OF EXPERIMENTAL STUFF -------------
	
	
	//back up from bin
	moveWithSerial(MOVE_MID_SPEED, -500);
	msleep(4000);
	lowerArmToBottom();
	
	// ---------- END OF PONG-FREE ROUTINE -------------
	
	/*
	closeFrontClaw();
	turnWithSerial(150, 150);
	msleep(2000);
	
	moveWithSerial(MOVE_MID_SPEED, 290);
	msleep(3500);
	
	moveWithSerial(MOVE_MID_SPEED, -60);
	msleep(2000);
	
	turnWithSerial(100, 90);
	msleep(1500);
	
	moveWithSerial(MOVE_MID_SPEED - 75, -246);
	msleep(3000);
	
	turnWithSerial(100, -94);
	msleep(2000);
	*/
	
	/*
	moveWithSerial(MOVE_MID_SPEED - 75, 100);
	msleep(3000);
	*/
	
	//openPongClaw();
	
	
	/*
	moveWithSerial(MOVE_MID_SPEED - 75, -400);
	msleep(4000);
	
	lowerArmToBottom();
	raiseArm(ARM_HIGH + 300);
	*/
	
	/*
	moveWithSerial(MOVE_MID_SPEED, 200);
	msleep(4000);
	*/
	
	/*
	//closePongClaw();
	//raiseElevator(ELEVATOR_TOP);
	msleep(500);
	//openPongClaw();
	
	moveWithSerial(MOVE_MID_SPEED, -1 * distToThirdPost);
	msleep(4000);
	
	//lowerElevatorToBottom();
	lowerArmToBottom();
	raiseArm(ARM_MID + 300);
	//closePongClaw();
	//raiseElevator(ELEVATOR_TOP);
	msleep(500);
	//openPongClaw();
	
	moveWithSerial(MOVE_MID_SPEED, -1 * distToSecondPost);
	msleep(4000);
	
	//lowerElevatorToBottom();
	lowerArmToBottom();
	raiseArm(ARM_LOW);
	//closePongClaw();
	//raiseElevator(ELEVATOR_TOP);
	msleep(500);
	//openPongClaw();
	
	
	//lowerElevatorToBottom();
	msleep(1500);
	//raiseElevator(ELEVATOR_MID);
	//lowerArmToBottom(); // Also moveArmToLow() isn't working either
	//raiseArm(ARM_LOW);
	
	moveWithSerial(MOVE_MID_SPEED, 12);
	msleep(1000);
	
	//do the KAMEHAMEHA and sling the pongs into the bin
	
	raiseArm(ARM_SUPER_HIGH - 800);
	turnWithSerial(350, -78);
	msleep(3500);
	*/
	
	/*
	turnWithSerial(300, 78);
	msleep(2000);
	turnWithSerial(300, -78);
	msleep(5000);
	turnWithSerial(300, 78);
	msleep(2000);
	*/
	
	console_clear();
	printf("---- FINISHED ----");
	
	
	//lowerArmToBottom();
	/*
	console_clear();
	printf("I do good? :D\n");
	*/
	/*
	
	//get into cube shoving position
	closePongClaw();
	turnWithSerial(TURN_MID_SPEED, -34);
	lowerArm(800);
	msleep(1000);
	moveWithSerial(MOVE_MID_SPEED, 190);
	msleep(500);
	
	int numTurnAdjustments = 5;
	//int i; already initialized
	for(i = 0; i < numTurnAdjustments; i++){
		turnWithSerial(TURN_MID_SPEED, 14);
		moveWithSerial(MOVE_MID_SPEED, 5);
		msleep(100);
	}
	msleep(1000);
	lowerArm(100);
	msleep(3000);
	moveWithSerial(MOVE_MID_SPEED, 80);
	
	msleep(9000);
	moveWithSerial(MOVE_MID_SPEED,-250);
	lowerArmToBottom();
	
	
	//shove cubes into bin & hope for best
	
	//set up for ping pong routine
	printf("Press b to continue\n");
	while(!b_button()){msleep(10);}
	clear_motor_position_counter(RIGHT_ARM_MOTOR);
	clear_motor_position_counter(LEFT_ARM_MOTOR);
	while(1) {
		printf("Right: %d, Left: %d\n", get_motor_position_counter(RIGHT_ARM_MOTOR), get_motor_position_counter(LEFT_ARM_MOTOR));
	}
	
	raiseArm(500);
	lowerArmToBottom();
	raiseArm(ARM_LOW);
	
	console_clear();
	printf("Align it with first post and press ready.\n");
	set_a_button_text("");
	set_b_button_text("READY");
	set_c_button_text("");
	
	while(!b_button()) {}
	
	lowerArmToBottom();
	
	initializeFull();
	raiseArm(ARM_LOW);
	closePongClaw();
	msleep(600);
	moveElevatorToTop();
	openPongClaw();
	
	lowerElevatorToBottom();
	raiseArm(ARM_MID - ARM_LOW);
	
	//move to second pong post
	moveWithSerial(MOVE_MID_SPEED, distToSecondPost);
	msleep(3000);
	
	//get second pong
	closePongClaw();
	msleep(600);
	moveElevatorToPosition(ELEVATOR_TOP);
	openPongClaw();
	
	lowerElevatorToBottom();
	
	//moveArmToTop();
	raiseArm((ARM_HIGH - ARM_MID) + 200); // because moveArmToTop(); wasn't working
	
	//move to third pong post
	moveWithSerial(MOVE_MID_SPEED, distToThirdPost);
	msleep(5000);
	
	//get third pong
	closePongClaw();
	msleep(600);
	moveElevatorToPosition(ELEVATOR_TOP);
	openPongClaw();
	
	
	//move to pong slinging position
	moveWithSerial(-1 * MOVE_MID_SPEED, distToSecondPost + distToThirdPost - 200);
	lowerElevatorToBottom();
	msleep(1500);
	raiseElevator(ELEVATOR_MID);
	//lowerArmToBottom(); // Also moveArmToLow() isn't working either
	//raiseArm(ARM_LOW);
	
	//do the KAMEHAMEHA and sling the pongs into the bin
	raiseArm(ARM_SUPER_HIGH - ARM_HIGH);
	turnWithSerial(450, -80);
	msleep(5000);
	turnWithSerial(100, 120);
	msleep(2000);
	
	lowerElevatorToBottom();
	lowerArmToBottom();
	*/
	
	
	/*
	raiseArmPastSensor();
	lowerArmToBottom();
	raiseArm(ARM_LOW);
	
	console_clear();
	printf("Press \"Ready\" when the createbot's ball catcher is aligned to the first ping pong ball post.\n\n");
	set_a_button_text("");
	set_b_button_text("Ready");
	set_c_button_text("");
	
	while (!b_button()) { msleep(10); }
	
	console_clear();
	set_a_button_text("");
	set_b_button_text("");
	set_c_button_text("");
	
	initializeFull();
	
	msleep(500);
	raiseArm(ARM_LOW);
	closePongClaw();
	msleep(1000);
	moveElevatorToTop();
	openPongClaw();
	
	lowerElevatorToBottom();
	moveArmToMiddle();
	
	moveWithSerial(MOVE_SLOW_SPEED, distToSecondPost);
	msleep(5500);
	
	closePongClaw();
	moveElevatorToPosition(ELEVATOR_TOP);
	openPongClaw();
	
	lowerElevatorToBottom();
	
	//moveArmToTop();
	raiseArm((ARM_HIGH - ARM_MID) + 200); // because moveArmToTop(); wasn't working
	
	moveWithSerial(MOVE_SLOW_SPEED, distToThirdPost);
	msleep(6000);
	
	closePongClaw();
	moveElevatorToPosition(ELEVATOR_TOP);
	openPongClaw();
	
	moveWithSerial(-1 * MOVE_SLOW_SPEED, distToSecondPost + distToThirdPost - 200);
	lowerElevatorToBottom();
	msleep(5000);
	lowerArmToBottom(); // Also moveArmToLow() isn't working either
	//raiseArm(ARM_LOW);
	raiseArm(ARM_SUPER_HIGH);
	turnWithSerial(300, -80);
	msleep(5000);
	turnWithSerial(300, 80);
	lowerArmToBottom();
	*/
	
}

//            ---------------------- ROUTINE END ----------------------

void testingUtility() {
	printf("Press A to raise Arm 4990 ticks, B to lower arm by sensor, C to center, side button to exit");
	msleep(500);
	while (!side_button()) {
		if (a_button()) {
			raiseArm(4990);
			} else if (b_button()) {
			lowerArmToBottom();
			} else if (c_button()) { 
			centerCamera(0, 0);
		}
		msleep(100);
	}
}

void serialTestingUtility() {
	
	console_clear();
	
	set_a_button_text("Bytecode Move");
	set_b_button_text("Bytecode Turn");
	set_c_button_text("Testing Utility");
	
	printf("--------MAIN MENU--------\n");
	printf("\"Bytecode Move\"\n -- Test moving with bytecode functions\n\n");
	printf("\"Bytecode Turn\"\n -- Test turning with bytecode functions\n\n");
	printf("\"Testing Utility\"\n -- Enter the robot testing utilty");
	
	while (!side_button()) {
		
		if (a_button()) {
			printf("\n\nMoving to distance 100cm at speed 350 mm/s with serial function...\n\n");
			moveWithSerial(300, 1000);
			console_clear();
		}
		
		else if (b_button()) {
			
			console_clear();
			
			set_a_button_text("90");
			set_b_button_text("180");
			set_c_button_text("-90");
			
			printf("Press the desired degree angle to test. Side button returns to main menu.\n");
			msleep(250);
			
			while (!side_button()) {
				
				if (a_button()) {
					
					printf("\n\nTurning 90 degrees at speed 150 mm/s with serial function...\n\n");
					turnWithSerial(150, 90);
					
					} else if (b_button()) {
					
					printf("\n\nTurning 180 degrees at speed 150 mm/s with serial function...\n\n");
					turnWithSerial(150, 180);
					
					} else if (c_button()) {
					
					printf("\n\nTurning 180 degrees at speed 150 mm/s with serial function...\n\n");
					turnWithSerial(150, -90);
					
				}
				
			}
			msleep(100);
			
			console_clear();
			
			set_a_button_text("Bytecode Move");
			set_b_button_text("Bytecode Turn");
			set_c_button_text("Testing Utility");
			
			printf("--------MAIN MENU--------\n");
			printf("\"Bytecode Move\"\n -- Test moving with bytecode functions\n\n");
			printf("\"Bytecode Turn\"\n -- Test turning with bytecode functions\n\n");
			printf("\"Testing Utility\"\n -- Enter the robot testing utilty");
			
		}
		
		else if (c_button()) {
			testingUtility();
			console_clear();
		}
		msleep(100);
	}
}

void routineTestingUtility(){
	
	console_clear();
	
	printf("--------ROUTINE TESTING UTILITY--------\n");
	printf("\n\tSide Button ---- Run the full routine.\n\n");
	set_a_button_text("Block Vision");
	
	while (1) {
		
		if (side_button()) {
			
			printf("\n\nRunning routine...\n\n\n");
			
			msleep(500);
			
			routine();
			
		}
		
		msleep(100);
		
	}
	
}

void sensorTestingUtility() {
	
	int maxValue = -1;
	int minValue = 5000;
	
	while(!side_button()) {
		
		console_clear();
		set_a_button_text("");
		set_b_button_text("");
		set_c_button_text("");
		
		int i = 0;
		for(i = 0; i <= 7; i++) {
			printf("sensor %d: %d\n", i, analog10(i));
		}
		
		msleep(1000);
		
	}
}


