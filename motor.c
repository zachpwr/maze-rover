// Zachary Maniatis & Zachary Power
#include "motor.h"

void initMotorDriver() {
    MOTOR_PORT_DDR = (1 << PD0 | 1 << PD1 | 1 << PD2 | 1 << PD3);
}

// -- HIGH-LEVEL MOTOR I/O -- //
void turn(int direction) {
    int leftDirection = (direction == TURN_LEFT) ? BACKWARD : FORWARD; // Dictates left/right turn depending on sign of input value
    int rightDirection = (direction == TURN_RIGHT) ? BACKWARD : FORWARD;

    setRightMotor(rightDirection);
    setLeftMotor(leftDirection);
    _delay_ms(MOTOR_DELAY);

    stop();
    return;
}

void driveForward() {//Makes rover drive Forward
    setRightMotor(FORWARD);
    setLeftMotor(FORWARD);
    _delay_ms(MOTOR_DELAY);

    stop();
    return;
}

int stop() {//Makes rover stop moving
    setLeftMotor(BREAK);
    setRightMotor(BREAK);

    _delay_ms(MOTOR_DELAY);
    return 1;
}

// -- LOW-LEVEL MOTOR I/O -- //
int setLeftMotor(int direction) { // Gives access to the left motor
    static int currentDirection;
    if(currentDirection == direction) return 0;

    MOTOR_PORT_OUT &= ~LEFT_MOTOR_MASK;
    MOTOR_PORT_OUT |= direction << 6;

    currentDirection = direction;
    return 1;
}

int setRightMotor(int direction) { // Gives access to the right motor
    static int currentDirection;
    if(currentDirection == direction) return 0;

    MOTOR_PORT_OUT &= ~RIGHT_MOTOR_MASK;
    MOTOR_PORT_OUT |= direction << 2;

    currentDirection = direction;
    return 1;
}
