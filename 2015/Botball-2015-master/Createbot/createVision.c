#include "createConstants.h"
#include "createFunctions.h"

//camera


//MED RES: width = 320, height = 240;
void cameraInitialize() {
	camera_open_at_res(MED_RES);
	//camera_load_config("orange.conf");
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
	
}

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
	
	
	return 0;
	
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
