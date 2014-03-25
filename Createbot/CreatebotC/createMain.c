#include "createFunctions.h"
#include "createConstants.h"
#include "createVision.h"


void lowerArmAt(int power) {
	motor(ARM_PORT, power);
}

void stopArm() {
	off(ARM_PORT);
}

void mainMenu() {
	
	console_clear();
	
	set_a_button_text("Bytecode Move");
	set_b_button_text("Bytecode Turn");
	set_c_button_text("Testing Utility");
	
	printf("--------MAIN MENU--------\n");
		printf("\"Bytecode Move\"\n -- Test moving with bytecode functions\n\n");
		printf("\"Bytecode Turn\"\n -- Test turning with bytecode functions\n\n");
		printf("\"Testing Utility\"\n -- Enter the robot testing utilty");
	
}

void testingUtility() {
	printf("Press A to raise Arm 4990 ticks, B to lower arm by sensor, C to center, side button to exit");
	msleep(500);
	while (!side_button()) {
		if (a_button()) {
			raiseArm(4990);
		}
		
		else if (b_button()) {
			lowerArmBySensor();
		}
		
		else if (c_button()) { 
			centerCamera(0, 0);

		}
		msleep(100);
	}
}

void serialTestingUtility(){
	mainMenu();
	while (!side_button()) {
		
		if (a_button()) {
			printf("\n\nMoving to distance 100cm at speed 350 mm/s with serial function...\n\n");
			moveWithSerial(350, 100);
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
			mainMenu();
		}
		
		else if (c_button()) {
			testingUtility();
			console_clear();
		}
		msleep(100);
	}
}


void routine()
	{
		
		//turn out of starting box
		rotate(TURN_MID_SPEED, -90);
		//move out of starting box
		moveToDist(600, MOVE_MID_SPEED);
		//turn to face left side of game board
		rotate(TURN_MID_SPEED, -90);
		//move to blue box
		moveToDist(300, MOVE_MID_SPEED);
		msleep(100);
		//capture blue box with lower claw
		setLowerClaw(LOWER_CLAW_CLOSED_BLOCK);
		thread t5 = thread_create(raiseArmTo1500);
		thread_start(t5);
		arcToPinkTape();
		thread_destroy(t5);
		lowerArmBySensor();
		//release blue box
		setLowerClaw(LOWER_CLAW_OPEN);
		msleep(200);
		//nudge blue box
		moveToDist(60, MOVE_MID_SPEED);
		moveToDist(-60, MOVE_MID_SPEED);
		//raise arm while turning to face orange boxes
		thread t = thread_create(raiseArmToTop);
		thread_start(t);
		/*
		GO FOR BLOCK 1
		*/
		arcToBlockCapturePosition();
		//turnWithSerial(TURN_SLOW_SPEED, 90);
		msleep(1500);
		thread_destroy(t);
		//move to final block capture position
		moveToDist(70, MOVE_SLOW_SPEED);
		
		int angle2 = sweepForOrange();
		printf("\nangle2: %d\n", angle2);
		msleep(100);
		int angle = centerCameraFast(0);
		printf("\nangle: %d\n", angle);
		msleep(500);
		int x;
		x = getMillimeterDistance();
		
		while (x > 150) {
			moveToDist(30, MOVE_SLOW_SPEED);
			x = getMillimeterDistance();
			msleep(500);
		}
		
		moveToDist(x-45, MOVE_SLOW_SPEED); //move until 6 cm away
		msleep(500);
		raiseArm(100);
		//capture orange box in upper claw
		setUpperClaw(UPPER_CLAW_CLOSED);
		msleep(250);
		raiseArm(70);
		msleep(250);
		//Raise arm slightly to pull away from surface
		//raiseArm(500);
		//back up from orange boxes
		moveToDist(-50, MOVE_SLOW_SPEED);
		msleep(100);
		moveToDist(-200, MOVE_MID_SPEED - 10);
		//compensate for camera turn
		thread t2 = thread_create(lowerArmBySensor);
		thread_start(t2);
		//turnWithSerial(TURN_SLOW_SPEED, 90);
		printf("\nturn compensation: %d\n", -87 - (angle + angle2));
		rotate(TURN_MID_SPEED - 10, -87 - (angle + angle2));
		msleep(4000);
		//thread_destroy(t2);		//turn to face left wall
		/*thread_destroy(t2);
		printf("SHOULD BE D-STROYED\n");*/
		//wall align
		moveToWallAlign(800, MOVE_MID_SPEED, 2.0);
		moveToDist(-90, MOVE_SLOW_SPEED);
		//turn to face tubes
		rotate(TURN_MID_SPEED, -90);
		/*moveToDist(x - 600, MOVE_SLOW_SPEED);
		setUpperClaw(UPPER_CLAW_CLOSED);
		moveToDist(-300,MOVE_MID_SPEED);*/
		//wall align on tube wall
		moveToWallAlign(900, MOVE_MID_SPEED, 1.5);
		msleep(500);
		//capture tube in lower claw
		setLowerClaw(LOWER_CLAW_CLOSED_PIPE);
		msleep(750);
		//drop orange box into tube below
		setUpperClaw(UPPER_CLAW_OPEN);
		msleep(500);
		//release tube in lower claw
		setLowerClaw(LOWER_CLAW_OPEN);
		//back up from tube wall
		moveToDist(-120, MOVE_MID_SPEED);
		//turn to face left wall
		rotate(TURN_MID_SPEED, 90);
		//back up to position to turn to view orange block
		moveToDist(-200, MOVE_MID_SPEED); //was -150
		//raise arm while turning to face orange boxes
		/*
		GO FOR BLOCK 2
		*/
		thread t3 = thread_create(raiseArmToTop);
		thread_start(t3);
		rotate(TURN_SLOW_SPEED + 10, 90);
		msleep(1500);
		thread_destroy(t3);
		moveToDist(70, MOVE_SLOW_SPEED);
		angle2 = sweepForOrange();
		printf("\nangle2: %d\n", angle2);
		msleep(1000);
		angle = centerCameraFast(0);
		printf("\nangle: %d\n", angle);
		msleep(500);
		x = getMillimeterDistance();
		while (x > 150) {
			moveToDist(30, MOVE_SLOW_SPEED);
			x = getMillimeterDistance();
			msleep(500);
		}
		moveToDist(x-45, MOVE_SLOW_SPEED); //move until 6 cm away
		msleep(500);
		//capture remaining orange box in upper claw
		raiseArm(100);
		setUpperClaw(UPPER_CLAW_CLOSED);
		msleep(250);
		raiseArm(70);
		msleep(250);
		//Raise arm slightly to pull away from surface
		//raiseArm(500);
		//pull away from orange box starting position
		moveToDist(-50, MOVE_SLOW_SPEED);
		msleep(100);
		moveToDist(-200, MOVE_MID_SPEED - 10);
		//compensate for camera turn
		thread t4 = thread_create(lowerArmBySensor);
		thread_start(t4);
		//turnWithSerial(TURN_SLOW_SPEED, 90);
		printf("\nturn compensation: %d\n", -87 - (angle + angle2));
		rotate(TURN_MID_SPEED -10, -87 - (angle + angle2));
		msleep(4000);
		//thread_destroy(t4);
		//adding more comments for fun
		moveToWallAlign(800, MOVE_MID_SPEED, 2.0);
		//back up from wall align on left wall
		moveToDist(-90, MOVE_SLOW_SPEED);
		//rotate to face tubes
		rotate(TURN_MID_SPEED, -90);
		/*moveToDist(x - 600, MOVE_SLOW_SPEED);
		setUpperClaw(UPPER_CLAW_CLOSED);
		moveToDist(-300,MOVE_MID_SPEED);*/
		//wall align on tube wall
		moveToWallAlign(1000, MOVE_MID_SPEED, 1.5);
		msleep(500);
		//capture tube in lower claw
		setLowerClaw(LOWER_CLAW_CLOSED_PIPE);
		msleep(500);
		//drop orange box into pipe
		setUpperClaw(UPPER_CLAW_OPEN);
		/*
		//release tube in lower claw
		setLowerClaw(LOWER_CLAW_OPEN);
		//back up from tube wall
		moveToDist(-300, MOVE_MID_SPEED);
		//rotate towards wall
		turnWithSerial(TURN_MID_SPEED, 90);
		//wall align
		moveToWallAlign(700, MOVE_MID_SPEED, 3.0);
		//backup
		moveToDist(-300, MOVE_MID_SPEED);
		//rotate to center of board
		turnWithSerial(TURN_MID_SPEED, -180);
		//move to center of board
		moveToDist(650, MOVE_MID_SPEED);
		//turn to bot guy
		turnWithSerial(TURN_MID_SPEED, -90);
		//center camera on bot guy
		angle = centerCameraFast(1);
		//move to bot guy
		moveToDist(300, MOVE_SLOW_SPEED);
		//str4ngle bot guy
		setLowerClaw(LOWER_CLAW_STRANGLE_BOT_GUY);
		//back up from bot guy
		moveToDist(-100, MOVE_MID_SPEED);
		//raise arm so botguy doesn't drag
		raiseArm(1600);
		//turn -90
		turnWithSerial(TURN_MID_SPEED, -90);
		//move to block
		moveToDist(300, MOVE_MID_SPEED);
		//turn -90
		turnWithSerial(TURN_MID_SPEED, -90);
		//center on blue block
		angle = centerCameraFast(2);
		//wall align with block
		moveToWallAlign(1000, MOVE_MID_SPEED, 3.0);
		//lower botguy hopefully on block
		lowerArm(1200);
		//release botguy on block
		setLowerClaw(LOWER_CLAW_OPEN);
		//move back after putting botguy on block
		moveToDist(-100, MOVE_SLOW_SPEED);
		//lowers arm to bottom
		lowerArmBySensor();
		//moves toward botguy/block
		moveToDist(100, MOVE_SLOW_SPEED);
		//str4ngles botguy with upper claw
		setUpperClaw(UPPER_CLAW_STRANGLE_BOT_GUY);
		//grabs block with lower claw
		setLowerClaw(LOWER_CLAW_CLOSED_BLOCK);
		//raises arm to prevent dragging
		raiseArm(1500);
		//turns toward pink tape
		turnWithSerial(TURN_SLOW_SPEED, 90);
		//moves to pink tape
		moveToDist(200, MOVE_SLOW_SPEED);
		//lowers arm to place botguy/cube on ground
		lowerArmBySensor();
		*/
		
	}
	
int main() {
	createInit();
	printf("\n Battery Capacity: %d", get_create_battery_capacity());
	printf("\n Battery Charge: %d", get_create_battery_charge());
	printf("\n Battery Temp: %d", get_create_battery_temp());
	initActuators();
	cameraInitialize();
	//int x = 0;
	
	routine();
	
	/*while (x < 4) {
		rotate(TURN_MID_SPEED, -90);
		msleep(500);
		x++;
		printf("%d\n", x);
	}*/
	
	
	/*
	raiseArmToTop();
	
	
	while(1){
		if (b_button()) {
			sweepForOrange();
		}
		msleep(100);
	}
	
	
	while (1) {
		if (cameraSeesBigOrange()) {
			printf("%d: I see a block!\n", x);
			camera_update();
			msleep(500);
			printf("Area: %d\n", get_object_area(0,0));
		} else {
			printf("%d: I can't see a good block.\n", x);
		}
		x++;
	}
	*/
	
	//raiseArmToTop();
	
	//sweepToFindLargestBlock(0, 45);
	
	return 0;
	
}


