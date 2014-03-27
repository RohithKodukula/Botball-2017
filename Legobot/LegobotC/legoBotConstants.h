
#ifndef _LEGOBOTCONSTANTS_H_
#define _LEGOBOTCONSTANTS_H_

//motor ports
const int LEFT_MOTOR;
const int RIGHT_MOTOR;
const int SPINNER_MOTOR;
const int ARM_MOTOR;

//motor constants
const int TICKS_PER_CM;
const double TICKS_PER_DEGREE;
const double R_WHEEL_CALIBRATION_CONSTANT;

//servos
const int DUMPER_SERVO;
const int KICKER_SERVO;
const int POM_ALIGNER_SERVO;
const int HANGER_SERVO;
const int DISTANCE_SENSOR;

//sensor ports
const int ARM_DOWN_SENSOR;
const int ARM_UP_SENSOR;
const int LEFT_TOUCH_SENSOR;
const int RIGHT_TOUCH_SENSOR;

//arm positions in ticks
const int ARM_TOP_POS;

//hanger position constants
const int HANGER_FORWARD;
const int HANGER_BACK;
const int HANGER_UP;

//kicker servo
const int KICKER_KICKED;
const int KICKER_BACK;

//dumper position constants
const int DUMPER_DUMP;
const int DUMPER_UP;

//disturber position constants
const int POM_ALIGNER_OPEN;
const int POM_ALIGNER_CLOSE;
const int POM_ALIGNER_PARALLEL;

//motor powers
const int FAST_SPEED;
const int NORMAL_SPEED;
const int SLOW_SPEED;
const int SUPER_SLOW_SPEED;

//motor power to maintain arm height
const int ARM_HOLDING_POWER;

#endif
