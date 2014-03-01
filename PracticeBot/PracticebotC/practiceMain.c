int R_MOTOR = 0;
int L_MOTOR = 2;
int main() {	
	moveStraight(66.6);
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
	ao();
}
