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
		rotate(TURN_MID_SPEED, -90);
		//moveToDist(730, MOVE_MID_SPEED);
		//wall align
		moveToWallAlign(780, MOVE_MID_SPEED, 4.5);
		//back up after wall align
		moveToDist(-300,MOVE_MID_SPEED);
		lowerArmBySensor();
		//release blue box
		setLowerClaw(LOWER_CLAW_OPEN);
		msleep(500);
		//push blue box to wall
		moveToDist(115,MOVE_MID_SPEED);
		//back up after pushing blue box to wall
		moveToDist(-300,MOVE_MID_SPEED);
		//turn to face left wall
		rotate(TURN_MID_SPEED, 75);
		moveToDist(150, MOVE_MID_SPEED);
		//raise arm while turning to face orange boxes
		thread t = thread_create(raiseArmToTop);
		thread_start(t);
		//turnWithSerial(TURN_SLOW_SPEED, 90);
		rotate(TURN_SLOW_SPEED, 75);
		thread_destroy(t);
		msleep(1500);
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
		rotate(TURN_SLOW_SPEED, -angle);
		lowerArmBySensor();
		//turn to face left wall
		rotate(TURN_MID_SPEED, -90);
		//wall align
		moveToDist(400, MOVE_SLOW_SPEED);
		moveToDist(-90, MOVE_SLOW_SPEED);
		//turn to face tubes
		rotate(TURN_MID_SPEED, -90);
		/*moveToDist(x - 600, MOVE_SLOW_SPEED);
		setUpperClaw(UPPER_CLAW_CLOSED);
		moveToDist(-300,MOVE_MID_SPEED);*/
		//wall align on tube wall
		moveToWallAlign(1000, MOVE_SLOW_SPEED, 4.5);
		msleep(500);
		//capture tube in lower claw
		setLowerClaw(LOWER_CLAW_CLOSED_PIPE);
		msleep(1000);
		//drop orange box into tube below
		setUpperClaw(UPPER_CLAW_OPEN);
		//release tube in lower claw
		setLowerClaw(LOWER_CLAW_OPEN);
		//back up from tube wall
		moveToDist(-300, MOVE_MID_SPEED);
		//turn to face left wall
		turnWithSerial(TURN_MID_SPEED, 90);
		//advance to left wall
		moveToDist(-150, MOVE_MID_SPEED);
		//raise arm while turning to face orange boxes
		thread t2 = thread_create(raiseArmToTop);
		thread_start(t2);
		turnWithSerial(TURN_SLOW_SPEED, 90);
		msleep(2000);
		thread_destroy(t2);
		angle = centerCameraFast(0);
		msleep(1000);
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
		msleep(1000);
		//pull away from orange box starting position
		moveToDist(-300, MOVE_MID_SPEED);
		//compensate for camera turn
		rotate(TURN_SLOW_SPEED, -angle);
		lowerArmBySensor();
		//rotate to face left wall
		rotate(TURN_MID_SPEED, -90);
		//wall align on left wall
		moveToDist(400, MOVE_SLOW_SPEED);
		//back up from wall align on left wall
		moveToDist(-90, MOVE_SLOW_SPEED);
		//rotate to face tubes
		rotate(TURN_MID_SPEED, -90);
		/*moveToDist(x - 600, MOVE_SLOW_SPEED);
		setUpperClaw(UPPER_CLAW_CLOSED);
		moveToDist(-300,MOVE_MID_SPEED);*/
		//wall align on tube wall
		moveToWallAlign(1000, MOVE_SLOW_SPEED, 4.5);
		msleep(500);
		//capture tube in lower claw
		setLowerClaw(LOWER_CLAW_CLOSED_PIPE);
		msleep(1000);
		//drop orange box into pipe
		setUpperClaw(UPPER_CLAW_OPEN);
		
		
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


