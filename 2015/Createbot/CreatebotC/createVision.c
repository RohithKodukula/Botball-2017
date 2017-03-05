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

int sweepForOrange() {
	
	int angle;
	
	printf("\nSweeping for orange...\n");
	
	if (!cameraSeesBigOrange()) {
		printf("\nTurning right because I didn't see anything...\n");
		turnWithSerial(50, 20);
		angle = 10;
		msleep(1000);
		if (!cameraSeesBigOrange()) {
			printf("\nTurning left because I didn't see anything...\n");
			turnWithSerial(50, -40);
			angle = -10;
			msleep(1000);
			if (!cameraSeesBigOrange()) {
				printf("\nSomething pooped itself.\n");
				ao();
				create_disconnect();
				return angle;
			}
		}	
	}

		
	printf("i see it");
	//angle = 0;
	
	msleep(1000);
	return angle;
}

int sweepForYellow() {
	
	int angle;
	
	printf("\nSweeping for orange...\n");
	
	if (!cameraSeesBigOrange()) {
		printf("\nTurning right because I didn't see anything...\n");
		rotate(TURN_SLOW_SPEED + 30, 15);
		angle = 10;
		msleep(1000);
		if (!cameraSeesBigOrange()) {
			printf("\nTurning left because I didn't see anything...\n");
			rotate(TURN_SLOW_SPEED + 30, -30);
			angle = -10;
			msleep(1000);
			if (!cameraSeesBigOrange()) {
				printf("\nSomething pooped itself.\n");
				ao();
				create_disconnect();
				return angle;
			}
		}	
	}

		
	printf("i see it");
	//angle = 0;
	
	msleep(1000);
	return angle;
}

int cameraSeesBigOrange() {
	
	printf("\nseesbigorange started...\n");
	
	int x, y, z;
	double averageArea;
	int isLargeEnough;
	
	camera_update();
	msleep(200);
	camera_update();
	msleep(200);
	camera_update();
	msleep(200);
	camera_update();
	msleep(200);
	camera_update();
	msleep(200);
	camera_update();
	msleep(200);
	x = get_object_area(0, 0);
	msleep(200);
	camera_update();
	msleep(200);
	camera_update();
	msleep(200);
	y = get_object_area(0, 0);
	msleep(200);
	camera_update();
	msleep(200);
	camera_update();
	msleep(200);
	z = get_object_area(0, 0);
	msleep(200);
	
	averageArea = ((x + y + z) / 3);
	printf("\nx: %d\ny: %d\nz: %d\n", x, y, z);
	
	if (averageArea > 800.00) {
		isLargeEnough = 1;
	} else {
		isLargeEnough = 0;
	}
	
	return isLargeEnough;
	
}

point2 cameraSeesBigOranges() {
	
	printf("\nseesbigoranges started...\n");
	
	int x, y, z;
	double averageArea;
	int isLargeEnough;
	int i = 0;
	int bestObjectIndex = 0;
	
	point2 bestObjectLocation;
	bestObjectLocation.x = -1;
	bestObjectLocation.y = -1;
	
	while (i < 2 && isLargeEnough) { //begin while loop
		
	camera_update();
	msleep(200);
	camera_update();
	msleep(200);
	camera_update();
	msleep(200);
	camera_update();
	msleep(200);
	camera_update();
	msleep(200);
	camera_update();
	msleep(200);
	x = get_object_area(0, i);
	msleep(200);
	camera_update();
	msleep(200);
	camera_update();
	msleep(200);
	y = get_object_area(0, i);
	msleep(200);
	camera_update();
	msleep(200);
	camera_update();
	msleep(200);
	z = get_object_area(0, i);
	msleep(200);
	
	averageArea = ((x + y + z) / 3);
	printf("\nx: %d\ny: %d\nz: %d\n", x, y, z);
	
	if (averageArea > 800.00) {
		isLargeEnough = 1;
		
		printf("\nY-coord of current object: %d", get_object_centroid(0, i).y);
		printf("\nY-coord of best object: %d", get_object_centroid(0, bestObjectIndex).y);
		
		
		if (get_object_centroid(0, bestObjectIndex).y > get_object_centroid(0, i).y) {
			bestObjectIndex = i;
			printf("\nfound the best object index...\n");
		}
		
	} else {
		isLargeEnough = 0;
		if(i==0)
		{
			
			printf("failed and exiting function...");
			
			return bestObjectLocation;
		}
	}
	
	i++;
		
	}		//end while loop
	
	printf("\nIndex: %d", bestObjectIndex);
	printf("\nLocation: (%d, %d)", get_object_centroid(0, bestObjectIndex).x, get_object_centroid(0, bestObjectIndex).y);
	
	point2 returnedPoint = get_object_centroid(0, bestObjectIndex);
	
	return returnedPoint;
	
}

int cameraSeesBigYellow() {
	
	printf("\nseesbigyellow started...\n");
	
	int x, y, z;
	double averageArea;
	int isLargeEnough;
	
	camera_update();
	msleep(200);
	camera_update();
	msleep(200);
	camera_update();
	msleep(200);
	camera_update();
	msleep(200);
	camera_update();
	msleep(200);
	camera_update();
	msleep(200);
	x = get_object_area(0, 0);
	msleep(200);
	camera_update();
	msleep(200);
	camera_update();
	msleep(200);
	y = get_object_area(0, 0);
	msleep(200);
	camera_update();
	msleep(200);
	camera_update();
	msleep(200);
	z = get_object_area(0, 0);
	msleep(200);
	
	averageArea = ((x + y + z) / 3);
	printf("\nx: %d\ny: %d\nz: %d\n", x, y, z);
	
	if (averageArea > 600.00) {
		isLargeEnough = 1;
	} else {
		isLargeEnough = 0;
	}
	
	return isLargeEnough;
	
}

void centerCamera(int channel, int object) {
	
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
	while ( (get_object_centroid(channel, object).x > camCenter.x+mOE || 
		     get_object_centroid(channel, object).x < camCenter.x-mOE) && get_object_area(channel,object) > 1000)
	{
		printf("camCenter = (%d,%d)\nobject centroid = (%d,%d)\n\n",camCenter.x,camCenter.y,get_object_centroid(channel, object).x,get_object_centroid(channel, object).y);
		camera_update();
		camera_update();
		if(get_object_centroid(channel, object).x > camCenter.x) {
			turnWithSerial(2, TURN_SLOW_SPEED);
		}
		else if(get_object_centroid(channel, object).x < camCenter.x) {
			turnWithSerial(-2, TURN_SLOW_SPEED);
		}
		msleep(200);
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



void moveToBestBlob(point2 objectPosition) {
	
	printf("\nstarting movetobestblob...\n");
	
	thread moveArm;
	
	if (objectPosition.y < 100) {
		moveArm = thread_create(raiseArmToTopFromBetween);
	} else {
		moveArm = thread_create(lowerArmToMiddleFromBetween);
	}
	
	printf("\nangle to move to the block: %d\n", getAngle(objectPosition.x));
	
	printf("\nstarting movement threads...\n");
	
	int angleToBlock = getAngle(objectPosition.x);
	setDeltaAngle(angleToBlock);
	
	turnWithSerial(200, angleToBlock);
	thread_start(moveArm);
	
	msleep(4000);
	
	printf("\ndestroying movement threads...\n");
	
	thread_destroy(moveArm);
	
}


//camera width is 320 with MED_RES
int centerCameraFast(int channel) {
	int x;
	int accumulatedAngle = 0;
	int angle = 999;
	int blob = 0; //largest blob
	int counter = 0;
	
	while ( (angle < -1 || angle > 1) && counter < 5){
		printf("\ntest 1, %d\n", counter);
		angle = getAngleToBlob(channel, blob);
		if (counter == 0) {
			accumulatedAngle = angle;
		}
		else {
			accumulatedAngle += angle;
		}
		printf("\nangle: %d\n", angle);
		if (angle == 0) {
			break;
		}
		printf("\ncalculated angle: %d\n",angle);
		
		turnWithSerial(40, angle);
		msleep(500);
		counter++;
	}
	printf("\nAngle from original: %d\n", accumulatedAngle);
	return accumulatedAngle;
}


//returns angle from original position that has the largest block
//sweepAngle is angle to the left and then to the right (total sweep angle is 2*)
/*
=======
//sweepAngle is angle to see the  left and then to the right (total sweep angle is 2*)
>>>>>>> FETCH_HEAD
int sweepToFindLargestBlock(int channel, int sweepAngle) {
	
	//SOMETIMES THIS DOENS'T CHECK EACH POSITION, why?
	const int LEFT_VIEW = (-sweepAngle) + (int)CAMERA_VIEW_ANGLE/2; //left view is end where furthest point left is displayed in view in far left corner 
	const int RIGHT_VIEW = (sweepAngle) - (int)CAMERA_VIEW_ANGLE/2; //right view is end where furthest point right is displayed in view in far right corner 
	int currentAngle = 0;
	int largestBlobArea;
	int bestAngle = 0;
	if ((double)sweepAngle > CAMERA_VIEW_ANGLE/2) 
	{
		currentAngle = (-sweepAngle) + (int)CAMERA_VIEW_ANGLE/2; //set current angle to be the leftmost camera frame
		//turn to current angle
		turnWithSerial(MOVE_SLOW_SPEED, currentAngle);
		
		//find largest blob and save as largestBlobArea
		largestBlobArea = getLargestBlobArea(channel);
		
		//bestAngle should be set to the where the blob is
		bestAngle = currentAngle + getAngleToBlob(channel, 0);
		printf("\n Blob area %d at angle %d", largestBlobArea, bestAngle);
		msleep(5000);
		
		//while current angle is less than opposite end of view (
		while (currentAngle < RIGHT_VIEW) 
		{
			printf("\n rotating forward one...\n");
			turnWithSerial(MOVE_SLOW_SPEED, (int)CAMERA_VIEW_ANGLE/2);
			
			//currentAngle updated
			currentAngle += (int)CAMERA_VIEW_ANGLE/2;
			
			
			newLargestBlobArea = getLargestBlobArea(channel);
			if (newLargestBlobArea > largestBlobArea) 
			{
				bestAngle = currentAngle + getAngleToBlob(channel, 0);
				largestBlobArea = newLargestBlobArea;
				printf("\nNew best blob area %d at angle %d\n", largestBlobArea, bestAngle);

			}
		msleep(5000);
		}
	}
	else 
	{
		return getAngleToBlob(channel, 0);
	}
	printf("\ncurrent angle: %d, best angle: %d", currentAngle, bestAngle);
	printf("\n turning %d", bestAngle- currentAngle);
	turnWithSerial(MOVE_SLOW_SPEED, bestAngle-currentAngle); //align with that block approximately
	return bestAngle;
}

*/
/*

//returns angle from original position that has the largest block
//sweepAngle is angle to the left and then to the right (total sweep angle is 2*)
int sweepToFindLargestBlock(int channel, int sweepAngle) {
	
	//SOMETIMES THIS DOENS'T CHECK EACH POSITION, why?
	int currentAngle = 0;
	int largestBlobArea;
	int bestAngle = 0;
	if ((double)sweepAngle > CAMERA_VIEW_ANGLE/2) {
		turnWithSerial(MOVE_SLOW_SPEED, (-sweepAngle) + (int)CAMERA_VIEW_ANGLE/2);
		currentAngle = (-sweepAngle) + (int)CAMERA_VIEW_ANGLE/2; //turn until seeing the leftmost camera frame
		largestBlobArea = getLargestBlobArea(channel);
		bestAngle = currentAngle + getAngleToBlob(channel, 0);
		printf("\n Blob area %d at angle %d", largestBlobArea, bestAngle);
		msleep(5000);
		while (currentAngle < (sweepAngle-(int)CAMERA_VIEW_ANGLE)) {
			printf("\n rotating forward one...\n");
			turnWithSerial(MOVE_SLOW_SPEED, (int)CAMERA_VIEW_ANGLE/2);
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
*/


/*

//returns angle from original position that has the largest block
//sweepAngle is angle to the left and then to the right (total sweep angle is 2*)
int sweepToFindLargestBlock(int channel, int sweepAngle) {
	
	//SOMETIMES THIS DOENS'T CHECK EACH POSITION, why?
	int currentAngle = 0;
	int largestBlobArea;
	int bestAngle = 0;
	if ((double)sweepAngle > CAMERA_VIEW_ANGLE/2) {
		turnWithSerial(MOVE_SLOW_SPEED, (-sweepAngle) + (int)CAMERA_VIEW_ANGLE/2);
		currentAngle = (-sweepAngle) + (int)CAMERA_VIEW_ANGLE/2; //turn until seeing the leftmost camera frame
		largestBlobArea = getLargestBlobArea(channel);
		bestAngle = currentAngle + getAngleToBlob(channel, 0);
		printf("\n Blob area %d at angle %d", largestBlobArea, bestAngle);
		msleep(5000);
		while (currentAngle < (sweepAngle-(int)CAMERA_VIEW_ANGLE)) {
			printf("\n rotating forward one...\n");
			turnWithSerial(MOVE_SLOW_SPEED, (int)CAMERA_VIEW_ANGLE/2);
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
*/

int getAngleToBlob(channel, blob) {
	int xCoords[3];
	camera_update(); //2 are required to clear for some reason...
	camera_update();
	msleep(200);
	xCoords[0] = getBlobXCoord(channel, blob);
	xCoords[1] = getBlobXCoord(channel, blob);
	xCoords[2] = getBlobXCoord(channel, blob);
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
