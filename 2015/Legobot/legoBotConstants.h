
#ifndef _LEGOBOTCONSTANTS_H_
#define _LEGOBOTCONSTANTS_H_

// Motor ports
const int LEFT_MOTOR;
const int RIGHT_MOTOR;

// Motor constants
const double TICKS_PER_CM;
const double TICKS_PER_DEGREE;
const double TICKS_PER_DEGREE_LEFT;
const double TICKS_PER_DEGREE_RIGHT;

// Servo ports
const int CLAW_MICRO_SERVO;
const int CLAW_BASE_SERVO;
const int BASKET_SERVO;
const int POM_SORTING_SERVO;

// Movement speeds (in mm/s)
const int FAST_SPEED;
const int MID_SPEED;
const int SLOW_SPEED;
const int SUPER_SLOW_SPEED;

// Power levels (%)
const int FULL_POWER;
const int MID_POWER;
const int LOW_POWER;

// Camera color channels
const int GREEN_CHANNEL;
const int RED_CHANNEL;

// Servo positions

const int POM_SORTING_NEUTRAL;
const int POM_SORTING_BASKET;
const int POM_SORTING_TABLE;
const int POM_JIGG_R;
const int POM_JIGG_L;
const int POM_SORT_R;

const int BASKET_NEUTRAL;
const int BASKET_JIGGLE;
const int BASKET_BIG_JIGGLE;
const int BASKET_DUMP;

const int CLAW_CLOSED;
const int CLAW_SLIGHTLY_OPEN;
const int CLAW_OPEN;

const int CLAW_POM_DEPOSIT;
const int CLAW_RAISED;
const int CLAW_DOWNISH;
const int CLAW_DOWN;

// Durations
const int POM_DEPOSIT_BASKET_DURATION;
const int POM_DEPOSIT_TABLE_DURATION;

// Miscellaneous
const int MIN_BLOB_AREA;

#endif

