//program to demonstrate use of QTR driver
#define F_CPU 8000000UL

#include <avr/io.h>
#include "qtr_driver.h"

int main()
{
	//We'll output QTR values continuously to PORTB
	DDRB=0xFF;
	//iMust call the driver initialization
	init_QTR_driver();

	//Forever output QTR value on PORTB
	while(1)
		PORTB=get_QTR_value();
}
	
