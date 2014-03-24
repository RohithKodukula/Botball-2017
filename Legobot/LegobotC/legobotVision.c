#include "legobotConstants.h"
#include "legobotFunctions.h"

void cameraInitialize() {
	camera_open_at_res(LOW_RES);
	camera_load_config("tribble.conf");

}

void moveToDistWithKickerAndDipstick(int power, int dist, int channelToKick) {
	printf("going to move %d\n", dist);
	int ticks = dist*TICKS_PER_CM;
	printf("ticks: %d\n", ticks);
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	
	power = dist > 0 ? power : -power;
	
	int kickDelay = 425;
	
	printf("delay ms: %d, power level: %f\n", kickDelay, power_level());
	
	thread dipstickThread;
	dipstickThread = thread_create(dipstickDoesShit);
	thread_start(dipstickThread);
	
	moveStraight(power);
	
	//all the distance calibrations are based on the left motor
	if (dist < 0) {
		while (get_motor_position_counter(LEFT_MOTOR) > ticks) {
			camera_update();
			camera_update();

			printf("moving backwards!");
			if (channelToKick == getRightMostBlock(get_channel_count())) {
				printf("see green blob\n");
				msleep(kickDelay);
				kick();
			}
		}
	}
	else {
		int pinkCount = 0;
		while (get_motor_position_counter(LEFT_MOTOR) < ticks) {
			camera_update();
			camera_update();
			printf("moving!");
			if (channelToKick == getRightMostBlock(get_channel_count()) && pinkCount == 0) {
				printf("See pink blob\n");
				msleep(kickDelay);
				printf("kicking\n");
				kick();
				pinkCount++;
			}
			msleep(10);
		}
	}
	thread_destroy(dipstickThread);
	halt();
	
}

void moveToDistWithKicker(int power, int dist, int channelToKick) {
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
			camera_update();

			printf("moving backwards!");
			if (channelToKick == getRightMostBlock(get_channel_count())) {
				kick();
			}
		}
	}
	else {
		printf("dist more than 0\n");
		printf("motor: %d, target ticks: %d", get_motor_position_counter(LEFT_MOTOR), ticks);
		int pinkCount = 0;
		while (get_motor_position_counter(LEFT_MOTOR) < ticks) {
			camera_update();
			camera_update();
			printf("moving!");
			if (channelToKick == getRightMostBlock(get_channel_count()) && pinkCount == 0) {
				printf("See pink blob\n");
				msleep(350);
				printf("kicking\n");
				kick();
				pinkCount++;
			}
			msleep(10);
		}
	}
	
	halt();
	
}

int getRightMostBlock(int numChannels) {
	int rightMostChannel = -1; //none...
	int xCoord = -999;
	int i, coord;
	for (i = 0; i < numChannels; i++) {
		coord = get_object_centroid(i,0).x;
		if (xCoord < coord && get_object_area(i,0) > 4500) {
			xCoord = coord;
			rightMostChannel = i;
		}
	}
	return rightMostChannel;
}

