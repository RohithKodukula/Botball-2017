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
	
	thread dipstickThread;
	dipstickThread = thread_create(dipstickDoesShit);
	thread_start(dipstickThread);
	
	msleep(4000);
	
	halt();
	turn(-90.0);
	
	motor(RIGHT_MOTOR, 40*1.05);
	motor(LEFT_MOTOR, 40);
	
	msleep(5000);
	
	ao();
	msleep(1000);
	thread_destroy(dipstickThread);
}

int main() {
	legobotInit();
	cameraInitialize();

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
			
			turnTest(-90.0);
			turnTest(-90.0);
			turnTest(-90.0);
			turnTest(-90.0);
			msleep(1000);
			turnTest(90.0);
			turnTest(90.0);
			turnTest(90.0);
			turnTest(90.0);
			
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

void routine() {
	
			thread spinnerThread = thread_create(spinnerStart);
			thread_start(spinnerThread);
			//arcToWallAlign(NORMAL_SPEED+10, 1, 1);
			//arcToTouch(NORMAL_SPEED, 1, 1);
			//pivotOnRightTillLeftTouch(NORMAL_SPEED, 1);
			
			
			//wall align
			moveToWallAlign(NORMAL_SPEED); 
			pivotOnLeft(NORMAL_SPEED, -45);
			msleep(100);
			moveToDist(NORMAL_SPEED, -5);
			pivotOnRight(NORMAL_SPEED, -45);
			msleep(100);
			moveToDist(NORMAL_SPEED,-5);
			turnTest(-90.0);
			
			//move to black tape
			moveToDistWithKickerAndDipstick(NORMAL_SPEED - 10, 36, 1);
			//turn to center of board
			turnTest(-90.0);
			//move to center of board
			moveToDistWithKickerAndDipstick(NORMAL_SPEED - 10, 72, 1);
			//turn to rack
			turnTest(84.0);
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
			moveToDist(NORMAL_SPEED, -3);
			msleep(100);
			moveArm(-90);
			msleep(500);
			off(SPINNER_MOTOR);
			msleep(100);
			pivotOnLeft(NORMAL_SPEED, -90);
			resetArm();
			moveToDist(NORMAL_SPEED, 35);
			//move back to the pipe
			moveUntilMaxDist(-1 * NORMAL_SPEED);
			//move back an extra 3 cm
			moveToDist(NORMAL_SPEED, -3);
			//hanger claw forward to grab hanger
			setHangerClawPosition(HANGER_FORWARD);
			//pivot until claw is next to hanger
			pivotOnLeft(NORMAL_SPEED, 60);
			//move in a little to wedge between hanger and pipe
			moveToDist(NORMAL_SPEED, 1);
			//pivot until claw is under hanger
			pivotOnLeft(NORMAL_SPEED, 26);
			msleep(500);
			pivotOnLeft(NORMAL_SPEED, 10);
			moveToDist(SLOW_SPEED, 5);
			msleep(500);
			moveArm(400);
			//moveToDist(SLOW_SPEED, 3);
			setHangerClawPosition(HANGER_BACK);
			msleep(500);
			moveToDist(NORMAL_SPEED, -13);
			resetArm();
			pivotOnRight(NORMAL_SPEED, -80);
			pivotOnLeft(NORMAL_SPEED, -58);
			raiseArm();
			moveToDist(NORMAL_SPEED, 30);
			setHangerClawPosition(HANGER_UP);
			moveToTouch(NORMAL_SPEED);
			setHangerClawPosition(HANGER_FORWARD);
			
			

}

void turnTest(double degrees) {
	
	clear_motor_position_counter(LEFT_MOTOR);
	
	double ticks = degrees * TICKS_PER_DEGREE;
		
	//everything is calibrated around left wheel
	if (ticks < 0) {
		motor(LEFT_MOTOR, -1 * NORMAL_SPEED);
		motor(RIGHT_MOTOR, NORMAL_SPEED);
		while (get_motor_position_counter(LEFT_MOTOR) > ticks) {
			msleep(20);
		}
	}
	else {
		motor(LEFT_MOTOR, NORMAL_SPEED);
		motor(RIGHT_MOTOR, -1 * NORMAL_SPEED);
		while (get_motor_position_counter(LEFT_MOTOR) < ticks) {
			msleep(20);
		}
	}
	
	halt();
	
}
