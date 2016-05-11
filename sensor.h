// Zachary Maniatis & Zachary Power

#define LEFT_SENSOR_MASK 0x03

unsigned char getSensorData();
int isAligned(unsigned char sensorData);
int shouldGoLeft(unsigned char sensorData);
int shouldGoRight(unsigned char sensorData);
int getAlignmentSensorData(unsigned char sensorData);
