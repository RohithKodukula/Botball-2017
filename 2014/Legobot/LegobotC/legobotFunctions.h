#ifndef _LEGOBOTFUNCTIONS_H_
#define _LEGOBOTFUNCTIONS_H_

//miscellaneous functions
void legobotInit();
void halt();
void rollStop();

//movement functions
void moveStraight(int power);
void moveToDist(int power, int dist);
void moveToDistWithTribbleGrabbing(int power, int dist);
void moveToWallAlign(int power);
void moveToTouch(int power);
void moveUntilMaxDist(int power);
//void moveToDistWithPausingPomCapture(int power, int dist);

//wall align functions
void arcToWallAlign(int power, int arcLeft, int extremeArc);

//turning functions
void rotate(double degrees);
void turn(double degrees);
void turn_OLD(int speed, int degrees);

//arm functions
void resetArm();
void raiseArm();
void moveArm(int pos);

//pom collection functions
void runPomAligner();
void spinnerStop();
void spinnerStart();
int capturePom();

//servo functions
void setHangerClawPosition(int position);
void kick();
void flickPom();
void setServoSlow(int targetPos, int sleepTime);

//get sensor data functions
int getArmDownSensorValue();
int getArmUpSensorValue();
int getLeftTouchSensor();
int getRightTouchSensor();

#endif
