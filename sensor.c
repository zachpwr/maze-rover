/**
 * Functions for interpreting QTR sensor readings
 * Authors: Zachary Maniatis & Zachary Power
 */

#include "qtr_driver.h"
#include "sensor.h"

unsigned char getSensorData() {
    return ~get_QTR_value();
}

int isAligned(unsigned char sensorData) {
    // Return true if left line boundary is between the left-most sensors
    return (getLeftAlignment(sensorData) == 0b10);
}

int shouldGoLeft(unsigned char sensorData) {
    // Return true if right line boundary is between the left-most sensors
    // or if left turn is available
    return (getLeftAlignment(sensorData) == 0b01) || (getLeftAlignment(sensorData) == 0b11);
}

int shouldGoRight(unsigned char sensorData) {
    // Return true if left line boundary is missing or if right curve is present
    return (getLeftAlignment(sensorData) == 0b00) || (getRightAlignment(sensorData) == 0b11);
}

int getLeftAlignment(unsigned char sensorData) {
    // Return the right-most bits of the sensor data (represent left-most sensors)
    return (sensorData & LEFT_SENSOR_MASK);
}

int getRightAlignment(unsigned char sensorData) {
    // Return the left-most bits of the sensor data (represent right-most sensors)
    return (sensorData & RIGHT_SENSOR_MASK) >> 6;
}
