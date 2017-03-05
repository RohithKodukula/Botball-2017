
# ifndef _CREATECONSTANTS_H_
# define _CREATECONSTANTS_H_

//motor ports
const int RIGHT_ARM_MOTOR;
const int LEFT_ARM_MOTOR;
const int ELEVATOR_MOTOR;

//servo ports
const int PONG_CLAW;
const int FRONT_CLAW;

//sensor ports
const int ARM_LOWER_CHERRY;
const int ELEVATOR_IR;
const int LOWER_CLAW;
const int ARM_DOWN_SENSOR_PORT;
const int LIGHT_SENSOR;

//sensor constants
const int IR_RANGE_MIN_REASONABLE;
const int IR_RANGE_MAX_REASONABLE;

const int ELEVATOR_IR_MAX_REASONABLE;
const int ELEVATOR_IR_MIN_REASONABLE;

const int ELEVATOR_IR_MIN_DEFAULT;
const int ELEVATOR_IR_MAX_DEFAULT;

int ELEVATOR_IR_MIN;
int ELEVATOR_IR_MAX;

//arm positions in ticks
const int ARM_SUPER_HIGH;
const int ARM_HIGH;
const int ARM_MID;
const int ARM_LOW;
const int ARM_POM_BOARD_HIGH;
const int ARM_CUBE_LOW;

//variable elevator and arm height states
int ARM_STATE;
int ELEVATOR_STATE;

//claw position constants
const int FRONT_CLAW_OPEN;
const int FRONT_CLAW_CLOSED;
const int PONG_CLAW_OPEN;
const int PONG_CLAW_CLOSED;

//slide position constants (relative to lowerBySensor)
const int ELEVATOR_TOP;
const int ELEVATOR_MID;

//turn speeds
const int TURN_SLOW_SPEED;
const int TURN_MID_SPEED;
const int TURN_FAST_SPEED;

//move speeds
const int MOVE_SLOW_SPEED;
const int MOVE_MID_SPEED;
const int MOVE_FAST_SPEED;

//times
const int CREATE_BYTE_SEND_WAIT;

# endif
