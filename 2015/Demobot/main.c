
const int RIGHT_MOTOR = 3;
const int LEFT_MOTOR = 1;

const double TICKS_PER_CM = 67.25;

int main() {
	
	driveStraight(50, 20);
	
	return 0;
	
}

int abs(int x) {
	
	if (x < 0) return (-1 * x);
	else return x;
	
}

int signOf(int x) {
	
	if (x < 0) return -1;
	else return 1;
	
}

void stop() {
	
	freeze(RIGHT_MOTOR);
	freeze(LEFT_MOTOR);
	
}

void driveStraight(int velocity, int distance) { //speed in percentage, dist in cm
	
	int ticks = abs(distance * TICKS_PER_CM);
	
	double compensation = 1.05;
	
	int rightPower = (int) ((double) velocity * compensation);
	int leftPower = velocity;
	
	clear_motor_position_counter(RIGHT_MOTOR);
	clear_motor_position_counter(LEFT_MOTOR);
	
	printf("\nTarget ticks: %d\nLeft power: %d\nRight power: %d\n\n", ticks, leftPower, rightPower);
	
	motor(RIGHT_MOTOR, rightPower);
	motor(LEFT_MOTOR, leftPower);
	
	while (abs(get_motor_position_counter(RIGHT_MOTOR)) < ticks) {
		msleep(10);
	}
	
	stop();
	
	
}

void turn(int speed, int degrees) { //speed in mm/s
	
	
	
}

void pivotOnLeft(int speed, int degrees) {
	
	
	
}

void pivotOnRight(int speed, int degrees) {
	
	
	
}
