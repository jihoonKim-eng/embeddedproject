#include <stdio.h>
#include <unistd.h>
#include "led.h"

int main(void)
{	
	ledLibInit();
	sleep(10);
	
	ledLibRaw(0xFF);
	sleep(10);
	ledLibRaw(0xAA);
	sleep(10);
	ledLibEXT();
}
