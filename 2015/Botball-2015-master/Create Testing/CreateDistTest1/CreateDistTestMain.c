const int speed = 100;
const int distance = 1000;

int main() {
	
	create_connect();
	serialTestingUtility();
	
	
	
	return 0;
	
}


























































/*
pongLoadingSubroutine function by John S. 3/07/15
--------------------------------------------------------------------
This function starts at the base of the first pipe, collects all 3 ping pong balls, 
and stops after the third ping pong ball is collected.
*/
void pongLoadingSubroutine()
{
	int pipeNumber;
	for(pipeNumber=1; pipeNumber<=3; pipeNumber++)
	{
		moveArm(armHeight(pipeNumber));
		msleep(ARM_RAISE_DURATION);
		closePongPinchers();
		moveElevator(elevatorHeight(pipeNumber));
		msleep(ELEVATOR_RAISE_DURATION);
		openPongPinchers();
		lowerElevatorToBottom();
		
		if(pipeNumber!=3)
		{
			moveWithSerial(MOVE_SLOW_SPEED, DISTANCE_BETWEEN_PIPES);
			msleep(PIPE_TRAVEL_DURATION);
		}
	}
}




void serialTestingUtility() {
	
	int x = 0;
	
	console_clear();
	
	set_a_button_text("Bytecode Move");
	set_b_button_text("Serial Stability");
	set_c_button_text("Ping Pong Fling");
	
	printf("--------MAIN MENU--------\n\n");
	printf("\"Bytecode Move\"\n -- Test moving with bytecode accuracy\n\n");
	
	printf("\"Serial Test\"\n -- Test moving with bytecode stability\n\n");
	
	while (!side_button()) {
		
		if (a_button()) {
			
			console_clear();
			
			printf("\n\nMoving to distance %d cm at speed %d mm/s with serial function...\n\n", distance, speed);
			moveWithSerial(speed, distance);
			
			console_clear();
			
			printf("\n\tRunning test.....");
			
			set_a_button_text("Bytecode Move");
			set_b_button_text("Serial Stability");
			set_c_button_text("------");
			
		}
		
		if (b_button()) {
			
			console_clear();
			
			printf("\n\nMoving to distance %d cm at speed %d mm/s with serial function...\n\n", distance, speed);
			
			while (x < 1000) {
				
				moveWithSerial(speed, distance);
				x++;
				moveWithSerial(speed, (-1 * distance));
				x++;
				
			}
			
			console_clear();
			
			printf("\n\tRunning test.....");
			
			set_a_button_text("Bytecode Move");
			set_b_button_text("Serial Stability");
			set_c_button_text("------");
			
		}
		
		if (c_button()) {
			
			console_clear();
			
			printf("\n\nFlinging poms...\n\n");
			
			turnWithSerial(250, -90);
			
			console_clear();
			
			//printf("\n\tRunning test.....");
			
			set_a_button_text("Bytecode Move");
			set_b_button_text("Serial Stability");
			set_c_button_text("------");
			
		}
		
		msleep(100);
		
	}
}

void moveWithSerial(int speed, int distance) {
	
	printf("\nspeed value recieved: %d\ndistance value recieved: %d\n",
	speed, distance);
	
	int dist1, dist2, speed1, speed2, counter1 = 0;
	
	if (speed < 0) {
		
		speed1 = 0;
		speed2 = speed * -1;
		distance *= -1;
		
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
	
	msleep(300);
	create_clear_serial_buffer();
	msleep(300);
	
	create_write_byte(128); //initializes mode to full
	msleep(20);
	create_write_byte(132);
	msleep(20);
	
	create_write_byte(152); // script size
	msleep(20);
	create_write_byte(13);
	msleep(20);
	
	create_write_byte(137); //drive straight
	msleep(20);
	create_write_byte(speed1);
	msleep(20);
	create_write_byte(speed2);
	msleep(20);
	create_write_byte(128);
	msleep(20);
	create_write_byte(0);
	msleep(20);
	
	create_write_byte(156); //wait specified distance
	msleep(20);
	create_write_byte(dist1);
	msleep(20);
	create_write_byte(dist2);
	msleep(20);
	
	create_write_byte(137); //stop
	msleep(20);
	create_write_byte(0);
	msleep(20);
	create_write_byte(0);
	msleep(20);
	create_write_byte(0);
	msleep(20);
	create_write_byte(0);
	msleep(20);
	create_write_byte(153);
	
	msleep(300);
	create_clear_serial_buffer();
	msleep(300);
	
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
			compensation = 6;
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
			compensation = 6;
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
	create_clear_serial_buffer();
	msleep(300);
	
	create_write_byte(128); //initializes mode to full
	msleep(20);
	create_write_byte(132);
	msleep(20);
	
	create_write_byte(152); //script size
	msleep(20);
	create_write_byte(13);
	msleep(20);
	
	create_write_byte(137); //spin
	msleep(20);
	create_write_byte(speed1);
	msleep(20);
	create_write_byte(speed2);
	msleep(20);
	create_write_byte(0);
	msleep(20);
	create_write_byte(0);
	msleep(20);
	
	create_write_byte(157); //wait angle
	msleep(20);
	create_write_byte(angle1);
	msleep(20);
	create_write_byte(angle2);
	msleep(20);
	
	create_write_byte(137); //stop
	msleep(20);
	create_write_byte(0);
	msleep(20);
	create_write_byte(0);
	msleep(20);
	create_write_byte(0);
	msleep(20);
	create_write_byte(0);
	msleep(20);
	create_write_byte(153);
	
	msleep(300);
	create_clear_serial_buffer();
	msleep(300);
	
}


