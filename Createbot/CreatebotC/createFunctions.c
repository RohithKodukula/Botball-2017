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


void moveWithSerial(int speed, int distance) {
	
	printf("\nspeed value recieved: %d\ndistance value recieved: %d\n",
	speed, distance
	);
	
	int dist1, dist2, speed1, speed2, counter1 = 0;
	
	if (speed < 0) {
		
		speed1 = 0;
		speed2 = speed * -1;
		
		while (speed2 > 255) {
			speed1++;
			speed2 -= 255;
		}
		
	} else {
		speed1 = 255;
		speed2 = speed;
		while (speed2 > 255) {
			speed1--;
			speed2 -= 255;
		}
		speed2 = 255 - speed2;
	}
	
	distance = distance * 10;
	
	if (distance < 0) {
		
		dist1 = 0;
		dist2 = distance * -1;
		
		while (dist2 > 255) {
			dist1++;
			dist2 -= 255;
		}
		
	} else {
		dist1 = 255;
		dist2 = distance;
		while (dist2 > 255) {
			dist1--;
			dist2 -= 255;
		}
		dist2 = 255 - dist2;
	}
	
	printf("\nspeed1: %d\nspeed2:%d\ndist1: %d\ndist2: %d\n\n",
	speed1, speed2, dist1, dist2
	);
	 
			create_write_byte(128); //initializes mode to full
			create_write_byte(132);

			create_write_byte(152); // script size
			create_write_byte(12);
	
			create_write_byte(137); //drive straight
			create_write_byte(speed1);
			create_write_byte(speed2);
			create_write_byte(128);
			create_write_byte(0);
	
			create_write_byte(156); //wait specified distance
			create_write_byte(dist1);
			create_write_byte(dist2);

			create_write_byte(137); //stop
			create_write_byte(0);
			create_write_byte(0);
			create_write_byte(0);
			create_write_byte(0);
			
	create_disconnect();
	
	create_connect();
	create_write_byte(153);
	create_disconnect();
	create_connect();
	
}


void turnWithSerial(int speed, int degrees) {
	
	printf("\nspeed value recieved: %d\nangle value recieved: %d\n",
	speed, degrees
	);
	
	int compensation = 6;
	
	int angle1, angle2, speed1, speed2, counter1 = 0;
	
	if (degrees < 0) {
		
		speed1 = 0;
		speed2 = speed;
		
		while (speed2 > 255) {
			speed1++;
			speed2 -= 255;
		}
		
	} else {
		speed1 = 255;
		speed2 = speed;
		while (speed2 > 255) {
			speed1--;
			speed2 -= 255;
		}
		speed2 = 255 - speed2;
	}
	
	if (degrees < 0) {
		
		angle1 = 0;
		angle2 = degrees * -1;
		
		while (angle2 > 255) {
			angle1++;
			angle2 -= 255;
		}
		angle2 -= compensation;
		
	} else {
		angle1 = 255;
		angle2 = degrees;
		while (angle2 > 255) {
			angle1--;
			angle2 -= 255;
		}
		angle2 = 255 - angle2;
		angle2 += compensation;
	}
	
	printf("\nspeed1: %d\nspeed2:%d\nangle1: %d\nangle2: %d\n\n",
	speed1, speed2, angle1, angle2
	);
	 
			create_write_byte(128); //initializes mode to full
			create_write_byte(132);

			create_write_byte(152); //script size
			create_write_byte(12);
	
			create_write_byte(137); //spin
			create_write_byte(speed1);
			create_write_byte(speed2);
			create_write_byte(0);
			create_write_byte(0);
	
			create_write_byte(157); //wait angle
			create_write_byte(angle1);
			create_write_byte(angle2);

			create_write_byte(137); //stop
			create_write_byte(0);
			create_write_byte(0);
			create_write_byte(0);
			create_write_byte(0);
			
	create_disconnect();
	
	create_connect();
	create_write_byte(153);
	create_disconnect();
	create_connect();
	
}

