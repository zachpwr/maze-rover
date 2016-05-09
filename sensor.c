#include "qtr_driver.h"
#include "sensor.h"

unsigned char getSensorData() {
    return get_QTR_value();
}

int isLeftTurnAvailable(unsigned char sensorData) {
    return ((sensorData & 0xC0) >> 6) == 3;
}

int isRightTurnAvailable(unsigned char sensorData) {
    return (sensorData & 0x03) == 3;
}

int isOnPath(unsigned char sensorData) {
    return ((sensorData & 0x3C) >> 2) == 0x0F;
}

int isTooFarLeft(unsigned char sensorData) {
    return ((sensorData & 0x0F) << 4 | (sensorData & 0xF0) >> 4) > sensorData;
}

int isTooFarRight(unsigned char sensorData) {
    return ((sensorData & 0x0F) << 4 | (sensorData & 0xF0) >> 4) < sensorData;
}

int isOffOfPath(unsigned char sensorData) {
    return sensorData == 0x00;
}
