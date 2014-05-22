#include "legobotConstants.h"
#include "legobotFunctions.h"
#include "legobotVision.h"


void tribbleCollectTest() {
	
	printf("collecting test");
	legobotInit();
	printf("collecting test");
	motor(RIGHT_MOTOR, 40*1.05);
	motor(LEFT_MOTOR, 40);
	
	mav(SPINNER_MOTOR, 500);
	
	thread pomAlignerThread3;
	pomAlignerThread3 = thread_create(runPomAligner);
	thread_start(pomAlignerThread3);
	
	msleep(4000);
	
	halt();
	turn(-90.0);
	
	motor(RIGHT_MOTOR, 40*1.05);
	motor(LEFT_MOTOR, 40);
	
	msleep(5000);
	
	ao();
	msleep(1000);
	thread_destroy(pomAlignerThread3);
	
}

int main() {
	
	legobotInit();
	cameraInitialize();
	console_clear();
	mainMenu();
	
	

	//console_clear();
	printf("Running routine...\n\n");
	seeding(1);
	
}

int seeding(int kickChannel) {
	wait_for_light(LIGHT_SENSOR);
	shut_down_in(119.5);
	
	//wall align
	moveToWallAlign(NORMAL_SPEED);
	msleep(1000);
	
	//create and beging a pom collector thread
	thread spinnerThread = thread_create(spinnerStart);
	thread_start(spinnerThread);

	//move to beginning of route
	pivotOnLeft(NORMAL_SPEED, -44);
	msleep(100);
	moveToDist(NORMAL_SPEED, -5);
	pivotOnRight(NORMAL_SPEED, -44);
	msleep(5000);
	moveToDist(NORMAL_SPEED,-5);
	//turn to face black tape
	rotate(-83.0);
	//move to black tape
	moveToDistWithKickerAndPomAligner(NORMAL_SPEED - 20, 39, kickChannel);
	//turn to center of board + hangers
	rotate(-81.5);
	//move to center of board
	moveToDistWithKickerAndPomAligner(NORMAL_SPEED - 20, 69, kickChannel);
	//turn to rack
	rotate(87.8);
	//arm raises
	raiseArm();
	msleep(500);
	//hanger platform rotates forward
	setHangerClawPosition(HANGER_UP);
	//touch sensor activate 
	moveToTouch(NORMAL_SPEED);
	msleep(500);
	//hangers are put on rack
	setHangerClawPosition(HANGER_FORWARD);
	msleep(500);
	//back up to make room to get out of
	//the way of the pink hangers
	moveToDist(NORMAL_SPEED, -3);
	msleep(500);
	//lower the arm out of way of hangers
	moveArm(-80);
	moveArm(60);
	msleep(500);
	off(SPINNER_MOTOR);
	msleep(100);
	//pivot out from under pink hangers
	pivotOnLeft(NORMAL_SPEED, -98);
	//lower the arm
	lowerArmBySensor();
	pivotOnRight(NORMAL_SPEED,30);
	moveToDist(NORMAL_SPEED, 35);
	pivotOnLeft(NORMAL_SPEED, 35);

/*
//move back to the pipe
	moveUntilMaxDist(-1 * NORMAL_SPEED);
	//move back an extra 5 cm
	moveToDist(NORMAL_SPEED, -5);
	//hanger claw forward to grab hanger
	setHangerClawPosition(HANGER_FORWARD);
	//pivot until claw is next to hanger
	pivotOnLeft(NORMAL_SPEED, 40);
	msleep(500);
	//pivot until claw is under hanger
	pivotOnLeft(SLOW_SPEED, 18);
	msleep(500);
	moveToDist(SLOW_SPEED, 1);
	msleep(500);
	moveArm(400);
	setServoSlow(HANGER_UP, 100);
	//pick up the right multiplier hanger
	setHangerClawPosition(HANGER_UP);
	msleep(500);
	moveToDist(NORMAL_SPEED, -13);
	//lowerArmBySensor();
	pivotOnRight(NORMAL_SPEED, -83);
	pivotOnLeft(NORMAL_SPEED, -61);
	raiseArm();
	moveToDist(NORMAL_SPEED, 30);
	setHangerClawPosition(HANGER_UP);
	msleep(250);
	moveToTouch(NORMAL_SPEED);
	msleep(500);
	setHangerClawPosition(HANGER_FORWARD);
	msleep(500);
	moveToDist(NORMAL_SPEED - 10, -3);
	msleep(500);
	moveArm(-20);
	msleep(500);
	pivotOnLeft(NORMAL_SPEED, -40);
	moveToDist(NORMAL_SPEED, -10);
	rotate(48.0);
	lowerArmBySensor();
	moveToTouch(NORMAL_SPEED);
	setHangerClawPosition(HANGER_UP);
*/

	//angle park
	moveToWallAlign(NORMAL_SPEED);
	moveToDist(NORMAL_SPEED, -2);
	pivotOnRight(NORMAL_SPEED, -45);
	pivotOnLeft(NORMAL_SPEED, 45);
	moveToDist(NORMAL_SPEED, 15);
	pivotOnRight(NORMAL_SPEED, -20);
	moveToDist(NORMAL_SPEED, -14);
	//pivotOnLeft(NORMAL_SPEED, -22);
	
	//dump poms in lower area
	dumpBasket();
	
	moveToDist(NORMAL_SPEED, 30);
	
	ao();
	disable_servos();

	return 1;
	
}

int doubleElim(int kickChannel) {
	
	
	wait_for_light(LIGHT_SENSOR);
	shut_down_in(119.5);


	//wall align
	moveToWallAlign(NORMAL_SPEED);
	msleep(1000);
	
	//create and beging a pom collector thread
	thread spinnerThread = thread_create(spinnerStart);
	thread_start(spinnerThread);

	//move to beginning of route
	pivotOnLeft(NORMAL_SPEED, -44);
	msleep(100);
	moveToDist(NORMAL_SPEED, -5);
	pivotOnRight(NORMAL_SPEED, -45);
	msleep(3000);
	moveToDist(NORMAL_SPEED,-5);
	//turn to face black tape
	rotate(-83.0);
	//move to black tape
	moveToDistWithKickerAndPomAligner(NORMAL_SPEED, 39, kickChannel);
	//turn to center of board + hangers
	rotate(-83.0);
	//move to center of board
	moveToDistWithKickerAndPomAligner(NORMAL_SPEED, 69, kickChannel);
	//turn to rack
	
	thread t1 = thread_create(raiseArm);
	thread_start(t1);
	rotate(86.0);
	//arm raises
	msleep(500);
	//hanger platform rotates forward
	setHangerClawPosition(HANGER_UP);
	//touch sensor activate 
	moveToTouch(NORMAL_SPEED);
	msleep(500);
	//hangers are put on rack
	setHangerClawPosition(HANGER_FORWARD);
	msleep(500);
	//back up to make room to get out of
	//the way of the pink hangers
	moveToDist(NORMAL_SPEED, -3);
	msleep(500);
	//lower the arm out of way of hangers
	moveArm(-80);


	ao();
	disable_servos();
	/*
	
	moveArm(40);
	msleep(500);
	off(SPINNER_MOTOR);
	msleep(100);
	//pivot out from under pink hangers
	pivotOnLeft(NORMAL_SPEED, -98);
	//lower the arm
	lowerArmBySensor();
	//move past the pipe
	moveToDist(NORMAL_SPEED, 35);
	//move back to the pipe
	moveUntilMaxDist(-1 * NORMAL_SPEED);
	//move back an extra 5 cm
	moveToDist(NORMAL_SPEED, -5);
	//hanger claw forward to grab hanger
	setHangerClawPosition(HANGER_FORWARD);
	//pivot until claw is next to hanger
	pivotOnLeft(NORMAL_SPEED, 40);
	msleep(500);
	//pivot until claw is under hanger
	pivotOnLeft(SLOW_SPEED, 18);
	msleep(500);
	moveToDist(SLOW_SPEED, 1);
	msleep(500);
	moveArm(400);
	setServoSlow(HANGER_UP, 100);
	//pick up the right multiplier hanger
	setHangerClawPosition(HANGER_UP);
	msleep(500);
	moveToDist(NORMAL_SPEED, -13);
	//lowerArmBySensor();
	pivotOnRight(NORMAL_SPEED, -83);
	pivotOnLeft(NORMAL_SPEED, -61);
	raiseArm();
	moveToDist(NORMAL_SPEED, 30);
	setHangerClawPosition(HANGER_UP);
	msleep(250);
	moveToTouch(NORMAL_SPEED);
	msleep(500);
	setHangerClawPosition(HANGER_FORWARD);
	msleep(500);
	moveToDist(NORMAL_SPEED - 10, -3);
	msleep(500);
	moveArm(-20);
	msleep(500);
	pivotOnLeft(NORMAL_SPEED, -40);
	moveToDist(NORMAL_SPEED, -10);
	rotate(48.0);
	lowerArmBySensor();
	moveToTouch(NORMAL_SPEED);
	setHangerClawPosition(HANGER_UP);
	
	//angle park
	moveToDist(NORMAL_SPEED, -2);
	pivotOnRight(NORMAL_SPEED, -45);
	pivotOnLeft(NORMAL_SPEED, 45);
	pivotOnRight(NORMAL_SPEED, -20);
	moveToDist(NORMAL_SPEED, -14);
	//pivotOnLeft(NORMAL_SPEED, -22);
	
	//dump poms in lower area
	dumpBasket();

*/
	return 1;
	
}


void mainMenu() {
	
	console_clear();
	set_a_button_text("moveStraight");
	set_b_button_text("seeding");
	set_c_button_text("doubleElim");
	
	while(1) {
		if (a_button()) {
			//thread spinnerThread = thread_create(spinnerStart);
			//thread_start(spinnerThread);
			moveToDistWithKickerAndPomAligner(NORMAL_SPEED, 100, 0);
			
			msleep(5000);
			
			moveToDistWithKickerAndPomAligner(NORMAL_SPEED, 100, 0);
			
			
			
			/*
			enable_servo(HANGER_SERVO);
			set_servo_position(HANGER_SERVO,HANGER_FORWARD);
			msleep(1500);
			moveToDist(NORMAL_SPEED,-25);
			msleep(100);
			pivotOnRight(NORMAL_SPEED,5);
			msleep(1000);
			raiseArm();
			msleep(500);
			moveArm(-90);
			moveToDist(NORMAL_SPEED,26);
			msleep(100);
			raiseArm();
			msleep(200);
			moveArm(-100);
			msleep(100);
			set_servo_position(HANGER_SERVO,HANGER_BACK);
			msleep(1000);
			*/
			
			
			
			//arcToWallAlign(NORMAL_SPEED, 1,1);
			
			//pivotOnLeft(NORMAL_SPEED, 45);
			//pivotOnRight(NORMAL_SPEED, 45);
			//pivotOnLeft(NORMAL_SPEED, -45);
			//pivotOnRight(NORMAL_SPEED, -45);
		}
		
		else if (b_button()) {
			set_a_button_text("");
			set_b_button_text("green side");
			set_c_button_text("pink side");
			msleep(200);
			while (!side_button()) {
				if (b_button()) {
					msleep(200);
					//run seeding looking to kick pink
					seeding(1);
				}
				else if (c_button()) {
					msleep(200);
					//run seeding looking to kick green
					seeding(0);
				}
				msleep(50);
			}
			
		}
		
		else if (c_button()) {
			set_a_button_text("green side");
			set_b_button_text("pink side");
			set_c_button_text("");
			msleep(200);
			while (!side_button()) {
				if (a_button()) {
					msleep(200);
					//run DE looking to kick pink
					doubleElim(1);
				}
				else if (b_button()) {
					msleep(200);
					//run seeding looking to kick green
					doubleElim(0);
				}
				msleep(50);
			}
		}
		
		msleep(100);
		
	}
	
}
