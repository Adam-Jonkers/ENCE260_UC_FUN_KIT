# File:   Makefile
# Authors: Liam Morrison (lmo99), Adam Jonkers (ajo164)
# Date:   19 OCT 2022
# Descr:  Makefile for game

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../utils -I../../fonts -I../../drivers -I../../drivers/avr
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: game.out


# Compile: create object files from C source files.
game.o: game.c ../../drivers/avr/system.h ../../drivers/avr/pio.h ../../drivers/navswitch.h ../../drivers/avr/timer.h ../../utils/pacer.h ../../utils/tinygl.h ../../fonts/font5x5_1.h ../../utils/font.h ../../drivers/display.h ../../drivers/avr/ir_uart.h update.h menu.h
	$(CC) -c $(CFLAGS) $< -o $@

menu.o: menu.c ../../drivers/avr/system.h ../../drivers/avr/pio.h ../../drivers/navswitch.h ../../drivers/avr/timer.h ../../utils/pacer.h ../../utils/tinygl.h ../../fonts/font5x5_1.h ../../utils/font.h ../../drivers/display.h ../../drivers/avr/ir_uart.h
	$(CC) -c $(CFLAGS) $< -o $@

update.o: update.c ../../drivers/avr/system.h ../../drivers/avr/pio.h ../../drivers/navswitch.h ../../drivers/avr/timer.h ../../utils/pacer.h ../../utils/tinygl.h ../../fonts/font5x5_1.h ../../utils/font.h ../../drivers/display.h ../../drivers/avr/ir_uart.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: ../../drivers/avr/timer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: ../../drivers/navswitch.c ../../drivers/avr/system.h ../../drivers/avr/pio.h ../../drivers/navswitch.h ../../drivers/avr/delay.h
	$(CC) -c $(CFLAGS) $< -o $@

pacer.o: ../../utils/pacer.c ../../utils/pacer.h ../../drivers/avr/system.h ../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

tinygl.o: ../../utils/tinygl.c ../../drivers/avr/system.h ../../utils/tinygl.h ../../drivers/display.h ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@

font.o: ../../utils/font.c ../../drivers/avr/system.h ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@

display.o: ../../drivers/display.c ../../drivers/avr/system.h ../../drivers/display.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

ledmat.o: ../../drivers/ledmat.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

led.o: ../../drivers/led.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/led.h
	$(CC) -c $(CFLAGS) $< -o $@

ir_uart.o: ../../drivers/avr/ir_uart.c ../../drivers/avr/ir_uart.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/avr/timer0.h ../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

timer0.o: ../../drivers/avr/timer0.c ../../drivers/avr/bits.h ../../drivers/avr/prescale.h ../../drivers/avr/system.h ../../drivers/avr/timer0.h
	$(CC) -c $(CFLAGS) $< -o $@

prescale.o: ../../drivers/avr/prescale.c ../../drivers/avr/prescale.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

usart1.o: ../../drivers/avr/usart1.c ../../drivers/avr/system.h ../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@



# Link: create ELF output file from object files.
game.out: game.o system.o pio.o timer.o navswitch.o pacer.o tinygl.o font.o display.o ledmat.o led.o ir_uart.o timer0.o prescale.o usart1.o menu.o update.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean: 
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: game.out
	$(OBJCOPY) -O ihex game.out game.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash game.hex; dfu-programmer atmega32u2 start






