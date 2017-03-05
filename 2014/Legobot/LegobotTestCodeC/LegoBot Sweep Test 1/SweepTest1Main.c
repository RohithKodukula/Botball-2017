// Created on Fri February 28 2014

#include "SweepTest1Constants.h"

int main()
{
	legobotInit();
	cameraInitialize();
	
	camera_update();
	camera_update();
	while (1) {
		camera_update();
		printf("\nRightmost channel: %d", getRightMostBlock(2));
	}
	
	return 0;
}

void cameraInitialize() {
	camera_open_at_res(LOW_RES);
	camera_load_config("tribble.conf");

}


void legobotInit(){
	//setting all servo positions and enabling.
	set_servo_position(DUMPER_SERVO, DUMPER_UP);
	set_servo_position(DIPSTICK_SERVO, DIPSTICK_OPEN);
	set_servo_position(HANGER_SERVO, HANGER_BACK);
	set_servo_position(KICKER_SERVO, KICKER_BACK);
	enable_servos();
	//clear motor positions
	//should use the link to move the motors to initial first
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	clear_motor_position_counter(SPINNER_MOTOR);
	clear_motor_position_counter(ARM_MOTOR);
	//moveArm(500);
	//resetArm();
}


//returns channel
int getRightMostBlock(int numChannels) {
	int xCoord = get_object_centroid(0,0).x;
	int rightMostChannel = 0;
	int i = 1;
	int coord;
	for (i = 1; i < numChannels; i++) {
		coord = get_object_centroid(i,0).x;
		if (xCoord < coord) {
			xCoord = coord;
			rightMostChannel = i;
		}
	}
	return rightMostChannel;
}
