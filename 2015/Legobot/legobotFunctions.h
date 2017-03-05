
#ifndef _LEGOBOTFUNCTIONS_H_
#define _LEGOBOTFUNCTIONS_H_

// Miscellaneous functions
void legobotInitialize();
int abs(int x);
int sign(int x);

// Movement functions
void stop();
void rollStop();
void moveToDist(int velocity, double dist);
void jiggleEntireRobot();

// Turning functions
void rotate(double degrees);
void pivotOnLeft(double degrees);
void pivotOnRight(double degrees);

// Pom collection functions
int capturePom();

// Servo functions
void smoothMove();
void scoopPoms();
void scooperJiggle();
void setServoSlow(int targetPos, int sleepTime);

// Sorting functions
void sortSinglePom();
void sortSixPoms();
void sortAllPoms();

#endif
