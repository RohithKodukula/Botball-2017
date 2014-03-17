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
		turnWithSerial(TURN_MID_SPEED, -90);
		//move out of starting box
		moveToDist(600, MOVE_MID_SPEED);
		//turn to face left side of game board
		turnWithSerial(TURN_MID_SPEED, -90);
		//move to blue box
		moveToDist(300, MOVE_MID_SPEED);
		msleep(100);
		//capture blue box with lower claw
		setLowerClaw(LOWER_CLAW_CLOSED_BLOCK);
		raiseArm(1500);
		moveToDist(460, MOVE_MID_SPEED);
		//turn to face wide side of game board
		turnWithSerial(TURN_MID_SPEED,-90);
		//moveToDist(730, MOVE_MID_SPEED);
		//wall align
		moveToWallAlign(780, MOVE_MID_SPEED, 3.75);
		//back up after wall align
		moveToDist(-300,MOVE_MID_SPEED);
		lowerArmBySensor();
		//release blue box
		setLowerClaw(LOWER_CLAW_OPEN);
		msleep(500);
		//push blue box to wall
		moveToDist(122,MOVE_MID_SPEED);
		//back up after pushing blue box to wall
		moveToDist(-200,MOVE_MID_SPEED);
		//turn to face left wall
		turnWithSerial(TURN_MID_SPEED, 90);
		moveToDist(220, MOVE_MID_SPEED);
		//raise arm while turning to face orange boxes
		thread t = thread_create(raiseArmToTop);
		thread_start(t);
		//turnWithSerial(TURN_SLOW_SPEED, 90);
		turnWithSerial(TURN_SLOW_SPEED, 80);
		msleep(1000);
		thread_destroy(t);
		msleep(500);
		int angle = centerCameraFast(0);
		msleep(1000);
		int x;
		x = getMillimeterDistance();
		while (x > 150) {
			moveToDist(50, MOVE_SLOW_SPEED);
			x = getMillimeterDistance();
			msleep(500);
		}
		moveToDist(x-30, MOVE_SLOW_SPEED); //move until 3 cm away
		msleep(1000);
		//capture orange box in upper claw
		setUpperClaw(UPPER_CLAW_CLOSED);
		msleep(1000);
		//back up from orange boxes
		moveToDist(-300, MOVE_MID_SPEED);
		//compensate for camera turn
		thread t2 = thread_create(lowerArmBySensor);
		thread_start(t2);
		//turnWithSerial(TURN_SLOW_SPEED, 90);
		turnWithSerial(TURN_MID_SPEED - 10, -90 - angle);
		//thread_destroy(t2);		//turn to face left wall
		//wall align
		moveToWallAlign(800, MOVE_MID_SPEED, 2.0);
		moveToDist(-90, MOVE_SLOW_SPEED);
		//turn to face tubes
		turnWithSerial(TURN_MID_SPEED, -90);
		/*moveToDist(x - 600, MOVE_SLOW_SPEED);
		setUpperClaw(UPPER_CLAW_CLOSED);
		moveToDist(-300,MOVE_MID_SPEED);*/
		//wall align on tube wall
		moveToWallAlign(900, MOVE_MID_SPEED, 1.5);
		msleep(500);
		//capture tube in lower claw
		setLowerClaw(LOWER_CLAW_CLOSED_PIPE);
		msleep(500);
		//drop orange box into tube below
		setUpperClaw(UPPER_CLAW_OPEN);
		//release tube in lower claw
		setLowerClaw(LOWER_CLAW_OPEN);
		//back up from tube wall
		moveToDist(-300, MOVE_MID_SPEED);
		//turn to face left wall
		turnWithSerial(TURN_MID_SPEED, 90);
		//back up to position to turn to view orange block
		moveToDist(-190, MOVE_MID_SPEED);
		//raise arm while turning to face orange boxes
		thread t3 = thread_create(raiseArmToTop);
		thread_start(t3);
		turnWithSerial(TURN_SLOW_SPEED, 90);
		msleep(500);
		thread_destroy(t3);
		angle = centerCameraFast(0);
		msleep(500);
		x = getMillimeterDistance();
		while (x > 150) {
			moveToDist(50, MOVE_SLOW_SPEED);
			x = getMillimeterDistance();
			msleep(500);
		}
		moveToDist(x-30, MOVE_SLOW_SPEED); //move until 3 cm away
		msleep(1000);
		//capture remaining orange box in upper claw
		setUpperClaw(UPPER_CLAW_CLOSED);
		msleep(500);
		//pull away from orange box starting position
		moveToDist(-300, MOVE_MID_SPEED);
		//compensate for camera turn
		thread t4 = thread_create(lowerArmBySensor);
		thread_start(t4);
		//turnWithSerial(TURN_SLOW_SPEED, 90);
		turnWithSerial(TURN_MID_SPEED -10, -90 - angle);
		//thread_destroy(t4);
		moveToWallAlign(800, MOVE_MID_SPEED, 2.0);
		//back up from wall align on left wall
		moveToDist(-90, MOVE_SLOW_SPEED);
		//rotate to face tubes
		turnWithSerial(TURN_MID_SPEED, -90);
		/*moveToDist(x - 600, MOVE_SLOW_SPEED);
		setUpperClaw(UPPER_CLAW_CLOSED);
		moveToDist(-300,MOVE_MID_SPEED);*/
		//wall align on tube wall
		moveToWallAlign(1000, MOVE_MID_SPEED, 1.5);
		msleep(500);
		//capture tube in lower claw
		setLowerClaw(LOWER_CLAW_CLOSED_PIPE);
		msleep(1000);
		//drop orange box into pipe
		setUpperClaw(UPPER_CLAW_OPEN);
		msleep(1000);
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
	initActuators();
	cameraInitialize();

	//sweepToFindLargestBlock(0,45);
	//raiseArm(ARM_TOP_POS);
	//centerCameraFast(0);
	/*while (1) {
		printf("\n%d",getLargestBlobArea(0));

	}
	*/
	//rotate(TURN_MID_SPEED, -90);
	
	routine();
	
	/*while(1)
	{
		printf("distance = %f\n", getMillimeterDistance());
	}*/
	return 0;
}


