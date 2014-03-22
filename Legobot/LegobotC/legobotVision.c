#include "legobotConstants.h"
#include "legobotFunctions.h"

void cameraInitialize() {
	camera_open_at_res(LOW_RES);
	camera_load_config("tribble.conf");

}


void moveToDistWithKicker(int power, int dist, int channelToLookFor) {
	printf("going to move %d\n", dist);
	int ticks = dist*TICKS_PER_CM;
	printf("ticks: %d\n", ticks);
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	
	power = dist > 0 ? power : -power;
	
	printf("moveToDistWithKicker\n");
	
	moveStraight(power);
	
	//all the distance calibrations are based on the left motor
	if (dist < 0) {
		printf("dist less than 0");
		while (get_motor_position_counter(LEFT_MOTOR) > ticks) {
			camera_update();
			printf("moving backwards!");
			if (channelToLookFor == getRightMostBlock(get_channel_count())) {
				kick();
			}
		}
	}
	else {
		printf("dist more than 0\n");
		printf("motor: %d, target ticks: %d", get_motor_position_counter(LEFT_MOTOR), ticks);
		while (get_motor_position_counter(LEFT_MOTOR) < ticks) {
			camera_update();
			printf("moving!");
			if (channelToLookFor == getRightMostBlock(get_channel_count())) {
				kick();
			}
			msleep(10);
		}
	}
	
	halt();
	
}

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

