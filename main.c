#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <linux/input.h>
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl
#include <string.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdint.h>
#include <errno.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#include "buzzer.h"
#include "led.h"
#include "button.h"
#include "colorLED.h"
#include "fnd.h"
#include "temperature.h"
#include "textlcd.h"
#include "bitmap.h"

int main(void)
{	

   show("exam1.bmp");



	int messageID = msgget (MESSAGE_ID, IPC_CREAT|0666);	//To Receive Message from Library.
	BUTTON_MSG_T rxMsg;

	while (1)
	{
		msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0 ,0);
		printf ("ReceivedMessage:%d-%d",rxMsg.keyInput, rxMsg.pressed);
		//rxMsg.pressed == 0 -> Really Pressed.

		
		switch(rxMsg.keyInput)
		{
			case KEY_HOME: 
				printf("Home key):");   
			break;
			case KEY_BACK: 
				printf("Back key):"); 
			break;
			case KEY_SEARCH: 
				printf("Search key):"); 
			break;
			case KEY_MENU: 
				printf("Menu key):"); 
			break;
			case KEY_VOLUMEUP: 
				printf("Volume up key):");  
			break;
			case KEY_VOLUMEDOWN:
				printf("Volume down key):");
			break;
		}

		
		
	}

	ledLibInit();   //led
	sleep(1);
	
	ledLibRaw(0xFF);
	sleep(3);
	ledLibRaw(0xAA);
	sleep(3);
	ledLibEXT();    //led


        buzzerInit();        //buzzer
        buzzerPlaySong(0);
        sleep(1);
        buzzerPlaySong(1);
        sleep(1);        
        buzzerPlaySong(2);
        sleep(1);
        buzzerPlaySong(3);
        sleep(1);
        buzzerPlaySong(4);
        sleep(1);
        buzzerPlaySong(5);
        sleep(1);
        buzzerPlaySong(6);
        sleep(1);
        buzzerPlaySong(7);
        sleep(1);
		 buzzerStopSong();			
        buzzerExit();       //buzzer	

	buttonExit();   //button


    pwmLedInit();              //pwmled
	pwmSetPercent(100,0);
	pwmSetPercent(0,1);
	pwmSetPercent(0,2);
	pwmInactiveAll();          //pwmled

                                                   //temperature
        char *buffer; int file;
		file=spi_init("/dev/spidev1.0"); //dev
		buffer=(char *)spi_read_lm74(file);
		close(file);
		int value = 0; //13비트 Big Endian Signed Int를 16비트 Little Endian Signed Int로 바꾼다
		value = (buffer[1] >> 3); //Last 3bit: Trashes 날려버리는 함수: 남은 5비트만 value에 더해짐
		value += (buffer[0]) << 5; //위에서 5비트 더한거에 상위 8비트 (= 13비트) 를 원하는 값으로 채움
		if ( buffer[0]&0x80 ) //만약 buffer[0]의 최상위 8번째 비트가 1이라면 사실은 음수 = 영하 기온이 디텍팅 된 것
		{ //그럼 value의 32번 비트에서부터 14번 비트까지 1로 채워 줘야 함 (2의 보수, 음수 참고)
		int i=0;
		for (i=31;i > 12; i--)
		value |= (1<<i); //1로 비트를 채움
		}
		//다 바꿈
		double temp = (double)value*0.0625;
		//1비트가 0.0625도
		printf("Current Temp: %lf \n", temp);
	                                     //temperature                                               


char *name1 = "schoolsong";
char *name2 = "solo";
char *singer1 = "dont know";
char *singer2 = "geny";
char keyboard_1; 

   while(1)
{
     
   writeTextLcd("welcome","",1);
   writeTextLcd("","flag game",2);                                               
 

   fndDisp(111,1);
}
        fndOff();

return 0;

}
