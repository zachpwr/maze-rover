#include "rover.h"
#include "motor.h"

// -- HIGH-LEVEL MOTOR I/O -- //
void drift(int direction) {
    int leftDirection = (direction < 0) ? BREAK : FORWARD; // Dictates left/right turn depending on sign of input value
    int rightDirection = (direction < 0) ? FORWARD : BREAK;

    setLeftMotor(leftDirection);
    setRightMotor(rightDirection);

    _delay_ms(50);

    stop();
    return;
}

void turn(int direction) {
    int leftDirection = (direction > 0) ? FORWARD : BACKWARD; // Dictates left/right turn depending on sign of input value
    int rightDirection = (direction > 0) ? BACKWARD : FORWARD;

    while(!isOnPath()) { // While loop that continues until rover has completed 90degree turn
        setRightMotor(rightDirection);
        setLeftMotor(leftDirection);
        _delay_ms(10);
    }

    stop();
    return;
}

void driveForward() {
    setRightMotor(FORWARD);
    setLeftMotor(FORWARD);
    _delay_ms(10);

    stop();
    return;
}

int stop() {//Makes rover stop moving
    setLeftMotor(BREAK);
    setRightMotor(BREAK);
}

// -- LOW-LEVEL MOTOR I/O -- //
int setLeftMotor(int direction) { // Gives access to the left motor
    static int currentDirection;
    if(currentDirection == direction) return 0;

    LEFT_PORT_OUT &= ~LEFT_MOTOR_MASK;
    LEFT_PORT_OUT |= direction << 6;

    currentDirection = direction;
    return 1;
}

int setRightMotor(int direction) { // Gives access to the right motor
    static int currentDirection;
    if(currentDirection == direction) return 0;

    LEFT_PORT_OUT &= ~RIGHT_MOTOR_MASK;
    LEFT_PORT_OUT |= direction << 2;

    currentDirection = direction;
    return 1;
}
