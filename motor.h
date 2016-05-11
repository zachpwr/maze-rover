// Zachary Maniatis & Zachary Power
#define F_CPU 1000000UL

#define LEFT_MOTOR_MASK 0x03
#define RIGHT_MOTOR_MASK 0x0C

#define TURN_RIGHT 1
#define TURN_LEFT -1

#define FORWARD 0b10
#define BACKWARD 0b01
#define BREAK 0b11

#define MOTOR_DELAY 10

void turn(int direction);
void driveForward();
int stop();
int setLeftMotor(int direction);
int setRightMotor(int direction);
