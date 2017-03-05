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
	
//	Servo disturber(2);
	Servo dumper(3);
	dumper.setPosition(2000);
//	disturber.setPosition(700);
//	disturber.enable();
	dumper.enable();
	
	/*rWheel.motor(60);
	lWheel.motor(-65);
	spinner.moveAtVelocity(700);
	
	long time = systime();
	
	while (systime() - time < 7500) {
		msleep(500);
	}
	*/
	
	rWheel.motor(60);
	lWheel.motor(60);
	rWheel.off();
	lWheel.off();
	spinner.off();
	msleep(500);
	dumper.setPosition(900);
	msleep(500);
	//cout << spinner.getPosition() << endl;
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
