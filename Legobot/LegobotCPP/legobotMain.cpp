#include <iostream>
#include <kovan/motors.hpp>
#include <kovan/motors.h>

#include "legobotFunctions.cpp"

using namespace std;


class MyMotor: public Motor {
	public:
		MyMotor(int port): Motor(port) {
			tmp = 400;
		};
		
		int getPosition() {
			return get_motor_position_counter(port());
		};
	private:
		int tmp;

};

int main(int argc, char *argv[])
{
	const int x = 0;
	MyMotor spinner(x);
	Motor lWheel(1);
	Motor rWheel(3);
	
	rWheel.motor(60);
	lWheel.motor(-60);
	spinner.moveAtVelocity(600);
	
	for (int i = 0; i < 100; i++) {
		cout << spinner.getPosition() << endl;
	};	
	
	sleep(5);
	cout << spinner.getPosition() << endl;
	return 0;
}


/*
class DriveMotor: public Motor {
	public:
		void DeviceMotor(int port)  {
			Motor motor(port);
		};
		
		void setSpeedMultiplier(float multiplier) {
			speedMultiplier = multiplier;
		};
		
		float getSpeedMultiplier() {
			return speedMultiplier;
		};
		
	private:
		float speedMultiplier;
		int motorPort;
		Motor motor(motorPort);
}
*/
