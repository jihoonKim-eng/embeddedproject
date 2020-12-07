#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "led.h"

static int fd=0;
static int ledStatus = 0;
int ledLibInit(void)  							//이 라이브러리는 엘이디를 켜기 전에 반드시 한번 불러주어야 한다
{
		fd = open (LED_DRV_NODE, O_RDWR);
		if(fd < 0)
		{
				printf("Device Open ERror!\r\n");
				exit(1);
		}
		ledStatus = 0;
		ledLibRaw(ledStatus);
		return 1;
}
int ledLibOnOff(int ledNumber, int onOff)		//이 함수는 ledNumber에는 0~7을 넣으면, 그에 해당하는 led를 켜거나 끄거나 해준다.
{
	int lamp = 1;
	lamp = lamp << ledNumber;						//00010000 해 당하는 전구비트만 1임.
	ledStatus = (ledStatus &(~lamp));			//해당하는 전구비트만 0으로 바꿈.
	if(onOff)
		ledStatus = ledStatus | lamp;			//해당하는 전구비트만 1로 바꾸고 나머지는 그대로.
	ledLibRaw(ledStatus);
	return 1;
}

int ledLibStatus(void)							//이 함수를 호출하면 현재 led상태가 어떤지 확인해 준다.
{
		return ledStatus;
}
int ledLibEXT(void)
{
	ledLibRaw(0); //전부 끔.
	close(fd);
}
//이 함수를 호출하면 LED를 전부 끄고 driver를 close 한다.
int ledLibRaw(char ledwannabe)
//이 함수를 호출하면 ledStatus에 맞게 8개의 led를 전부 제어한다. 예를 들어 ledLibRaw(0x80); 1개만 켜진다.
{
		if(fd > 0)
		{
			write(fd, &ledwannabe, 1);
		}
		else
		{
			printf("WRONG! you must open device NODE!\r\n");
			exit(2);
		}
		ledStatus = ledwannabe;
		return 1;
}






