/**
 * Functions for controlling the rover motors
 * Authors: Zachary Maniatis & Zachary Power
 */

#include "motor.h"

void initMotorDriver() {
    // Set PC2-PC5 as outputs
    MOTOR_PORT_DDR = (1 << PC2 | 1 << PC3 | 1 << PC4 | 1 << PC5);
}

// HIGH-LEVEL MOTOR I/O
void turn(int direction) {
    // Determine the wheel rotation direction based on the overall turn direction
    int leftDirection = (direction == TURN_LEFT) ? BACKWARD : FORWARD;
    int rightDirection = (direction == TURN_RIGHT) ? BACKWARD : FORWARD;

    setRightMotor(rightDirection);
    setLeftMotor(leftDirection);

    _delay_ms(TURN_DELAY);

    stop();
    return;
}

void driveForward() {
    setRightMotor(FORWARD);
    setLeftMotor(FORWARD);

    _delay_ms(MOTOR_DELAY);

    stop();
    return;
}

void stop() {
    setLeftMotor(BREAK);
    setRightMotor(BREAK);

    _delay_ms(STOP_DELAY);

    return;
}

// LOW-LEVEL MOTOR I/O
void setLeftMotor(int direction) {
    // Compare the current direction to the new direction, exit if equal
    static int currentDirection;
    if(currentDirection == direction) return;

    // Clear the left motor bits and set them to the new direction
    MOTOR_PORT_OUT &= ~LEFT_MOTOR_MASK;
    MOTOR_PORT_OUT |= direction << 4;

    // Store the new direction statically for future setLeftMotor(...) calls
    currentDirection = direction;
    return;
}

void setRightMotor(int direction) {
    // Compare the current direction to the new direction, exit if equal
    static int currentDirection;
    if(currentDirection == direction) return;

    // Clear the right motor bits and set them to the new direction
    MOTOR_PORT_OUT &= ~RIGHT_MOTOR_MASK;
    MOTOR_PORT_OUT |= direction << 2;

    // Store the new direction statically for future setRightMotor(...) calls
    currentDirection = direction;
    return;
}
