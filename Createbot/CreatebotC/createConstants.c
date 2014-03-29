
//motor ports
const int ARM_PORT = 0;

//servo ports
const int LOWER_CLAW = 2;
const int UPPER_CLAW = 0;

//sensor ports
const int ARM_DOWN_SENSOR_PORT = 1;
const int ET_SENSOR_PORT = 2;
const int LIGHT_SENSOR_PORT = 3;

//arm positions in ticks
const int ARM_TOP_POS = 4735;

//claw position constants
const int UPPER_CLAW_OPEN = 425;
const int UPPER_CLAW_OPEN_BOT_GUY = 30;
const int UPPER_CLAW_CLOSED = 755; //was 1930
const int UPPER_CLAW_STRANGLE_BOT_GUY = 1250;
const int LOWER_CLAW_OPEN = 2000;
const int LOWER_CLAW_CLOSED_PIPE = 1100;
const int LOWER_CLAW_STRANGLE_BOT_GUY = 900;
const int LOWER_CLAW_CLOSED_BLOCK = 1300;
//turn speeds
const int TURN_SLOW_SPEED = 20;
const int TURN_MID_SPEED = 150;
const int TURN_FAST_SPEED = 300;

//move speeds
const int MOVE_SLOW_SPEED = 100;
const int MOVE_MID_SPEED = 300;
const int MOVE_FAST_SPEED = 450;

//power levels
const int ARM_POWER = 70;

//camera
const double CAMERA_VIEW_ANGLE = 22.2;
