#include <iostream>
#include <kovan/motors.hpp>

#include "legobotFunctions.cpp"

using namespace std;

int main(int argc, char *argv[])
{
	Motor spinner(0);
	Motor lWheel(1);
	Motor rWheel(3);
	
	rWheel.motor(60);
	lWheel.motor(-60);
	spinner.moveAtVelocity(600);
	sleep(20);
}


class DriveMotor {
	public:
		void DeviceMotor(int motorPort)  {
			
		};
		
		void setSpeedMultiplier(float multiplier) {
			speedMultiplier = multiplier;
		};
		
		float getSpeedMultiplier() {
			return speedMultiplier;
		};
		
	private:
		float speedMultiplier;
		Motor motor;
		
