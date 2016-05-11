// Zachary Maniatis & Zachary Power
#include <avr/io.h>
#include "main.h"
#include "rover.h"
#include "sensor.h"
#include "motor.h"
#include "qtr_driver.h"

int main(){
    init_QTR_driver();
    unsigned char firstState = getSensorData();
    solveMaze(firstState);
    return 0;
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

// -- HIGH-LEVEL MOTOR I/O -- //
void drift(int direction) {
    int leftDirection = (direction < 0) ? BREAK : FORWARD; // Dictates left/right turn depending on sign of input value
    int rightDirection = (direction < 0) ? FORWARD : BREAK;

    setLeftMotor(leftDirection);
    setRightMotor(rightDirection);

    _delay_ms(50);

    stop();
    return;
}

void turn(int direction) {
    int leftDirection = (direction > 0) ? FORWARD : BACKWARD; // Dictates left/right turn depending on sign of input value
    int rightDirection = (direction > 0) ? BACKWARD : FORWARD;

    while(!isOnPath(getSensorData())) { // While loop that continues until rover has completed 90degree turn
        setRightMotor(rightDirection);
        setLeftMotor(leftDirection);
        _delay_ms(10);
    }

    stop();
    return;
}

void driveForward() {
    setRightMotor(FORWARD);
    setLeftMotor(FORWARD);
    _delay_ms(10);

    stop();
    return;
}

int stop() {//Makes rover stop moving
    setLeftMotor(BREAK);
    setRightMotor(BREAK);
    return 0;
}

// -- LOW-LEVEL MOTOR I/O -- //
int setLeftMotor(int direction) { // Gives access to the left motor
    static int currentDirection;
    if(currentDirection == direction) return 0;

    LEFT_PORT_OUT &= ~LEFT_MOTOR_MASK;
    LEFT_PORT_OUT |= direction << 6;

    currentDirection = direction;
    return 1;
}

int setRightMotor(int direction) { // Gives access to the right motor
    static int currentDirection;
    if(currentDirection == direction) return 0;

    LEFT_PORT_OUT &= ~RIGHT_MOTOR_MASK;
    LEFT_PORT_OUT |= direction << 2;

    currentDirection = direction;
    return 1;
}

unsigned char QTR_ARRAY_VALUE; //variable holding current QTR sensor state

//returns the current state of the QTR array
unsigned char get_QTR_value()
{
	return QTR_ARRAY_VALUE;
}

//initializes the QTR interrupt-based driver
void init_QTR_driver()
{
	QTR_ARRAY_VALUE=0x00; //initial value
	DDR_QTR=0x00;   //configure port as input...
	PORT_QTR=0x00;  //in order to deactivate pull-up resistors
	OCR0B = QTR_CHARGE_TIME; //time we turn off the array charge
	OCR0A = QTR_DISCHARGE_TIME; //time we read the array
	TCCR0A |= (1<<WGM01); //configure counter to reset at QTR_DISCHARGE_TIME
	TIMSK0 |= (1 << OCIE0A) | (1 << OCIE0B);  //enable interrupts
	TCCR0B |= ((1<<CS02) | (1<<CS00)); //set counter prescaler to 1024 and start counter
	sei(); //enable global interrupts
	return;
}
void QTR_CHARGE_ARRAY()
{
	PORT_QTR=0xFF; //set array ping to output, then
	DDR_QTR=0xFF; //output 0xFF to QTR pins to charge array
	return;
}
ISR(TIMER0_COMPB_vect)
{
	DDR_QTR = 0x00;  //configure QTR port as input to start discharging
	return;
}
ISR(TIMER0_COMPA_vect)
{
	QTR_ARRAY_VALUE=PIN_QTR; //read current sensor value
	QTR_CHARGE_ARRAY(); //begin chrging array for next read
	return;
}
