// Zachary Maniatis & Zachary Power
#include "qtr_driver.h"
#include "sensor.h"

unsigned char getSensorData() {
    return get_QTR_value();
}

int isLeftTurnAvailable(unsigned char sensorData) {//Detects if a left turn is available
    return ((sensorData & 0xC0) >> 6) == 3;
}

int isRightTurnAvailable(unsigned char sensorData) {//Detects if a right turn is available
    return (sensorData & 0x03) == 3;
}

int isOnPath(unsigned char sensorData) {//Detects if the rover is on the path
    return ((sensorData & 0x3C) >> 2) == 0x0F;
}

int isTooFarLeft(unsigned char sensorData) {//Detects if the rover is drifting to the left
    return ((sensorData & 0x0F) << 4 | (sensorData & 0xF0) >> 4) > sensorData;
}

int isTooFarRight(unsigned char sensorData) {//Detects if the rover is drifting to the right
    return ((sensorData & 0x0F) << 4 | (sensorData & 0xF0) >> 4) < sensorData;
}

int isOffOfPath(unsigned char sensorData) {//Detects if the rover is on the path
    return sensorData == 0x00;
}
