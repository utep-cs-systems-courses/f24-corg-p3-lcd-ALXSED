COMMON_OBJECTS  = main.o sound.o
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS         = -L/opt/ti/msp430_gcc/include -L../lib

CC              = msp430-elf-gcc
AS              = msp430-elf-as
AR              = msp430-elf-ar

all: main.elf libLcd.a

libLcd.a: font-11x16.o font-5x7.o lcdutils.o lcddraw.o
	$(AR) crs $@ $^

lcddraw.o: lcddraw.c lcddraw.h lcdutils.h
lcdutils.o: lcdutils.c lcdutils.h


sound.o: sound.s
	$(AS) -mmcu=$(CPU) -o $@ $<

install: libLcd.a
	mkdir -p ../h ../lib
	mv $^ ../lib
	cp *.h ../h


main.elf: ${COMMON_OBJECTS} led.o switch.o buzzer.o libLcd.a ./lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: main.elf
	msp430loader.sh main.elf

clean:
	rm -f *.o *.elf *~
	rm -f libLcd.a *.o
