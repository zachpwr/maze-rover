/**
 * Functions for interpreting QTR sensor readings
 * Authors: Zachary Maniatis & Zachary Power
 */

// Bit masks to isolate the left and right-most sensor bits
#define LEFT_SENSOR_MASK 0x03
#define RIGHT_SENSOR_MASK 0xC0

// Function prototypes
unsigned char getSensorData();
int isAligned(unsigned char sensorData);
int shouldGoLeft(unsigned char sensorData);
int shouldGoRight(unsigned char sensorData);
int getLeftAlignment(unsigned char sensorData);
int getRightAlignment(unsigned char sensorData);

#include "sensor.c"
