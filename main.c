// Zachary Maniatis & Zachary Power
#include <avr/io.h>
#include <util/delay.h>
#include "main.h"
#include "rover.h"
#include "sensor.h"
#include "motor.h"
#include "qtr_driver.h"

int main() {
    init_QTR_driver();

    DDRD = (1 << PD0 | 1 << PD1 | 1 << PD2 | 1 << PD3);

    unsigned char firstState = getSensorData();
    solveMaze(firstState);
    
    return 0;
}

void solveMaze(unsigned char previousState) {
    unsigned char currentState = getSensorData();

    if(isOnPath(currentState)) {
        driveForward();
    } else if(shouldGoLeft(currentState)) {
        turn(TURN_LEFT);
    } else if(shouldGoRight(currentState)) {
        turn(TURN_RIGHT);
    }

    solveMaze(currentState);
}
