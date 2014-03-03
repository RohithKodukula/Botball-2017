#include "createConstants.h"

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
	/*while(1) {
		camera_update();
		camera_update();
		printf("object count = %d\n", get_object_count(channel));
		msleep(500);
	}*/
	camera_update();
	camera_update();
	/*point2 centroid = get_object_centroid(channel, object);
	printf("centroid = (%d, %d)\n",centroid.x, centroid.y);*/
	
	point2 camCenter;
	camCenter.x = 160;
	camCenter.y = 120;
	
	int counter = 0;
	while ( (get_object_centroid(channel, object).x > camCenter.x+5 || get_object_centroid(channel, object).x < camCenter.x-5) && get_object_area(channel,object) > 1000)
	{
		printf("camCenter = (%d,%d), object centroid = (%d,%d)\n",camCenter.x,camCenter.y,get_object_centroid(channel, object).x,get_object_centroid(channel, object).y);
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
		if ( counter > 60 )
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


void centerCamera2(int channel, int object) {
	camera_update();
	camera_update();
	
	//point2 object = 
	
}

//print x,y coordinates of a blob in a channel
void blobTrack(int channel, int object) {
	camera_update();
	camera_update();
	point2 centroid = get_object_centroid(channel, object);
	printf("Location of object: (%d, %d)", centroid.x, centroid.y);
}

