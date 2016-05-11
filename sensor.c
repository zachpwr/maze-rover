// Zachary Maniatis & Zachary Power
#include "qtr_driver.h"
#include "sensor.h"

unsigned char getSensorData() {
    return get_QTR_value();
}

int isAligned(unsigned char sensorData) {
    return (getAlignmentSensorData(sensorData) == 0b01);
}

int shouldGoLeft(unsigned char sensorData) {
    return (getAlignmentSensorData(sensorData) == 0b11);
}

int shouldGoRight(unsigned char sensorData) {
    return (getAlignmentSensorData(sensorData) == 0b00);
}

int getAlignmentSensorData(unsigned char sensorData) {
    return (sensorData & LEFT_SENSOR_MASK);
}
