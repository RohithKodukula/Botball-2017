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


void centerCameraFast(int channel, int object) {
	camera_update();
	camera_update();
	
	point2 object = 
	
}

//print x,y coordinates of a blob in a channel
void blobTrack(int channel, int object) {
	camera_update();
	camera_update();
	point2 centroid = get_object_centroid(channel, object);
	printf("Location of object: (%d, %d)", centroid.x, centroid.y);
}

