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





int main() {

	void routine()
	{
		createInit();
		initActuators();
		turnWithSerial(TURN_MID_SPEED, -90);
		moveToDist(600, MOVE_MID_SPEED);
		turnWithSerial(TURN_MID_SPEED, -90);
		moveToDist(250, MOVE_MID_SPEED);
		msleep(100);
		setLowerClaw(LOWER_CLAW_CLOSED_BLOCK);
		raiseArm(1000);
		moveToDist(500, MOVE_MID_SPEED);
		turnWithSerial(TURN_MID_SPEED, -90);
		moveToDist(700, MOVE_MID_SPEED);
		moveToDist(-300,MOVE_MID_SPEED);
		setLowerClaw(LOWER_CLAW_OPEN);
		msleep(500);
		lowerArmBySensor();
		turnWithSerial(TURN_MID_SPEED, 90);
		moveToDist(200, MOVE_MID_SPEED);
		thread t = thread_create(raiseArmToTop);
		thread_start(t);
		//turnWithSerial(TURN_SLOW_SPEED, 90);
		turnWithSerial(TURN_SLOW_SPEED, 90);
		thread_destroy(t);
		printf("continuing");
		msleep(1000);
		printf("continuing");
		centerCameraFast(0,getLargestBlob(0));
		msleep(500);
		int x;
		x = getMillimeterDistance();
		x = getMillimeterDistance();
		printf("distance to move: %d", x);
		moveToDist(x - 10, MOVE_SLOW_SPEED);
		setUpperClaw(UPPER_CLAW_CLOSED);
		moveToDist(-300,MOVE_MID_SPEED);
	}
	cameraInitialize();
	routine();
	return 0;
	
}


