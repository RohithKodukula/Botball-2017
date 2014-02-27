int R_MOTOR = 0;
int L_MOTOR = 2;
int main() {	
	moveStraight();
}

void moveStraight() {
motor(R_MOTOR , -50);
motor(L_MOTOR , -50);
msleep(5000);
ao();
}


