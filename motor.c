// Zachary Maniatis & Zachary Power
#include "rover.h"
#include "motor.h"

// -- HIGH-LEVEL MOTOR I/O -- //
void turn(int direction) {
    int leftDirection = (direction == LEFT_TURN) ? BACKWARD : FORWARD; // Dictates left/right turn depending on sign of input value
    int rightDirection = (direction == RIGHT_TURN) ? BACKWARD : FORWARD;

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
