
// Motor ports
const int LEFT_MOTOR = 1;
const int RIGHT_MOTOR = 3;

// Motor constants
const double TICKS_PER_CM = 51.3699;
const double TICKS_PER_DEGREE;
const double TICKS_PER_DEGREE_LEFT;
const double TICKS_PER_DEGREE_RIGHT;

// Servo ports
const int CLAW_MICRO_SERVO = 0;
const int CLAW_BASE_SERVO = 3;
const int BASKET_SERVO = 2;
const int POM_SORTING_SERVO = 1;

// Movement speeds (in mm/s)
const int FAST_SPEED = 80;
const int MID_SPEED = 60;
const int SLOW_SPEED = 40;
const int SUPER_SLOW_SPEED = 20;

// Power levels (%)
const int FULL_POWER = 100;
const int MID_POWER = 60;
const int LOW_POWER = 30;

// Camera channels
const int GREEN_CHANNEL = 0;
const int RED_CHANNEL = 1;

// Servo positions

const int POM_SORTING_NEUTRAL = 1070;
const int POM_SORTING_BASKET = 420;
const int POM_SORTING_TABLE = 1900;
const int POM_JIGG_L = 800;
const int POM_JIGG_R = 700;
const int POM_SORT_R = 670;

const int BASKET_NEUTRAL = 1850;
const int BASKET_JIGGLE = 1710;
const int BASKET_BIG_JIGGLE = 1680;
const int BASKET_DUMP = 150;

const int CLAW_CLOSED = 510;
const int CLAW_SLIGHTLY_OPEN = 300;
const int CLAW_OPEN = 130;

const int CLAW_POM_DEPOSIT = 1400;
const int CLAW_RAISED = 1000; 
const int CLAW_DOWNISH = 200;
const int CLAW_DOWN = 500;

// Durations
const int POM_DEPOSIT_BASKET_DURATION = 210;
const int POM_DEPOSIT_TABLE_DURATION = 450;

// Miscellaneous
const int MIN_BLOB_AREA = 4000;
