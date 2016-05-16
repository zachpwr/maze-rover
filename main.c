/**
 * Functions for driving the rover through a maze
 * Authors: Zachary Maniatis & Zachary Power
 */

#include <avr/io.h>
#include "main.h"
#include "sensor.h"
#include "motor.h"
#include "qtr_driver.h"

int main() {
    // Prepare the motors and sensors upon start-up
    init_QTR_driver();
    initMotorDriver();

    // Start maze-solving loop
    solveMaze();

    return 0;
}

void solveMaze() {
    unsigned char currentSensorData = getSensorData();

    // Check rover alignment and react to turns or drifting
    if(isAligned(currentSensorData)) {
        driveForward();
    } else if(shouldGoLeft(currentSensorData)) {
        turn(TURN_LEFT);
    } else if(shouldGoRight(currentSensorData)) {
        turn(TURN_RIGHT);
    }

    // Jump back to the beginning of the maze-solving loop
    solveMaze();
}

#include "qtr_driver.c"
#include "sensor.c"
#include "motor.c"
