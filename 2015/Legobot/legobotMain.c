
#include "legobotConstants.h"
#include "legobotFunctions.h"
#include "legobotVision.h"

void jiggleEntireRobotForever() {
	
	while (1) {
		
		jiggleEntireRobot();
		
	}
	
}

int main() {
	
	emergencyRoutine();
	
	
	
	
	
	
	//console_clear();
	//legobotInitialize();
	
	/*int i;
	for(i=0;i<100;i++)
	{
		printf("run %d\n", i);
		moveToDist(MID_SPEED, 10.0);
		moveToDist(MID_SPEED, -10.0);
		msleep(500);
	}*/
	
	//printLargestArea(RED_CHANNEL);
	
	//pomDepositTestingUtility();
	//moveTestingUtility();
	
	//pomSortingTestingUtility();
	
	
	//msleep(5000);
	//set_servo_position(CLAW_BASE_SERVO, CLAW_DOWN);
	//msleep(5000);
	//scoopPoms();
	
	/*
	thread jiggleThread = thread_create(jiggleEntireRobotForever);
	

	thread_start(jiggleThread);
	
	msleep(2000);
	sortSixPoms();
	sortSixPoms();
	
	thread_destroy(jiggleThread);
	*/
	
	//msleep(2000);
	//set_servo_position(BASKET_SERVO, BASKET_NEUTRAL);
	//msleep(1000);
	//jiggleBasket(5);
	//moveToDist(60, 100.00);
	//pomSortingTestingUtility();
	
	//sortSinglePom();
	//sortSixPoms();
	
	/*
	msleep(500);
	jiggleBasket(2);
	msleep(800);
	sortSinglePom();
	msleep(500);
	jiggleBasket(2);
	msleep(800);
	sortSinglePom();
	*/
	
	return 0;
	
}

void emergencyRoutine(){
	console_clear();
	//legobotInitialize();
	enable_servos();
	
	clear_motor_position_counter(0);
	clear_motor_position_counter(1);
	clear_motor_position_counter(2);
	clear_motor_position_counter(3);
	
	//put claw up & open in start box
	msleep(1000);
	set_servo_position(CLAW_BASE_SERVO, CLAW_RAISED);
	msleep(1000);
	set_servo_position(CLAW_MICRO_SERVO, CLAW_SLIGHTLY_OPEN);
	msleep(6000);
	
	//light stuff goes here
	
	
	//cose claw and pull out of start box
	set_servo_position(CLAW_MICRO_SERVO, CLAW_CLOSED);
	msleep(500);
	moveToDist(SLOW_SPEED, 35);
	msleep(500);
	
	//turn to poms
	rotate(-50);
	msleep(700);
	
	//set claw for pom grabbing
	set_servo_position(CLAW_BASE_SERVO, CLAW_DOWN);
	msleep(500);
	set_servo_position(CLAW_MICRO_SERVO, CLAW_OPEN);
	msleep(500);
	
	//go to pom clump & grab
	moveToDist(SLOW_SPEED, 25);
	msleep(700);
	set_servo_position(CLAW_MICRO_SERVO, CLAW_CLOSED);
	msleep(1000);
	rotate(-90);
	msleep(500);
	moveToDist(FAST_SPEED, 40);
	
	
}

void pomSortingTestingUtility() {
	
	console_clear();
	
	set_a_button_text("Sort 1");
	set_b_button_text("Sort 6");
	set_c_button_text("Sort 12");
	
	printf("--------MAIN MENU--------\n\n");
	printf("\"Sort 1\"\n -- Test sorting a single pom\n");
	printf("\"Sort 6\"\n -- Sort six poms\n");
	printf("\"Sort More\"\n -- Sort a full load of poms\n");
	
	while (!side_button()) {
		
		if (a_button()) {
			
			console_clear();
			
			sortSinglePom();
			
			console_clear();
			
			set_a_button_text("Sort 1");
			set_b_button_text("Sort 6");
			set_c_button_text("Sort More");
			
			} else if (b_button()) {
			
			console_clear();
			
			sortSixPoms();
			
			console_clear();
			
			set_a_button_text("Sort 1");
			set_b_button_text("Sort 6");
			set_c_button_text("Sort More");
			
			} else if (c_button()) {
			
			console_clear();
			
			sortMorePoms();
			
			console_clear();
			
			set_a_button_text("Sort 1");
			set_b_button_text("Sort 6");
			set_c_button_text("Sort More");
			
		}
		
		msleep(50);
		
	}
	
}

void pomDepositTestingUtility() {
	
	console_clear();
	
	set_a_button_text("Deposit Right");
	set_b_button_text("Deposit Left");
	
	printf("--------MAIN MENU--------\n\n");
	printf("\"Deposit Right\"\n -- Test depositing a pom in the basket\n\n");
	printf("\"Deposit Left\"\n -- Test depositing a pom to the left onto the table\n\n");
	
	while (!side_button()) {
		
		if (a_button()) {
			
			console_clear();
			
			printf("\n\nDepositing in basket...");
			
			depositPomInBasket();
			
			console_clear();
			
			set_a_button_text("Deposit Right");
			set_b_button_text("Deposit Left");
			
		}
		
		
		if (b_button()) {
			
			console_clear();
			
			printf("\n\nDepositing on the table...");
			
			depositPomOnTable();
			
			console_clear();
			
			set_a_button_text("Deposit Right");
			set_b_button_text("Deposit Left");
			
		}
		
		msleep(50);
		
	}
	
}

void moveTestingUtility() {
	
	set_a_button_text("AA");
	set_b_button_text("BB");
	set_c_button_text("CC");
	moveToDist(400,5);
	moveToDist(400,-5);
	msleep(200);
	moveToDist(400,5);
	
}
