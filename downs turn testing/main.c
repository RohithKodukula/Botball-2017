// Created on Fri March 28 2014

int main()
{
	
	printf("\nRunning...\n");
	
	int x = 1;
	
	while(1) {
		turnWithSerial(150, 45);
		msleep(200);
		printf("#: %d\n\n", x);
		x++;
	}
	
	return 0;
	
}

void turnTest() {
	
	create_connect();
	int x = 1;
	
	while(1) {
		turnWithSerial(150, 45);
		msleep(200);
		printf("#: %d\n\n", x);
		x++;
	}
	
}

void turnWithSerial(int speed, int degrees) {
	
	if (speed < 1) {
		speed *= -1;
	}
	
	int compensation = 0;
	
	if (degrees < 0) {
		
	if (degrees >= -15) {
		compensation = 0;
	} else if (degrees >= -45) {
		compensation = 4;
	} else if (degrees >= -90) {
		compensation = 2;
	} else if (degrees >= -180) {
		compensation = 8;
	} else {
		compensation = 0;
	}
	
	} else {
		
	if (degrees <= 15) {
		compensation = 0;
	} else if (degrees <= 45) {
		compensation = 4;
	} else if (degrees <= 90) {
		compensation = 2;
	} else if (degrees <= 180) {
		compensation = 8;
	} else {
		compensation = 0;
	}
	
	}
	
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
		
		angle2 -= compensation;
		angle2 = 255 - angle2; 
		
	}
	
	if (degrees = 0) {
		angle1 = 0;
		angle2 = 0;
		speed1 = 0;
		speed2 = 0;
	}
	
	if (speed = 0) {
		angle1 = 0;
		angle2 = 0;
		speed1 = 0;
		speed2 = 0;
	}
	
	msleep(300);
	create_connect();
	msleep(300);
	
			create_write_byte(128); //initializes mode to full
			create_write_byte(132);

			create_write_byte(152); //script size
			create_write_byte(13);
	
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
			create_write_byte(153);
			
	msleep(300);
	create_disconnect();
	msleep(300);
	
}

void moveWithSerial(int speed, int distance) {
	
	
	
	if (speed < 1) {
		speed *= -1;
	}
	
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
	create_connect();
	msleep(200);
	
			create_write_byte(128); //initializes mode to full
			create_write_byte(132);

			create_write_byte(152); // script size
			create_write_byte(13);
	
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
			
	msleep(200);
	create_disconnect();
	
	msleep(200);
	create_connect();
	msleep(200);
	create_write_byte(153);
	msleep(200);
	create_disconnect();
	msleep(200);
	
}

void checkData() {
	
	create_connect();
	
	create_write_byte(149);
	create_write_byte(3);
	create_write_byte(39);
	create_write_byte(41);
	create_write_byte(42);
	
}

void testCheckData() {
	/*
	printf("\nFirst run:");	
	
		thread t1 = thread_create(moveWithSerial(30, 20));
		thread_start(t1);
		msleep(2000);
		checkData();
		msleep(5000);
		thread_destroy(t1);
		msleep(5000);
	
	printf("\nSecond run:");
		
		thread t2 = thread_create(moveWithSerial(30, -20));
		thread_start(t2);
		msleep(2000);
		checkData();
		msleep(5000);
		thread_destroy(t2);
		*/
	
	
}

void mainMenu() {
	
	create_connect();
	
	turnTest();
	
}


