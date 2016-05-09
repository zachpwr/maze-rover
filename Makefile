CCARGS = -g -Wall -mmcu=atmega328 -01

default: main

main: main.c motor.o sensor.o qtr_driver.o
	avr-gcc  $(CCARGS) switch.o motor.o test.c -o test

motor.o: motor.c motor.h
	avr-gcc  $(CCARGS) -c motor.c motor.h

sensor.o: sensor.c sensor.h qtr_driver.h
	avr-gcc $(CCARGS) -c switch.c switch.h qtr_driver.h

main.hex: main
	avr-objcopy -O ihex -R .eeprom -R .fuse -R .lock main main.hex

main.mem: main.hex
	srec_cat main.hex -Intel -Byte_Swap 2 -Data_Only \
	-Output_Block_Size 32 -o main.mem -vmem 8

main.bit: main.mem
	/opt/Xilinx/14.6/ISE_DS/ISE/bin/lin64/data2mem       \
	-bm Papilio_AVR8_bd.bmm -bt Papilio_AVR8.bit \
	-bd main.mem -o b main.bit

fpga: main.bit
	papilio-prog -f main.bit

prom: test.bit
	papilio-prog -b /usr/share/papilio/bscan_spi_xc3s500e.bit -f main.bit

clean:
	-rm main.bit main.mem main.hex main *.o	 *.gch
