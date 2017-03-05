// ------ CONSTANTS -------

//ports
const int MINI_SERVO_PORT = 3;
const int LEFT_MOTOR = 0;
const int RIGHT_MOTOR = 2;
const int LIGHT_SENSOR = 6;

//constants
const double TICKS_PER_CM = 48.80;
const double LEFT_MULTIPLIER = 1.0;
const double TICKS_PER_DEGREE = 5.73;
const int TURN_SPEED = 50;

const double MILLIS_PER_DEGREE = 12.2;


//servo positions
const int CLAW_OPEN = 100;
const int CLAW_CLOSE = 350;


// ---- ROUTINE ----

int main() {
	
	initialize();
	
	routine();
	
	/*int i;
	for (i = 0; i < 8; i++) {
		//moveToDist(150);
		newRotate(90);
		msleep(1000);
		//msleep(5000);
		//moveToDist(-150);
		//msleep(5000);
	}*/
	
	//moveToDist(100);
	
	//routine();
	
	return 0;
	
}

void routine() {
	
	//21cm from pipe
	
	closeClaw();
	
	printf("Flash light to continue\n");
	while(analog10(LIGHT_SENSOR)>500){msleep(10);}
	msleep(200);
	while(analog10(LIGHT_SENSOR)>500){msleep(10);} //double check
	shut_down_in(119);
	
	msleep(500);
	
	//rotate to face 1st pom clump
	newRotate(87);
	msleep(250);
	
	moveToDist(2);
	openClaw();
	
	//move to poms
	moveToDist(25);
	msleep(250);
	
	//rotate to 2nd pom clump
	newRotate(-26);
	msleep(250);
	
	//move diagonal to 2nd poms
	moveToDist(129);
	msleep(250);
	
	//rotate to end zone
	newRotate(24);
	msleep(250);
	
	//move to end zone
	moveToDist(28);
	msleep(250);
	
	moveToDist(-8);
	msleep(250);
	/*closeClaw();
	msleep(500);
	openClaw();
	msleep(500);*/
	moveToDist(8);
	
	//back up from end zone
	moveToDist(-86);
	closeClaw();
	msleep(1000);
	
	
	//rotate to face secret tunnel
	newRotate(90);
	msleep(250);
	
	//wall align
	moveToDist(-43);
	msleep(500);
	
	//move through tunnel
	moveToDist(201);
	msleep(250);
	
	
	
	//END OF DOUBLE ELIM CODE
	killa();
	/* ACTIVATE THE STUFF BELOW FOR LEGIT STUFF AND COMMENT OUT KILLA. URBAN GORILLA.
	//rotate to face 3rd pom clump on other side
	newRotate(89);
	msleep(250);
	
	openClaw();
	msleep(1000);
	
	
	//move to 3rd pom clump
	moveToDist(85);
	msleep(250);
	
	moveToDist(-8);
	msleep(250);
	
	moveToDist(8);
	msleep(250);
	
	//back up from pom clump
	moveToDist(-70);
	msleep(250);
	
	//wall align
	newRotate(90);
	msleep(250);
	
	moveToDist(-35);
	msleep(400);
	
	//move to get 4th clump
	moveToDist(58);
	msleep(250);
	
	newRotate(93);
	msleep(250);
	
	moveToDist(93);
	msleep(250);
	*/
	
}

void initialize() {
	
	set_servo_position(MINI_SERVO_PORT, CLAW_OPEN);
	enable_servo(MINI_SERVO_PORT);
	
}


// ------ FUNCTIONS ------

void openClaw() {
	set_servo_position(MINI_SERVO_PORT, CLAW_OPEN);
}

void closeClaw() {
	set_servo_position(MINI_SERVO_PORT, CLAW_CLOSE);
}

void killa(){
	newRotate(-89);
	moveToDist(50);
	newRotate(-89);
	moveToDist(10);
}
/*
void moveToDist(int distance, int speed) {
	
	if (speed < 0) {
		speed *= -1;
		if (distance < 0) {
			distance *= -1;
		}
	}
	
	double ticksAsDouble = (distance * TICKS_PER_CM);
	
	int ticks = (int) ticksAsDouble;
	int power = abs(speed) * sign(distance);
	
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	
	motor(RIGHT_MOTOR, power);
	motor(LEFT_MOTOR, power * LEFT_MULTIPLIER);
	
	if (speed < 0) {
		while (abs(get_motor_position_counter(RIGHT_MOTOR)) < abs(ticks)) { msleep(10); }
	} else {
		while (abs(get_motor_position_counter(LEFT_MOTOR)) < abs(ticks)) { msleep(10); }
	}
	
	stop();
	
}
*/

void moveToDist(int distance) {
	
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	
	double ticksAsDouble = (distance * TICKS_PER_CM);
	int ticks = (int) ticksAsDouble;
	
	if (distance > 0) {
		
		motor(RIGHT_MOTOR, 90);
		motor(LEFT_MOTOR, 92);
		
		while (abs(get_motor_position_counter(LEFT_MOTOR)) < abs(ticks)) { msleep(10); }
		
		motor(RIGHT_MOTOR, -50);
		motor(LEFT_MOTOR, -50);
		
		msleep(100);
		stop();
		
	} else {
		
		motor(RIGHT_MOTOR, -90);
		motor(LEFT_MOTOR, -91);
		
		while (abs(get_motor_position_counter(LEFT_MOTOR)) < abs(ticks)) { msleep(10); }
		
		motor(RIGHT_MOTOR, 50);
		motor(LEFT_MOTOR, 50);
		
		msleep(100);
		stop();
		
	}
	
}

void rotate(double degrees) {
	
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	
	double ticks = degrees * TICKS_PER_DEGREE;
	
	if (ticks < 0) {
		
		motor(LEFT_MOTOR, -1 * TURN_SPEED * LEFT_MULTIPLIER);
		motor(RIGHT_MOTOR, TURN_SPEED);
		
		while (get_motor_position_counter(LEFT_MOTOR) > ticks) {
			msleep(10);
		}
		
	} else {
		
		motor(LEFT_MOTOR, TURN_SPEED * LEFT_MULTIPLIER);
		motor(RIGHT_MOTOR, -1 * TURN_SPEED);
		
		while (get_motor_position_counter(LEFT_MOTOR) < ticks) {
			msleep(10);
		}
		
	}
	
	stop();
	
}

void newRotate(int degrees) {
	
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	
	double millisAsDouble = 0.0;
	millisAsDouble = (double) degrees * MILLIS_PER_DEGREE;
	
	int millis = abs((int) millisAsDouble);
	
	printf("Milliseconds: %d\n", millis);
	
	if (degrees > 0) {
		
		motor(LEFT_MOTOR, 50);
		motor(RIGHT_MOTOR, -50);
		
		msleep(millis);
		
		stop();
		
	} else {
		
		motor(LEFT_MOTOR, -50);
		motor(RIGHT_MOTOR, 50);
		
		msleep(millis);
		
		stop();
		
	}
	
}

void stop() {
	freeze(LEFT_MOTOR);
	freeze(RIGHT_MOTOR);
}

//utilities

int abs (int x) {
	if (x < 0) return (-1 * x);
	else return x;
}

int sign (int x) {
	if (x < 0) return -1;
	else return 1;
}
