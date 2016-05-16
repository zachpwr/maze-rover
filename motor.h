/**
 * Functions for controlling the rover motors
 * Authors: Zachary Maniatis & Zachary Power
 */

// Define port through which the rover will activate the motors
#define MOTOR_PORT_OUT PORTC
#define MOTOR_PORT_DDR DDRC

// Bit masks to isolate left and right motor bits for setting wheel rotation
#define LEFT_MOTOR_MASK 0x30
#define RIGHT_MOTOR_MASK 0x0C

// Turn direction aliases to make code more readable
#define TURN_RIGHT 1
#define TURN_LEFT -1

// Wheel rotation aliases to make code more readable
#define FORWARD 0b01
#define BACKWARD 0b10
#define BREAK 0b11

// Calibrated timing for driving, turning, and stopping
#define MOTOR_DELAY 1
#define TURN_DELAY 3
#define STOP_DELAY 2

// Function prototypes
void initMotorDriver();
void turn(int direction);
void driveForward();
void stop();
void setLeftMotor(int direction);
void setRightMotor(int direction);
