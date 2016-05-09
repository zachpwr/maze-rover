#include <avr/io.h>
#include "rover.h"
#include "sensor.h"
#include "motor.h"
#include "qtr_driver.h"

int main(){
    init_QTR_driver();
    solveMaze();
}

int solveMaze(unsigned char previousState) {
    unsigned char currentState = getSensorData();

    if(isLeftTurnAvailable() == 1) {
        turn(-1);
    } else if(isOnPath() == 1) {
        driveForward();
    } else if(isRightTurnAvailable() == 1) {
        turn(1);
    } else if(isTooFarLeft() == 1) {
        drift(1);
    } else if(isTooFarRight() == 1) {
        drift(-1);
    } else if(isOffOfPath() == 1) {
        turn(1);
        turn(1);
    }

    solveMaze(currentState);
}
