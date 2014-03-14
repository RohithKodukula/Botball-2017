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
		rotate(TURN_MID_SPEED, -90);
		moveToDist(600, MOVE_MID_SPEED);
		rotate(TURN_MID_SPEED, -90);
		moveToDist(270, MOVE_MID_SPEED);
		msleep(100);
		setLowerClaw(LOWER_CLAW_CLOSED_BLOCK);
		raiseArm(1500);	//was 1000
		moveToDist(500, MOVE_MID_SPEED);
		rotate(TURN_MID_SPEED, -90);
		moveToDist(700, MOVE_MID_SPEED);
		moveToDist(-300,MOVE_MID_SPEED);//was -300
		lowerArmBySensor();
		setLowerClaw(LOWER_CLAW_OPEN);
		msleep(500);
		moveToDist(180,MOVE_MID_SPEED);//pushes block to edge
		moveToDist(-400,MOVE_MID_SPEED);//
		rotate(TURN_MID_SPEED, 70);//was 90
		moveToDist(180, MOVE_MID_SPEED);//was 215
		thread t = thread_create(raiseArmToTop);
		thread_start(t);
		//turnWithSerial(TURN_SLOW_SPEED, 90);
		rotate(TURN_SLOW_SPEED, 90);
		thread_destroy(t);
		printf("continuing");
		msleep(1500);
		printf("continuing");
		centerCameraFast(0);
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
		setUpperClaw(UPPER_CLAW_CLOSED);
		msleep(1000);
		moveToDist(-400, MOVE_MID_SPEED);
		lowerArmBySensor();
		rotate(TURN_SLOW_SPEED, -90);
		moveToDist(550, MOVE_MID_SPEED);
		/*moveToDist(x - 600, MOVE_SLOW_SPEED);
		setUpperClaw(UPPER_CLAW_CLOSED);
		moveToDist(-300,MOVE_MID_SPEED);*/
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


