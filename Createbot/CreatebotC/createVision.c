#include "createConstants.h"
#include "createFunctions.h"

//camera
/*void openGraphicsInterface() {
	 if(graphics_open(320, 190)) {
		 while(side_button() == 0) {
			 graphics_update();
		 }
	 }
	 graphics_close();
}*/


//MED RES: width = 320, height = 240;
void cameraInitialize() {
	camera_open_at_res(MED_RES);
	camera_load_config("orange.conf");
}

void centerCamera(int channel, int object) {
	//printf("channel count = %d\n", get_channel_count());
	
	//Objects are sorted by area, largest first
	printf("\ncentering camera on orange\n");
	
	point2 camCenter;
	camCenter.x = 160;
	camCenter.y = 120;
	
	camera_update();
	camera_update();
	
	//margin of error permitted, in pixels
	int mOE = 10;
	
	printf("\norange blob:\ncentroid.x: %d\narea: %d\n", get_object_centroid(channel, object).x, get_object_area(channel,object));
	
	int counter = 0;
	while ( (get_object_centroid(channel, object).x > camCenter.x+mOE || get_object_centroid(channel, object).x < camCenter.x-mOE) && get_object_area(channel,object) > 1000)
	{
		printf("camCenter = (%d,%d)\nobject centroid = (%d,%d)\n\n",camCenter.x,camCenter.y,get_object_centroid(channel, object).x,get_object_centroid(channel, object).y);
		camera_update();
		camera_update();
		if(get_object_centroid(channel, object).x > camCenter.x) {
			rotate(2, TURN_SLOW_SPEED);
		}
		else if(get_object_centroid(channel, object).x < camCenter.x) {
			rotate(-2, TURN_SLOW_SPEED);
		}
		msleep(167);
		camera_update();
		camera_update();
		
		counter++;
		if ( counter > 20 )
		{
			printf("timed out\n");
			break;
		}
	}
	
	//printf("object area1 = %d area2 = %d\n",get_object_area(channel, object), get_object_area(channel, 1));
	
	//printf("bbox area = %f", get_object_area(channel, 0));
	/*rectangle mybox;
	mybox = get_object_bbox(0,2);
	printf("x coord %d y coord %d\n", mybox.x, mybox.y);*/
	
}


//camera width is 320 with MED_RES
int centerCameraFast(int channel) {
	int x;
	int accumulatedAngle = 0;
	int angle = 999;
	int blob = 0; //largest blob
	int counter = 0;
	while ( (angle < -1 || angle > 1) && counter < 5){
		angle = getAngleToBlob(channel, blob);
		if (counter == 0) {
			accumulatedAngle = angle;
		}
		else {
			accumulatedAngle += angle;
		}
		printf("\n angle: %d", angle);
		if (angle == 0) {
			break;
		}
		//printf("\ncalculated angle: %d",angle);
		
		//rotate(50,angle);
		turnWithSerial(50, angle);
		msleep(1300);
		counter++;
	}
	printf("Angle from original: %d", accumulatedAngle);
	return accumulatedAngle;
}




//returns angle from original position that has the largest block
//sweepAngle is angle to the left and then to the right (total sweep angle is 2*)
int sweepToFindLargestBlock(int channel, int sweepAngle) {
	
	//SOMETIMES THIS DOENS'T CHECK EACH POSITION, why?
	int currentAngle = 0;
	int largestBlobArea;
	int bestAngle = 0;
	if ((double)sweepAngle > CAMERA_VIEW_ANGLE/2) {
		rotate(MOVE_SLOW_SPEED, (-sweepAngle) + (int)CAMERA_VIEW_ANGLE/2);
		currentAngle = (-sweepAngle) + (int)CAMERA_VIEW_ANGLE/2; //turn until seeing the leftmost camera frame
		largestBlobArea = getLargestBlobArea(channel);
		bestAngle = currentAngle + getAngleToBlob(channel, 0);
		printf("\n Blob area %d at angle %d", largestBlobArea, bestAngle);
		msleep(5000);
		while (currentAngle < (sweepAngle-(int)CAMERA_VIEW_ANGLE)) {
			printf("\n rotating forward one...\n");
			rotate(MOVE_SLOW_SPEED, (int)CAMERA_VIEW_ANGLE/2);
			currentAngle += (int)CAMERA_VIEW_ANGLE/2;
			if (getLargestBlobArea(channel) > largestBlobArea) {
				bestAngle = currentAngle + getAngleToBlob(channel, 0);
				largestBlobArea = getLargestBlobArea(channel);
				printf("\nNew best blob area %d at angle %d\n", largestBlobArea, bestAngle);

			}
			msleep(5000);
		}
	}
	else {
		return getAngleToBlob(channel, 0);
	}
	printf("\ncurrent angle: %d, best angle: %d", currentAngle, bestAngle);
	printf("\n turning %d", bestAngle- currentAngle);
	turnWithSerial(MOVE_SLOW_SPEED, bestAngle-currentAngle); //align with that block approximately
	return bestAngle;
}

int getAngleToBlob(channel, blob) {
	int xCoords[5];
	camera_update(); //2 are required to clear for some reason...
	camera_update();
	xCoords[0] = getBlobXCoord(channel, blob);
	xCoords[1] = getBlobXCoord(channel, blob);
	xCoords[2] = getBlobXCoord(channel, blob);
	xCoords[3] = getBlobXCoord(channel, blob);
	xCoords[4] = getBlobXCoord(channel, blob);
	int x = getMostLikelyCoord(xCoords, sizeof(xCoords)/sizeof(xCoords[0]),10); //second argument is length of array
	return getAngle(x);
}

int getAngle(int coord) {
	return (int)(((coord-160.0)/160.0) * (double)CAMERA_VIEW_ANGLE/2);
}


int getBlobXCoord(int channel, int object) {
	camera_update();
	camera_update();
	int counter = 0;
	point2 center = get_object_centroid(channel, object);
	
	while (center.x == -1 && counter < 5) { //nothing found in this channel
		printf("\nCan't find anything, getting new image...\n");
		camera_update();
		camera_update();
		center = get_object_centroid(channel, object);
		counter++;
	}
	printf("\n Final x coord: %d", center.x);
	return center.x;
}


int getLargestBlobArea(int channel){
	camera_update();
	camera_update();
	int counter = 0;
	int area = get_object_area(channel, 0);
	
	while ((area == -1 || area > 10000) && counter < 10) { //nothing found in this channel, or way too huge...
		printf("\nsomething wrong getting new image...");
		camera_update();
		camera_update();
		area = get_object_area(channel, 0);
		counter++;
	}
	printf("\n final area: %d", area);
	return area;
}


//really gets most COMMON number within a threshold
//also have to pass in array size manually
int getMostLikelyCoord(int xCoords[], int size, int threshold) {
	int countingArray[size];
	int i, j;
	//count up how many of each (binnned appropriately) there are
	countingArray[0] = 1; //first one is base comparison
	for (i = 1; i < size; i++) {
		countingArray[i] = 0;
		if (i == 0) {
			continue;	
		}
		for (j = 0; j <= i; j++) { //<= since if no others match, then will increment self
			if (xCoords[i] < xCoords[j] + threshold && xCoords[i] > xCoords[j] - threshold && xCoords[i] != 0) {
				countingArray[j] = countingArray[j] + 1;
				break;
			}
		}
	}
	int index = getMaxIndex(countingArray, size);
	int val = xCoords[index];
	return val;
	
}


int getMaxIndex(int array[], int size) {
	int max = 0;
	int i;
	for (i = 0; i < size; i++) {
		if (array[i] > array[max]) {
			max = i;
		}
	}
	return max;
}


//print x,y coordinates of a blob in a channel
void blobTrack(int channel, int object) {
	camera_update();
	camera_update();
	point2 centroid = get_object_centroid(channel, object);
	if (centroid.x == -1) {
		printf("\nobjects: %d", get_object_count(channel));
	}
	printf("\nLoc of object: (%d, %d)", centroid.x, centroid.y);
}

