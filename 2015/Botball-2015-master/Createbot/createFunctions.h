
# ifndef _CREATEFUNCTIONS_H_
# define _CREATEFUNCTIONS_H_

// Miscellaneous functions
int abs(int x);
int armStateToTicks(int armState);
int elevatorStateToTicks(int elevatorState);
void waitByteSendInterval();

// Sensor functions
int armCherrySensorIsTriggered();
int elevatorIRSensorIsTriggered();
int getElevatorIRSensorValue();
int getMillimeterDistance();
double distanceValueToMM(double y);

// Initialization
void createInit();
void initializeQuick();
void initializeFull();

// Servo functions
void openFrontClaw();
void closeFrontClaw();
void openPongClaw();
void closePongClaw();

// Arm movement
void moveArmToPosition(int position);
void moveArmToPositionWithRecalibration(int position);
void raiseArmToTop();
void raiseArm(int position);
void lowerArm(int position);
void moveArmToTop();
void moveArmToMiddle();
void moveArmToLow();
void lowerArmToBottom();

// Elevator movement
void moveElevatorToPosition(int position);
void raiseElevator(int position);
void lowerElevator(int position);
void lowerElevatorToBottom();

// Create movement
void moveStraight(int vel);
void createStop();
void moveToWallAlign(int dist, int speed, double secondTimeout);
void moveToDist(int dist, int speed);
void rotate(int degrees, int speed);

// Create serial movement
void moveWithSerial(int speed, int distance);
void turnWithSerial(int speed, int degrees);

// IR calibration functions
void runIRCalibrationUtility();
void setNormalizedIRValues(int armMin, int armMax, int elevatorMin, int elevatorMax);

# endif
