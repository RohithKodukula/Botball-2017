#ifndef _LEGOBOTFUNCTIONS_H_
#define _LEGOBOTFUNCTIONS_H_

void legobotInit();
void halt();
void rollStop();

void moveStraight(int power);
void moveToDist(int power, int dist);
void turn(int speed, int degrees);

void resetArm();
void moveArm(int pos);

void dipstickDoesShit();
void spinnerStop();
void spinner(int speed);

int getArmDownSensorValue();



#endif
