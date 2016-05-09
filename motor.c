#include "io_softcore.h"
#include "rover.h"
#include "motor.h"
#include <math.h>

// -- HIGH-LEVEL MOTOR I/O -- //
void drift(int direction) {
    int leftDirection = (direction < 0) ? BREAK : FORWARD; // Dictates left/right turn depending on sign of input value
    int rightDirection = (direction < 0) ? FORWARD : BREAK;

    setLeftMotor(leftDirection);
    setRightMotor(rightDirection);

    int finalTurns = 10;
    int currentTurns = 0;

    int lastState = (direction < 0) ? getRightEncoderState() : getLeftEncoderState();

    while(currentTurns < finalTurns) {
        int currentState = (direction < 0) ? getRightEncoderState() : getLeftEncoderState();

        if(currentState != lastState) {
            currentTurns += 1;
            lastState = currentState;
        }
    }

    stop();
    return;
}

void turn(int direction) {

    int finalTurns = (11 / 2) * 83.333;
    int rightTurns = 0;
    int leftTurns = 0;

    int lastLeftState = getLeftEncoderState();
    int lastRightState = getRightEncoderState();

    int leftDirection = (direction > 0) ? FORWARD : BACKWARD; // Dictates left/right turn depending on sign of input value
    int rightDirection = (direction > 0) ? BACKWARD : FORWARD;

    while(rightTurns < finalTurns || rightTurns < finalTurns) { // While loop that continues until rover has completed 90degree turn
        int currentLeftState = getLeftEncoderState();
        int currentRightState = getRightEncoderState();

        if(currentLeftState != lastLeftState) {
            leftTurns += 1;
            lastLeftState = currentLeftState;
        }

        if(currentRightState != lastRightState) {
            rightTurns += 1;
            lastRightState = currentRightState;
        }

        if(rightTurns < leftTurns) {
            setRightMotor(rightDirection);
            setLeftMotor(BREAK);
        } else if(rightTurns < leftTurns) {
            setRightMotor(BREAK);
            setLeftMotor(leftDirection);
        } else {
            setRightMotor(rightDirection);
            setLeftMotor(leftDirection);
        }
    }

    stop();
    return;
}

void driveForward(float displacement) {
    int leftTurns = 0;
    int rightTurns = 0;

    int lastLeftState = getLeftEncoderState();
    int lastRightState = getRightEncoderState();

    int direction = (displacement > 0) ? FORWARD : BACKWARD;

    displacement = sqrt(displacement * displacement);
    LEDS = displacement;

    while(((leftTurns/83.333) * 2) < displacement || ((rightTurns/83.333) * 2) < displacement) {//Makes both mothors turn until they have reached the desired displacement
        int currentLeftState = getLeftEncoderState();
        int currentRightState = getRightEncoderState();

        if(currentLeftState != lastLeftState) {
            leftTurns += 1;
            lastLeftState = currentLeftState;
        }

        if(currentRightState != lastRightState) {
            rightTurns += 1;
            lastRightState = currentRightState;
        }

        if(leftTurns < rightTurns) {//Statements to prevent drifting to one side
            setLeftMotor(direction);
            setRightMotor(BREAK);
        } else if(rightTurns < leftTurns) {
            setLeftMotor(BREAK);
            setRightMotor(direction);
        } else {
            setLeftMotor(direction);
            setRightMotor(direction);
        }
    }
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

// -- ENCODER I/O -- //
int getLeftEncoderState() { // Gives access to the left encoder
    return LEFT_PORT_IN & LEFT_ENCODER_MASK;
}

int getRightEncoderState() { // Gives access to the right encoder
    return LEFT_PORT_IN & RIGHT_ENCODER_MASK;
}
