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
#include <pthread.h>
#include "buzzer.h"
#include "led.h"
#include "button.h"
#include "colorLED.h"
#include "fnd.h"
#include "temperature.h"
#include "textlcd.h"
#include "bitmap.h"
#define MUTEX_ENABLE 0
int pic_num=0;
int key_home_pressed  = 0;
int key_back_pressed  = 0;
int key_search_pressed = 0;  
int sec=100;    //전역변수로 선언
int aa;

int start_once1=0;
int start_once2=0;
int random = 0;

pthread_t tid[2];
pthread_mutex_t lock;

void* dosome(void *arg) //thread1 fnd에 남은시간 표시
{

	 for(sec=5;sec>=0;sec--){
    fndDisp(sec,1);  
    sleep(1);
  }
		aa = 3;  
	  pthread_exit(0);

   }


/*void* dosome2(void *arg) //thread2 txtlcd에 온도표시
{
   
char *name1 = "schoolsong";
char *name2 = "solo";
char *singer1 = "dont know";
char *singer2 = "geny";
char keyboard_1;  


while(1)
{


}

   }*/


int main(void)
{	

	buttonInit();
	buzzerInit();        //buzzer
	ledLibInit();   //led
	pwmLedInit();              //pwmled


	int messageID = msgget(MESSAGE_ID, IPC_CREAT|0666);	//To Receive Message from Library.
	BUTTON_MSG_T rxMsg;

int err,arr;
  
 


while(1)
{
	pwmSetPercent(0,0);
	pwmSetPercent(0,1);
	pwmSetPercent(100,2);
   	show("start_pic.bmp");
	
	/*random open picture*/
	do{	
		random = (rand()%4)+2				// puzzle1 은 정답이므로 랜덤하게 나와야하는건 2~6중 랜덤한 수를 하나 뽑아줌
			
		start_once1 =1;				//위에다 int로 선언해주기, 랜덤하게 스타트하는 부분이 1번만 실행되게 해주는 변수 
	}while(start_once1 == 0);
	
		

     while(1)   //Wait here until key home pressed.
      { 
                msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0,0);
                printf ("ReceivedMessage:%d-%d",rxMsg.keyInput, rxMsg.pressed);
                         if (rxMsg.pressed == 0) continue;                               
                if (rxMsg.keyInput == KEY_HOME ) 
                 break;                                  
      }
do{
switch(random)
{ case 2: 
 	show("puzzle2.bmp");
 	pic_num=2;
	break;	
 
  case 3: 
 	show("puzzle3.bmp");
 	pic_num=3;
	break;	

  case 4: 
 	show("puzzle4.bmp");
 	pic_num=4;
	break;	
 
  case 5: 
 	show("puzzle5.bmp");
 	pic_num=5;
	break;	

  case 6: 
 	show("puzzle6.bmp");
 	pic_num=6;
	break;	

}
	open_once2=1;	
}while(open_once2==0);
   
    		 err = pthread_create(&(tid[1]), NULL, &dosome, NULL); 
  
		/*arr = pthread_create(&(tid[2]), NULL, &dosome2, NULL); */

int timeout = 0;

	while (1)
	{
		
	 
		
		msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0 ,0);
		printf ("ReceivedMessage:%d-%d",rxMsg.keyInput, rxMsg.pressed);
		//rxMsg.pressed == 0 -> Really Pressed.

		 if (rxMsg.pressed == 0) continue;
		switch(rxMsg.keyInput)
		{
			case KEY_HOME: 
				key_home_pressed = 1;   
			break;
			case KEY_BACK: 
				key_back_pressed = 1;  
			break;
			case KEY_SEARCH: 
				key_search_pressed = 1;
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
	

	 
switch(pic_num)
    {
    /*puzzle1번 사진이 떠있는경우-> 게임종료*/
     case 1:                          //puzzle1번 사진이 떠있는경우
          show ("end_pic.bmp");      //게임 종료안내 
								//while 문 빠져나가기(작성해야댐)
	/* if(aa==3)
	 {show("game_over.bmp");} */
     break;

/*puzzle2번 사진이 떠있는경우*/
     case 2:   
	 if(aa==3)
	 {show("game_over.bmp");
		 break;}				
        if(key_home_pressed==1 && key_back_pressed==1)
           { show("puzzle5.bmp");
			
                pic_num=5;
                key_home_pressed = 0; 
                key_back_pressed = 0;
             }
        else if (key_home_pressed==1 && key_search_pressed==1)
           {  show("puzzle4.bmp");
             pic_num=4;
                key_home_pressed = 0;
                key_search_pressed = 0;
            }
        else if (key_back_pressed==1 && key_search_pressed==1)
              { show("puzzle1.bmp");
               pic_num=1;
                 key_back_pressed = 0;
                 key_search_pressed = 0;
                    sleep(2);
                    show ("end_pic.bmp");
                }
			
     break;
 
/*puzzle 3번 이 떠있을때*/
     case 3: 
      if(aa==3)
	 {show("game_over.bmp");
		 break;}	
         if(key_home_pressed==1 && key_back_pressed==1)
            {show("puzzle1.bmp");
                pic_num=1;
                key_home_pressed = 0;
                key_back_pressed = 0;
                    sleep(2);
                    show ("end_pic.bmp");                    
              }
        else if (key_home_pressed==1 && key_search_pressed==1)
           {  show("puzzle5.bmp");
             pic_num=5;
                key_home_pressed = 0;
                key_search_pressed = 0;
             }
        else if (key_back_pressed==1 && key_search_pressed==1)
               {show("puzzle4.bmp");
               pic_num=4;
                key_back_pressed = 0;
                key_search_pressed = 0;
                  }
                
     break;

/*puzzle 4번 이 떠있을때*/
     case 4: 
      if(aa==3)
	 {show("game_over.bmp");
		 break;}	
         if(key_home_pressed==1 && key_back_pressed==1)
            {show("puzzle6.bmp");
                pic_num=6;
              key_home_pressed = 0;
              key_back_pressed = 0; 
              }
        else if (key_home_pressed==1 && key_search_pressed==1)
            { show("puzzle2.bmp");
             pic_num=2;
                key_home_pressed = 0;
                key_search_pressed = 0;
                }
        else if (key_back_pressed==1 && key_search_pressed==1)
             {  show("puzzle3.bmp");
               pic_num=3; 
                key_back_pressed = 0;
                key_search_pressed = 0;       
			}
			
     break;

/*puzzle 5번 이 떠있을때*/
     case 5: 
      if(aa==3)
	 {show("game_over.bmp");
		 break;}	
         if(key_home_pressed==1 && key_back_pressed==1)
          {  show("puzzle2.bmp");
                pic_num=2;
                key_home_pressed = 0;
                key_back_pressed = 0;
            }
        else if (key_home_pressed==1 && key_search_pressed==1)
           {  show("puzzle3.bmp");
             pic_num=3;
             key_home_pressed = 0;
             key_search_pressed = 0; 
                }
        else if (key_back_pressed==1 && key_search_pressed==1)
              { show("puzzle6.bmp");
               pic_num=6;
               key_back_pressed = 0;
               key_search_pressed = 0;
                }
              
     break;

/*puzzle 6번 이 떠있을때*/
     case 6:
      if(aa==3)
	 {show("game_over.bmp");
		 break;}	
         if(key_home_pressed==1 && key_back_pressed==1)
           { show("puzzle4.bmp");
                pic_num=4;
                 key_home_pressed = 0;
                 key_back_pressed = 0;        
            }
        else if (key_home_pressed==1 && key_search_pressed==1)
            { show("puzzle1.bmp");
             pic_num=1;
                key_home_pressed = 0;
                 key_search_pressed = 0;      
                    sleep(2);
                    show ("end_pic.bmp");      
                }
        else if (key_back_pressed==1 && key_search_pressed==1)
             {  show("puzzle5.bmp");
               pic_num=5;
                  key_back_pressed = 0;
                  key_search_pressed = 0;
                }

     break;
     
  }
		/*case 7:
		if(aa==3)
	 {show("game_over.bmp");
	 }
		break;
	}*/
    





if(pic_num==1){
	
	pwmSetPercent(100,0);
	pwmSetPercent(100,1);
	pwmSetPercent(100,2);
	pwmInactiveAll();          //pwmled
		ledLibRaw(0xFF);
	usleep(500000);
	ledLibRaw(0xAA);
	usleep(500000);
	ledLibRaw(0xFF);
	usleep(500000);
	ledLibRaw(0xAA);
	usleep(500000);
	ledLibRaw(0xFF);
	usleep(500000);
	ledLibRaw(0xAA);	
	usleep(500000);	
	ledLibEXT();    //led
        buzzerPlaySong(0);
        usleep(300000);
        buzzerPlaySong(1);
        usleep(300000);        
        buzzerPlaySong(2);
        usleep(300000);
        buzzerPlaySong(3);
        usleep(300000);
        buzzerPlaySong(4);
        usleep(300000);
        buzzerPlaySong(5);
        usleep(300000);
        buzzerPlaySong(6);
        usleep(300000);
        buzzerPlaySong(7);
        usleep(300000);
		 buzzerStopSong();			
        buzzerExit();       //buzzer	

	buttonExit();   //button

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

   writeTextLcd("welcome","",1);
   writeTextLcd("","oo",2);                                               
 

  // fndDisp(11111,1);//

       /* fndOff(); */




}








	}
   
		
		
	

	
	                                          

}
pthread_join (tid[0], NULL); 
/*pthread_join (tid[1], NULL);*/

return 0;
}

