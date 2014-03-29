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
	//mainMenu();
	printf("Running routine...\n\n");
	routine();
	
}

int routine() {
	
	//create and beging a pom collector thread
	thread spinnerThread = thread_create(spinnerStart);
	thread_start(spinnerThread);
	
	//wall align
	moveToWallAlign(NORMAL_SPEED);
	
	//move to beginning of route
	pivotOnLeft(NORMAL_SPEED, -44);
	msleep(100);
	moveToDist(NORMAL_SPEED, -5);
	pivotOnRight(NORMAL_SPEED, -44);
	msleep(100);
	moveToDist(NORMAL_SPEED,-5);
	//turn to face black tape
	rotate(-84.0);
	//move to black tape
	moveToDistWithKickerAndPomAligner(NORMAL_SPEED - 10, 36, 1);
	//turn to center of board + hangers
	rotate(-83.0);
	//move to center of board
	moveToDistWithKickerAndPomAligner(NORMAL_SPEED - 10, 72, 1);
	//turn to rack
	rotate(89.0);
	msleep(500);
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
	moveToDist(NORMAL_SPEED, -2);
	msleep(500);
	//lower the arm out of way of hangers
	moveArm(-20);
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
	moveToDist(SLOW_SPEED, 2);
	msleep(500);
	moveArm(400);
	setServoSlow(HANGER_UP, 100);
	setHangerClawPosition(HANGER_UP);
	msleep(500);
	moveToDist(NORMAL_SPEED, -13);
	lowerArmBySensor();
	pivotOnRight(NORMAL_SPEED, -80);
	pivotOnLeft(NORMAL_SPEED, -58);
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
	moveToDist(NORMAL_SPEED, -12);
	//pivotOnLeft(NORMAL_SPEED, -22);
	
	//dump poms in lower area
	dumpBasket();

	return 1;
	
}

void mainMenu() {
	
	console_clear();
	printf("-Side button to end\n-A button to test dist\n-B button to test turn\n-C button to run routine");
	set_a_button_text("Test Distance");
	set_b_button_text("Test Turn");
	set_c_button_text("Routine");
	
	while(1) {
		
		if (a_button()) {
			
			moveUntilMaxDist(-NORMAL_SPEED);
			
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
			while(1){
				//setServoSlow(HANGER_FORWARD, 50);
				set_servo_position(HANGER_SERVO, HANGER_FORWARD);
				msleep(500);
				setServoSlow(HANGER_BACK, 100);
			}
			
			/*enable_servo(HANGER_SERVO);
			set_servo_position(HANGER_SERVO,HANGER_BACK);
			msleep(2000);
			moveToDist(NORMAL_SPEED,-13);
			raiseArm();
			msleep(2000);
			pivotOnRight(NORMAL_SPEED,5);
			moveToDist(NORMAL_SPEED,15);
			msleep(1000);
			set_servo_position(HANGER_SERVO,HANGER_FORWARD);
			msleep(200);
			pivotOnRight(NORMAL_SPEED,10);
			msleep(200);
			moveToDist(NORMAL_SPEED,-13);*/
			
		}
		
		else if (c_button()) {
			routine();
		}
		
		msleep(100);
		
	}
	
}
