all: libMyPeri.a main.elf

main.elf: libMyPeri.a main.c led.h buzzer.h button.h colorLED.h fnd.h temperature.h textlcd.h bitmap.h
	arm-linux-gnueabi-gcc -o main.elf main.c -L. -lMyPeri -lpthread

libMyPeri.a: led.h led.c buzzer.h buzzer.c button.c button.h colorLED.c colorLED.h fnd.c fnd.h temperature.c temperature.h textlcd.c textlcd.h bitmap.c bitmap.h
	arm-linux-gnueabi-gcc -c led.c -o led.o
	arm-linux-gnueabi-gcc -c buzzer.c -o buzzer.o
	arm-linux-gnueabi-gcc -c button.c -o button.o
	arm-linux-gnueabi-gcc -c colorLED.c -o colorLED.o
	arm-linux-gnueabi-gcc -c fnd.c -o fnd.o	
	arm-linux-gnueabi-gcc -c temperature.c -o temperature.o
	arm-linux-gnueabi-gcc -c textlcd.c -o textlcd.o
	arm-linux-gnueabi-gcc -c bitmap.c -o bitmap.o
	arm-linux-gnueabi-ar rc libMyPeri.a led.o buzzer.o button.o colorLED.o fnd.o temperature.o textlcd.o bitmap.o

clean:
	rm -rf *.o *.a *.elf
	
