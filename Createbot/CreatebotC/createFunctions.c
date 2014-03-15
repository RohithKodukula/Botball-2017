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
	raiseArm(700);
	lowerArmBySensor();
	setUpperClaw(UPPER_CLAW_OPEN);
	setLowerClaw(LOWER_CLAW_OPEN);
	enable_servos();
}

void setUpperClaw(int position) {
	set_servo_position(UPPER_CLAW, position);
}

void setLowerClaw(int position) {
	set_servo_position(LOWER_CLAW, position);
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

void raiseArmToTop() {
	clear_motor_position_counter(ARM_PORT);
	while(get_motor_position_counter(ARM_PORT) < ARM_TOP_POS) {
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

int getMillimeterDistance() {
	int i;
	double sum = 0;
	int n = 10;
	for (i = 0; i < n; i++) {
		sum += analog_et(2);
	}
	double y = sum/n;
	double mm = 10*(2213.1614337305136 - 20.725917486966626*y + 0.07920950330177698*y*y - 0.0001526660102098271*y*y*y 
			+ 1.4770513368970602*(pow(10,-7))*y*y*y*y - 5.725546246379343*(pow(10,-11))*y*y*y*y*y);
	printf("cm = %f\n", mm/10);
	return (int)mm;
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

void moveToWallAlign(int dist, int speed, double secondTimeout) {
	//copy body of moveToDist
	//update when new moveToDist is made
	set_create_distance(0); 
	
	double startTime = seconds();
	
	//speed distance compensation
	if(speed >= 400){dist = dist - (22 * (dist * 0.01));} //fast speed
	else if(speed > 300 && speed < 400){dist = dist - (8 * (dist * 0.01));} //mid speed
	else if(speed <= 300){dist = dist - (6 * (dist * 0.01));} //slow speed

	if (dist > 0) {   
		moveStraight(speed); 
		while (-get_create_distance() < dist && seconds() - startTime < secondTimeout) { msleep(10); }
	}
	
	else if (dist < 0) { 
		moveStraight(-speed); 
		while (-get_create_distance() > dist && seconds() - startTime < secondTimeout) { msleep(10); }
	}
	
	createStop();
	
	printf("Distance Moved: %dmm\n", -get_create_distance(0)); 

	
}


//speed of -500 to 500mm/sec
//0 to 359 degrees
void rotate(int speed, int degrees) {
	set_create_normalized_angle(0);
	
	int absSpeed = speed;
	if(absSpeed < 0)
	{
		absSpeed = -absSpeed;
	}
	
	int absDegrees = degrees;
	if(absDegrees < 0){absDegrees = -absDegrees;}
	
	if(absSpeed >= 0 && absSpeed < 50)
	{
		degrees = 0.96 * degrees;
	}
	else if(absSpeed >= 50 && absSpeed < 150)
	{
		if(absDegrees < 90)
		{
			degrees = 0.98 * degrees;
		}
		else if(absDegrees >=90 && absDegrees < 180)
		{
			degrees = 0.94 * degrees; //works
		}
		else if(absDegrees >= 180 && absDegrees < 270)
		{
			degrees = 0.95 * degrees; //works
		}
		else if(absDegrees >= 270)
		{
			degrees = 0.96 * degrees; //works ---
		}
	}
	else if(absSpeed >= 150 && absSpeed < 250)
	{
		if(absDegrees < 90)
		{
			degrees = 0.98 * degrees;
		}
		else if(absDegrees >=90 && absDegrees < 180)
		{
			degrees = 0.87 * degrees; //works
		}
		else if(absDegrees >= 180 && absDegrees < 270)
		{
			degrees = 0.89 * degrees; //works
		}
		else if(absDegrees >= 270)
		{
			degrees = 0.95 * degrees; //okay
		}
	}
	else if(absSpeed >= 250 && absSpeed < 350)
	{
		if(absDegrees < 90)
		{
			degrees = 0.98 * degrees;
		}
		else if(absDegrees >=90 && absDegrees < 180)
		{
			degrees = 0.76 * degrees; //works
		}
		else if(absDegrees >= 180 && absDegrees < 270)
		{
			degrees = 0.81 * degrees; //works
		}
		else if(absDegrees >= 270)
		{
			degrees = 0.90 * degrees; //okay
		}
	}
	else if(absSpeed >= 350 && absSpeed < 500) //bad
	{
		if(absDegrees < 90)
		{
			degrees = 0.98 * degrees;
		}
		else if(absDegrees >=90 && absDegrees < 180)
		{
			degrees = 0.76 * degrees; 
		}
		else if(absDegrees >= 180 && absDegrees < 270)
		{
			degrees = 0.81 * degrees; 
		}
		else if(absDegrees >= 270)
		{
			degrees = 0.88 * degrees; //okay
		}
	}
	
	//change degrees based on speed and value
	
	//speed degree compensation
	//if(speed >= 200){degrees = degrees - (2.3 * (degrees * 0.1));} //fast speed
	//else if(speed > 40 && speed < 200){degrees = degrees;} //mid speed
	//else if(speed <= 40 && speed > 8){degrees = degrees - (1.1 * (degrees * 0.1));} //slow speed
	
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

//curves, 100cm = 110cm
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
	 
	create_disconnect();
	create_connect();
	
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
			
	create_disconnect();
	
	create_connect();
	create_write_byte(153);
	create_disconnect();
	create_connect();
	
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
		compensation = 5;
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
		compensation = 5;
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
	
	printf("\nspeed1: %d\nspeed2:%d\nangle1: %d\nangle2: %d\n\n",
	speed1, speed2, angle1, angle2
	);
	
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
	 
	create_disconnect();
	msleep(75);
	create_connect();
	
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
			
	create_disconnect();
	
	msleep(75);
	create_connect();
	msleep(75);
	create_write_byte(153);
	create_disconnect();
	msleep(75);
	create_connect();
	msleep(75);
	
}


