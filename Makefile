CCARGS = -mmcu=atmega103 -DF_CPU=16000000 -Os

default: test

test: test.c motor.o switch.o
	avr-gcc  $(CCARGS) switch.o motor.o test.c -o test 

motor.o: motor.c motor.h io_softcore.h
	avr-gcc  $(CCARGS) -c motor.c motor.h io_softcore.h 

switch.o: switch.c switch.h io_softcore.h
	avr-gcc $(CCARGS) -c switch.c switch.h io_softcore.h

test.hex: test
	avr-objcopy -O ihex -R .eeprom -R .fuse -R .lock test test.hex

test.mem: test.hex
	srec_cat test.hex -Intel -Byte_Swap 2 -Data_Only \
	-Output_Block_Size 32 -o test.mem -vmem 8

test.bit: test.mem
	/opt/Xilinx/14.6/ISE_DS/ISE/bin/lin64/data2mem       \
	-bm Papilio_AVR8_bd.bmm -bt Papilio_AVR8.bit \
	-bd test.mem -o b test.bit

fpga: test.bit
	papilio-prog -f test.bit

prom: test.bit
	papilio-prog -b /usr/share/papilio/bscan_spi_xc3s500e.bit -f test.bit

clean:
	-rm test.bit test.mem test.hex test *.o	 *.gch
