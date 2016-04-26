 
#define F_CPU 8000000UL

#include <avr/io.h>
#include "io_softcore.h"
#include <util/delay.h>

#define DELAY_UNIT 1024/8 //matches the delays to the QTR driver 

int main()
{
 unsigned int i; //a counter
 DDRD=0xFF;      //config LEDS port
 while(1)
 {
   PORTF=0xFF;  //set QTR port value required for charging array
   DDRF=0xFF;   //configure port to outputs to charge it
   _delay_us(DELAY_UNIT); //wait until done charging
   DDRF=0x00;   //configure QTR port to sense
   for( i=0; i<PINC; i++ )  //wait for number of delays specified on SWITCHES
 _    delay_us(DELAY_UNIT);
   PORTD=PINF;              //set LEDS to value sensed on QTR
 }
 return 0;
}