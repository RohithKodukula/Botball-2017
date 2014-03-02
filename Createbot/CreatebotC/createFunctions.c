#include "createConstants.h"

void createInit() {
	int connect = create_connect();
	enable_servos();
	if(connect == 0) {
		printf("Connection success.\n");
	}
	else {
		printf("Connection failed.\n");
	}
	create_full();
	msleep(500);
}

void initActuators() {
	set_servo_position(UPPER_CLAW, UPPER_CLAW_OPEN);
	set_servo_position(LOWER_CLAW, LOWER_CLAW_OPEN);
	enable_servos();
}

//----- ARM ------
void raiseArm(int position) {
	clear_motor_position_counter(ARM_PORT);
	while(get_motor_position_counter(ARM_PORT) < position) {
		printf("Motor position = %d\n", get_motor_position_counter(ARM_PORT));
		motor(ARM_PORT, 70);
		msleep(100);
	}
	off(ARM_PORT);
}

void lowerArm(int position) {
	clear_motor_position_counter(ARM_PORT);
	while(get_motor_position_counter(ARM_PORT) > position) {
		printf("Motor position = %d\n", get_motor_position_counter(ARM_PORT));
		motor(ARM_PORT, -70);
		msleep(100);
	}
	off(ARM_PORT);
}

void lowerArmBySensor() {
	motor(ARM_PORT, -30);
	while (analog10(ARM_DOWN_SENSOR_PORT) > 100) {
		msleep(100);
	}
	msleep(300);
	off(ARM_PORT);
}

//------ CREATE MOVEMENT-----
void moveStraight(int vel) {
	create_drive_straight(-vel);
}
void createStop() {
	moveStraight(0);
}
void moveToDist(int dist, int speed) { 
	set_create_distance(0); 
	
	//speed distance compensation
	if(speed >= 400){dist = dist - (22 * (dist * 0.01));} //fast speed
	else if(speed > 300 && speed < 400){dist = dist - (8 * (dist * 0.01));} //mid speed
	else if(speed <= 300){dist = dist - (6 * (dist * 0.01));} //slow speed

	if (dist > 0) {   
		moveStraight(speed); 
		while (-get_create_distance() < dist) { msleep(10); }
	}
	
	else if (dist < 0) { 
		moveStraight(-speed); 
		while (-get_create_distance() > dist) { msleep(10); }
	}
	
	createStop();
	
	printf("Distance Moved: %dmm\n", -get_create_distance(0)); 
}
//speed of -500 to 500mm/sec
//0 to 359 degrees
void rotate(int degrees, int speed) {
	set_create_normalized_angle(0);
	
	//speed degree compensation
	if(speed >= 200){degrees = degrees - (2.6 * (degrees * 0.1));} //fast speed
	//else if(speed > 40 && speed < 200){degrees = degrees;} //mid speed
	else if(speed <= 40 && speed > 8){degrees = degrees - (1.1 * (degrees * 0.1));} //slow speed
	
	//printf("rotating %d degrees at speed %d\n", degrees, speed);
	
	if(degrees > 0) {
		while(get_create_normalized_angle() > -degrees || get_create_normalized_angle() == 0) {
			create_spin_CW(speed);
			msleep(3);
			//printf("angle = %d\n", get_create_normalized_angle());
		}
	} else if (degrees < 0) {
		while(get_create_normalized_angle() < -degrees || get_create_normalized_angle() == 0) {
			create_spin_CCW(speed);
			msleep(3);
			//printf("angle = %d\n", get_create_normalized_angle());
		}
	}
	create_stop();
}

//camera
/*void openGraphicsInterface() {
	 if(graphics_open(320, 190)) {
		 while(side_button() == 0) {
			 graphics_update();
		 }
	 }
	 graphics_close();
}*/
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
	camCenter.x = 79 + 20;
	camCenter.y = 59;
	
	int counter = 0;
	while ( (get_object_centroid(channel, object).x > camCenter.x || get_object_centroid(channel, object).x < camCenter.x) && get_object_area(channel,object) > 1000)
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

