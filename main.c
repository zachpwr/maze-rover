#include <avr/io.h>
#include "rover.h"
#include "sensor.h"
#include "motor.h"
#include "qtr_driver.h"

int main(){
    init_QTR_driver();
    solveMaze();
}

void solveMaze(unsigned char previousState) {
    unsigned char currentState = getSensorData();

    if(isLeftTurnAvailable(currentState) == 1) {
        turn(-1);
    } else if(isOnPath(currentState) == 1) {
        driveForward();
    } else if(isRightTurnAvailable(currentState) == 1) {
        turn(1);
    } else if(isTooFarLeft(currentState) == 1) {
        drift(1);
    } else if(isTooFarRight(currentState) == 1) {
        drift(-1);
    } else if(isOffOfPath(currentState) == 1) {
        turn(1);
    }

    solveMaze(currentState);
}
