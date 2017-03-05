const int R_MOTOR = 3;
const int L_MOTOR = 1;
const int CLAW_RAISE_SERVO = 1;
const int CLAW_SERVO = 3;
const double TICKS_PER_CM =55;
const double WHEEL_CORRECTION = 1.055;
const double TURN_CONVERSION = 5.8;
const int SLEEP= 58;

//Moving
void moveToDist(int distInCm, int velocity){	

		
	int ticks = 0;
	if (velocity = 0){
		
		printf("You gave me a velocity of 0!\n")
	
	}
	//Moving When Distance is Negative
	if (velocity < 0) {
		
		clear_motor_position_counter(L_MOTOR);
		clear_motor_position_counter(R_MOTOR);
		
		ticks = cmToTicks(distInCm);
		
		motor(L_MOTOR, -velocity * WHEEL_CORRECTION);
		motor(R_MOTOR, -velocity);
		
		while (get_motor_position_counter(R_MOTOR) < ticks) {
			msleep(15);
		}
	//Moving When Distance is Positive	
	} if ( velocity > 0) {
		
		clear_motor_position_counter(L_MOTOR);
		clear_motor_position_counter(R_MOTOR);
		
		ticks = (cmToTicks(distInCm));
		
		motor(L_MOTOR, velocity * WHEEL_CORRECTION);
		motor(R_MOTOR, velocity * .95);
		
		while (get_motor_position_counter(R_MOTOR) < ticks) {
			msleep(15);
		}
		
	}
	
}

//Vertical Claw  Movement
void raiseAboveGround(){
	
	enable_servo(CLAW_RAISE_SERVO);
	set_servo_position(CLAW_RAISE_SERVO,800);
	msleep(750);
	
}	
void raiseToPomDeposit(){
	
	enable_servo(CLAW_RAISE_SERVO);
	set_servo_position(CLAW_RAISE_SERVO,1150);
	msleep(500);
	
}	
void lowerToGround(){
	
	enable_servo(CLAW_RAISE_SERVO);
	set_servo_position(CLAW_RAISE_SERVO,0);
	msleep(500);

}
		
//Claw Capture
void closeClaw(){
		
	enable_servo(CLAW_SERVO);
	set_servo_position(CLAW_SERVO,400);
	msleep(500);

}

//Turning
void turn(int degrees, int turnSpeed) {
	
	//Turn Left if Negative
	if(degrees < 0) {
			motor(L_MOTOR, -turnSpeed);
			motor(R_MOTOR, turnSpeed);
			msleep(degrees/TURN_CONVERSION*SLEEP);
	}
	
	//Turn Right if Positive
	if(degrees > 0) {
			motor(L_MOTOR, turnSpeed);
			motor(R_MOTOR, -turnSpeed);
			msleep(degrees/TURN_CONVERSION*SLEEP);
		
	}
	
}


//Input "moveDist" or "turn"(negative value turns left, positive turns right)
int main()
{
	//moveToDist(distInCm, speed(negative value goes forward))
	//turn(degrees, turnSpeed(turns right if positive))
	//raiseAboveGround, raiseToPomDeposit, lowerToGround
	
	
	raiseAboveGround();
	moveToDist(10,50);
	
}	
				
//Ticks & Centimeters//
int cmToTicks(double cm) {
	
	return (cm * TICKS_PER_CM);
}
