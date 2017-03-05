
//motor ports
const int RIGHT_ARM_MOTOR = 1;
const int LEFT_ARM_MOTOR = 3;
const int ELEVATOR_MOTOR = 0;

//servo ports
const int PONG_CLAW = 2;
const int FRONT_CLAW = 3;

//sensor ports
const int ARM_LOWER_CHERRY = 15;
const int ELEVATOR_IR = 5;
const int LIGHT_SENSOR = 6;

//IR sensor values
const int IR_RANGE_MIN_REASONABLE = 200;
const int IR_RANGE_MAX_REASONABLE = 500;

const int ELEVATOR_IR_MAX_REASONABLE = 700;
const int ELEVATOR_IR_MIN_REASONABLE = 700;

const int ELEVATOR_IR_MIN_DEFAULT = 300;
const int ELEVATOR_IR_MAX_DEFAULT = 600;

int ELEVATOR_IR_MIN = 0;
int ELEVATOR_IR_MAX = 0;

//real arm positions
const int ARM_SUPER_HIGH = 5200;
const int ARM_HIGH = 2200;
const int ARM_MID = 1900;
const int ARM_LOW = 1000;
const int ARM_POM_BOARD_HIGH = 3600;
const int ARM_CUBE_LOW = 615;

int ARM_STATE = 0;
int ELEVATOR_STATE = 0;

//claw position constants
const int FRONT_CLAW_OPEN = 680;
const int FRONT_CLAW_CLOSED = 1300;

const int PONG_CLAW_OPEN = 524;
const int PONG_CLAW_CLOSED = 1750;

//slide position constants
const int ELEVATOR_TOP = 1520;
const int ELEVATOR_MID = 850;

//turn speeds
const int TURN_SLOW_SPEED = 20;
const int TURN_MID_SPEED = 150;
const int TURN_FAST_SPEED = 300;

//move speeds
const int MOVE_SLOW_SPEED = 100;
const int MOVE_MID_SPEED = 300;
const int MOVE_FAST_SPEED = 450;

//times
const int CREATE_BYTE_SEND_WAIT = 15;
