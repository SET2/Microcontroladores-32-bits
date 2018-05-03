# 
CC=avr-gcc
CFLAGS= -g -Os -mmcu=atmega328p
SRCS= main.c\
		lcd.c\


LDFLAGS= -Wl,-Map=main.map
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump

all: main.hex main.elf   

main.elf: main.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

main.o: main.c 
	$(CC) $(CFLAGS) -c $< -o $@ 

main.lst: main.elf
	$(OBJDUMP) -d $< > $@

main.hex: main.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

program: main.hex
	avrdude -p atmega328p -c arduino -P COM14 -b 115200 -U flash:w:main.hex:i

clean:
	rm -rf *.o *.elf 
	rm -rf *.lst *.map 
