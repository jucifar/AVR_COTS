MCU=atmega32
F_CPU=8000000UL
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-std=c99 -Wall -g -Os -mmcu=${MCU} -DF_CPU=${F_CPU} -I. -I../../COTS
TARGET=main
SRCS=*.c

ifdef OS
   RM = del
else
   ifeq ($(shell uname), Linux)
      RM = rm
   endif
endif

all:
	${CC} ${CFLAGS} -o ${TARGET}.bin ${SRCS}
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.bin ${TARGET}.hex
flash:
	avrdude -p ${MCU} -c usbasp -P usb -U flash:w:${TARGET}.hex:i -F

clean:
	$(RM) -f *.bin *.hex

