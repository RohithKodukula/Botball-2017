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
			moveWithSerial(350, 1000);
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



void multipleBlockTestingUtility(){
	
	console_clear();
	
	printf("--------MULTIPLE LEVEL BLOCK TESTING UTILITY--------\n");
	printf("\n\t  Side Button ---- Check for blocks on both levels.\n\n");
	set_a_button_text("Block Vision");
	
	
	while (1) {
		
		if (a_button()) {
			console_clear();
			
			printf("running...\n");
			
			msleep(500);
			
			point2 bestBlobLocation = cameraSeesBigOranges();
			
			moveToBestBlob(bestBlobLocation);
			
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
			
			/*
			point2 bestBlobLocation = cameraSeesBigOranges();
			
			if (bestBlobLocation.x > 0 && bestBlobLocation.y > 0) {
			moveToBestBlob(bestBlobLocation);
			}
			*/
			
			
		}
		
		if (a_button()) {
			console_clear();
			
			printf("running...\n");
			
			raiseArmToBetween();
			
			msleep(500);
			
			point2 bestBlobLocation = cameraSeesBigOranges();
			
			moveToBestBlob(bestBlobLocation);
			
		}
		
		msleep(100);
		
	}
}


void routine()
{
	setDeltaAngle(0);
	setDeltaDistance(0);
	
	double initialTime = seconds();
	
	turnWithSerial(TURN_MID_SPEED, -45);
	moveWithSerial(MOVE_MID_SPEED + 40, 280);
	turnWithSerial(TURN_MID_SPEED, -53);
	
	raiseArmToBetween();
	point2 bestBlobLocation = cameraSeesBigOranges();
	
	if (bestBlobLocation.x > 0 && bestBlobLocation.y > 0) {
		moveToBestBlob(bestBlobLocation);
		moveWithSerial(MOVE_MID_SPEED, 300);
		setDeltaDistance(getDeltaDistance() + 300);
		captureOrangeBlock();
		lowerArmBySensor();
		moveWithSerial(MOVE_MID_SPEED, 330);
		turnWithSerial(TURN_MID_SPEED, -95);
		moveWithSerial(MOVE_MID_SPEED, 360);
		
	} else {
		lowerArmBySensor();
		moveWithSerial(MOVE_MID_SPEED, 400);
		turnWithSerial(TURN_MID_SPEED, -95);
		moveWithSerial(MOVE_MID_SPEED, 300);
	}
	
	msleep(500);
	
	moveBlueCube();
	
	//raise arm while turning to face orange boxes
	thread t = thread_create(raiseArmToTop);
	thread_start(t);
	arcToBlockCapturePosition();
	msleep(8000);
	thread_destroy(t);
	msleep(100);
	turnWithSerial(200, -8);
	int angle2 = sweepForOrange();
	printf("\nangle2: %d\n", angle2);
	msleep(100);
	int angle = centerCameraFast(0);
	printf("\nangle: %d\n", angle);
	
	
	
	/*
	
	int x;
	x = getMillimeterDistance();
	
	while (x > 150) {
	moveToDist(30, MOVE_SLOW_SPEED);
	x = getMillimeterDistance();
	msleep(150);
	}
	
	moveToDist(x-45, MOVE_SLOW_SPEED); //move until 6 cm away
	msleep(500);
	raiseArm(15);
	//capture orange box in upper claw
	msleep(300);
	setUpperClaw(UPPER_CLAW_CLOSED);
	msleep(100);
	setUpperClaw(UPPER_CLAW_OPEN);
	msleep(100);
	setUpperClaw(UPPER_CLAW_CLOSED);
	msleep(200);
	raiseArm(50);
	msleep(200);
	//Raise arm slightly to pull away from surface
	//raiseArm(500);
	//back up from orange boxes
	moveToDist(-70, MOVE_SLOW_SPEED);
	msleep(100);
	moveToDist(-180, MOVE_MID_SPEED - 10);
	//compensate for camera turn
	thread t2 = thread_create(lowerArmBySensor);
	thread_start(t2);
	//turnWithSerial(TURN_SLOW_SPEED, 90);
	printf("\nturn compensation: %d\n", -74 - (angle + angle2));
	//<<<<<<< HEAD
	turnWithSerial(200, -90 - (angle + angle2));
	//=======
	rotate(TURN_MID_SPEED - 10, -84 - (angle + angle2));
	//>>>>>>> FETCH_HEAD
	msleep(3500);
	//thread_destroy(t2);		//turn to face left wall
	/*thread_destroy(t2);
	printf("SHOULD BE D-STROYED\n");
	
	*/
	
	//wall align
	moveToWallAlign(1000, MOVE_MID_SPEED, 3.0);
	moveToDist(-90, MOVE_SLOW_SPEED);
	//turn to face tubes
	turnWithSerial(200, -90);
	//wall align on tube wall
	moveToWallAlign(1100, MOVE_MID_SPEED, 2.5);
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
	turnWithSerial(200, 90);
	//back up to position to turn to view orange block
	moveToDist(-200, MOVE_MID_SPEED); //was -150
	
	//raise arm while turning to face orange boxes
	
	/*
	GO FOR BLOCK 2
	*/
	
	thread t3 = thread_create(raiseArmToBetween);
	thread_start(t3);
	turnWithSerial(200, 90);
	msleep(7000);
	//rotate(TURN_SLOW_SPEED + 10, 90);
	//msleep(4000);
	thread_destroy(t3);
	moveWithSerial(200, 30);
	
	bestBlobLocation = cameraSeesBigOranges();
	
	if (bestBlobLocation.x > 0 && bestBlobLocation.y > 0) {
		moveToBestBlob(bestBlobLocation);
		captureOrangeBlock();
	}
	
	/*
	
	angle2 = sweepForOrange();
	printf("\nangle2: %d\n", angle2);
	msleep(100);
	angle = centerCameraFast(0);
	printf("\nangle: %d\n", angle);
	//msleep(500);
	x = getMillimeterDistance();
	while (x > 150) {
		moveWithSerial(250, 500);
		x = getMillimeterDistance();
		msleep(150);
	}
	moveToDist(x-45, MOVE_SLOW_SPEED); 				//move until 6 cm away
	msleep(500);									//capture remaining orange box in upper claw
	raiseArm(15);
	msleep(300);
	setUpperClaw(UPPER_CLAW_CLOSED);
	msleep(100);
	setUpperClaw(UPPER_CLAW_OPEN);
	msleep(100);
	setUpperClaw(UPPER_CLAW_CLOSED);
	msleep(250);
	raiseArm(50);
	msleep(200);
	//pull away from orange box starting position
	moveToDist(-90, MOVE_SLOW_SPEED);
	msleep(100);
	moveToDist(-180, MOVE_MID_SPEED - 10);
	//compensate for camera turn
	thread t4 = thread_create(lowerArmBySensor);
	thread_start(t4);
	printf("\nturn compensation: %d\n", -84 - (angle + angle2));
	turnWithSerial(200, -74 - (angle + angle2));
	rotate(TURN_MID_SPEED -10, -74 - (angle + angle2));
	msleep(3500);
	
	*/
	
	
	//adding more comments for fun
	moveToWallAlign(1000, MOVE_MID_SPEED, 3.0);
	//back up from wall align on left wall
	moveToDist(-90, MOVE_SLOW_SPEED);
	//turn to face tubes
	turnWithSerial(200, -90);
	/*moveToDist(x - 600, MOVE_SLOW_SPEED);
	setUpperClaw(UPPER_CLAW_CLOSED);
	moveToDist(-300,MOVE_MID_SPEED);*/
	//wall align on tube wall
	moveToWallAlign(1100, MOVE_MID_SPEED, 2.5);
	msleep(500);
	//capture tube in lower claw
	setLowerClaw(LOWER_CLAW_CLOSED_PIPE);
	msleep(500);
	//drop orange box into pipe
	setUpperClaw(UPPER_CLAW_OPEN);
	
	//release tube in lower claw
	setLowerClaw(LOWER_CLAW_OPEN);
	//back up from tube wall
	/*
	msleep(800);
	moveToDist(-300, MOVE_FAST_SPEED);
	<<<<<<< HEAD
	//turn towards wall
	=======
	//rotate towards wall
	>>>>>>> FETCH_HEAD
	rotate(TURN_MID_SPEED, -80);
	moveToDist(40,MOVE_FAST_SPEED);
	//yolo
	if(seconds() - initialTime < 0) { //105.0
	
	arcToPinkTape();
	msleep(6000);
	setLowerClaw(LOWER_CLAW_STRANGLE_BOT_GUY);
	
	raiseArm(400);
	
	thread t6 = thread_create(raiseArmToBlueBlockHeight);
	thread_start(t6);
	
	moveToDist(-830,MOVE_FAST_SPEED);
	
	
	msleep(500);
	
	rotate(TURN_FAST_SPEED, -186);
	msleep(500);
	//setLowerClaw(LOWER_CLAW_OPEN);
	//moveToDist(800,MOVE_FAST_SPEED);
	
	}
	*/
	/*
	//wall align
	//moveToWallAlign(700, MOVE_MID_SPEED, 3.0);
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

void moveBlueCube() {
	
	/*
	
	//turn to face left side of game board
	turnWithSerial(200, -90);
	moveToDist(300, MOVE_MID_SPEED); //move to blue box
	msleep(100); //capture blue box with lower claw
	
	*/
	
	setLowerClaw(LOWER_CLAW_CLOSED_BLOCK);
	thread t5 = thread_create(raiseArmTo250);
	thread_start(t5); //bring blue block to tape
	arcToPinkTape();
	msleep(4000);
	thread_destroy(t5);
	lowerArmBySensor(); //release blue box
	setLowerClaw(LOWER_CLAW_OPEN);
	msleep(500); //nudge blue box
	moveToDist(80, MOVE_MID_SPEED);
	moveToDist(-70, MOVE_MID_SPEED);
}

int main() {
	
	
	createInit();
	printf("\nBattery Capacity: %d", get_create_battery_capacity());
	printf("\nBattery Charge: %d", get_create_battery_charge());
	printf("\nBattery Temp: %d", get_create_battery_temp());
	initActuators();
	cameraInitialize();
	
	//raiseArmToBetween();
	
	routineTestingUtility();
	
	//shut_down_in(119.5);
	//routine();
	
	/*
	int x = 0;
	
	while(1) {
	turnWithSerial(200, 90);
	msleep(500);
	x++;
	printf("\nTurns: %d", x);
	}
	*/
	
	//printf("Waiting for light\n");
	//printf("See light, starting routine\n");
	
	/*
	wait_for_light(LIGHT_SENSOR_PORT);
	printf("see light, starting\n");
	shut_down_in(119.5);//119.5
	routine();
	*/
	
	
	
	
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
