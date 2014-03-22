# ifndef _CREATEFUNCTIONS_H_
# define _CREATEFUNCTIONS_H_

//init
void createInit();

//arm
void raiseArm(int position);
void raiseArmTo1500();
void raiseArmToTop();
void lowerArm(int position);
void lowerArmBySensor();

//create movement
void moveStraight(int vel);
void createStop();
void moveToDist(int dist, int speed);
void rotate(int degrees, int speed);
void arcToPinkTape();
void arcToBlockCapturePosition();

//create serial movement
void moveWithSerial(int speed, int distance);
void turnWithSerial(int speed, int degrees);

//claws
void initActuators();
void setUpperClaw(int position);
void setLowerClaw(int position);

//distance sensor
double getMillimeterDistance();
# endif
