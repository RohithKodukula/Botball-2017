#include "legobotConstants.h"
#include "legobotFunctions.h"


int main() {
	
	//Tribble collecting/drive straight test!
	legobotInit();
	motor(RIGHT_MOTOR, 40*1.05);
	motor(LEFT_MOTOR, 40);
	
	mav(SPINNER_MOTOR, 500);
	
	thread dipstickThread;
	dipstickThread = thread_create(dipstickDoesShit);
	thread_start(dipstickThread);
	
	msleep(10000);
	
	ao();
	msleep(1000);
	thread_destroy(dipstickThread);
	
	
}
