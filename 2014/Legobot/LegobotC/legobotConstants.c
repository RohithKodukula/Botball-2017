
//motor ports
const int LEFT_MOTOR = 2;
const int RIGHT_MOTOR = 0;
const int SPINNER_MOTOR = 1;
const int ARM_MOTOR = 3;

//motor constants
const int TICKS_PER_CM = 52;
const double TICKS_PER_DEGREE = 11.06;
const double R_WHEEL_CALIBRATION_CONSTANT = 1.01;

//servos
const int DUMPER_SERVO = 0;
const int KICKER_SERVO = 1;
const int POM_ALIGNER_SERVO = 2;
const int HANGER_SERVO = 3;
const int BASKET_SERVO = 0;

//sensor ports
const int ARM_DOWN_SENSOR = 3;
const int ARM_UP_SENSOR = 1;
const int LEFT_TOUCH_SENSOR = 14;
const int RIGHT_TOUCH_SENSOR = 12;
const int DISTANCE_SENSOR = 5;
const int LIGHT_SENSOR = 7;

//arm positions in ticks
const int ARM_TOP_POS = 2000;

//hanger position constants
const int HANGER_FORWARD = 2047;
const int HANGER_BACK = 0;
const int HANGER_UP = 1024;

//basket position constants
const int BASKET_UP = 2047;
const int BASKET_DOWN = 800;

//kicker servo
const int KICKER_KICKED = 1800;
const int KICKER_BACK = 725;
const int KICKER_DOWN = 725;

//dumper position constants
const int DUMPER_DUMP = 900;
const int DUMPER_UP = 1960;

//disturber position constants
const int POM_ALIGNER_OPEN = 900;
const int POM_ALIGNER_CLOSE = 200;
const int POM_ALIGNER_PARALLEL = 860;

//motor powers
const int FAST_SPEED = 80;
const int NORMAL_SPEED = 60;
const int MID_SPEED = 60;
const int SLOW_SPEED = 40;
const int SUPER_SLOW_SPEED = 20;

//motor power to maintain arm height
const int ARM_HOLDING_POWER = 15;

//camera color channels
const int GREEN_CHANNEL = 0;
const int PINK_CHANNEL = 1;
