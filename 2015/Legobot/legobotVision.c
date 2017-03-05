
#include "legobotConstants.h"
#include "legobotFunctions.h"

void initializeCamera() {
	
	camera_open_at_res(LOW_RES);
	camera_load_config("Pom-Config.conf");
	
}

int cameraSeesAnyPom() {
	
	camera_update();
	msleep(100);
	camera_update();
	
	int greenArea = get_object_area(GREEN_CHANNEL, 0);
	int redArea = get_object_area(RED_CHANNEL, 0);
	
	if (greenArea > 2000 || redArea > 2000) {
		return 1;
	} else {
		return 0;
	}
	
}

int cameraSeesGreenPom() {
	
	camera_update();
	msleep(200);
	camera_update();
	
	int greenArea = get_object_area(GREEN_CHANNEL, 0);
	int redArea = get_object_area(RED_CHANNEL, 0);
	
	if (greenArea > MIN_BLOB_AREA && greenArea > redArea) {
		return 1;
	} else {
		return 0;
	}
	
}

int cameraSeesRedPom() {
	
	camera_update();
	msleep(200);
	camera_update();
	
	int greenArea = get_object_area(GREEN_CHANNEL, 0);
	int redArea = get_object_area(RED_CHANNEL, 0);
	
	if (redArea > MIN_BLOB_AREA && redArea > greenArea) {
		return 1;
	} else {
		return 0;
	}
	
}

void printLargestArea(int channel){
	while(1){
		camera_update();
		msleep(200);
		camera_update();
		int largestArea = get_object_area(channel, 0);
		printf("largestArea %d \n", largestArea);
	}
}
