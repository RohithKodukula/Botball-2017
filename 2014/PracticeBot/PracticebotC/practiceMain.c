int R_MOTOR = 1;
int L_MOTOR = 3;

int main() {	
	moveStraight(66.6);
	turn(100,10);
}

void moveStraight(double distance) {
	
	clear_motor_position_counter(R_MOTOR);
	double ticksPerCentimeter = 75.35;
	double ticks = 75.35 * distance;
	printf("Ticks: %d\n", ticks);
	motor(R_MOTOR , 49);
	motor(L_MOTOR , 50);
	printf("Target position: %d\n", 75*66);
	while ((double)get_motor_position_counter(R_MOTOR) < ticks) {
		msleep(50);
		printf("%d\n",get_motor_position_counter(R_MOTOR));
	}

}
void turn(double degrees, int speed) { 
	
	double ticksPerCentimeter = 75.35; (degrees/360);
	int ticks = (int) ticksPerCentimeter;
	ticks = (ticks > 0) ? ticks : -ticks;
	printf("Ticks: %d\n", ticks);
	
	mav(R_MOTOR, (degrees > 0) ? 100 : 10);
	mav(L_MOTOR, (degrees > 0) ? 10 : 100);
	while(abs(get_motor_position_counter(R_MOTOR)) < ticks);
	ao();
	
}
