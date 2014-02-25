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

# endif
