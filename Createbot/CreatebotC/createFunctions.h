# ifndef _CREATEFUNCTIONS_H_
# define _CREATEFUNCTIONS_H_

//init
void createInit();

//arm
void raiseArm(int position);
void lowerArm(int position);

//create movement
void moveStraight(int vel);
void createStop();
void moveToDist(int dist, int speed);
void rotate(int degrees, int speed);

//create serial movement
void moveWithSerial(int speed, int distance);
void turnWithSerial(int speed, int degrees);

# endif
