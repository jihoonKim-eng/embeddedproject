#include <stdio.h>                                                              
#include <stdlib.h>                                                             
#include <sys/msg.h>                                                            
#include <linux/input.h>                                                        
#include <time.h>                                                               
#include "led.h"                                                                
#include "lcd.h"                                                                
#include "fnd.h"                                                                
#include "buzzer.h"                                                             
#include "button2.h"                                                            
#include "bitmap.h"                                                             
                                                                                
                                                                                
                                                                                
int main (void) {
int score = 0 ;
   buzzerInit();                                                        
   buttonInit();         
   ledLibInit();           
   
                                                 
        int messageID = msgget (MESSAGE_ID, IPC_CREAT|0666);    //To Receive Me.
        BUTTON_MSG_T rxMsg;                                                     

   while(1)
{
        show("bh22.bmp");
   writeTextLcd("welcome","",1);
        writeTextLcd("","flag game",2);                                               
        int n=0;                                         
   int requiredFlag=0;

   fndDisp(score,1);
                       
      while(1)   //Wait here until key home pressed.
      { 
                msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0,0);
                printf ("ReceivedMessage:%d-%d",rxMsg.keyInput, rxMsg.pressed);
      if (rxMsg.pressed == 0) continue;
                //rxMsg.pressed == 0 -> Really Pressed.                         
                                                                                                                                       
                srand(time(NULL));                                               
                n=rand()%4;                                                     
                if (rxMsg.keyInput == KEY_HOME )                                        
                  break;
      }              
   switch (n)
   {                  //Whup:01, WHdown:0x, Blup:04, Bldown:08
            case 0:
               show("bh01.bmp");
               requiredFlag = 0x01 | 0x08;
            break;                       
                                case 1: show("bh10.bmp");
               requiredFlag = 0x02 | 0x04;
            break;       
                        case 2: 
                                   show("bh00.bmp"); 
               requiredFlag = 0x02 | 0x08;                      
                                break;
            case 3:
               show("bh11.bmp");
               requiredFlag = 0x01 | 0x04;                       
                                break;            
         }                                          
                                                                               
        int timeout = 0;
   int answerFlag = 0;          
   int howManyKey = 0;                    
        while (1)                                                               
        {                                                                       
                if (msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0 ,IPC_NOWAIT) == -1)
      {
         timeout++;
         usleep(10*1000);   //10ms;
         if (timeout > 500)   //if 2Sec No input 
         {
            printf ("WROING!!!\r\n");
            break;
         }
      continue;
      }
                printf ("ReceivedMessage:%d-%d",rxMsg.keyInput, rxMsg.pressed);
      if (rxMsg.pressed == 0) continue;
               howManyKey ++;
      switch (rxMsg.keyInput)
      {
         case KEY_VOLUMEUP:
            answerFlag |= 0x01;
         break;
         case KEY_VOLUMEDOWN:
            answerFlag |= 0x02;
         break;
         case KEY_SEARCH:
            answerFlag |= 0x04;
         break;
         case KEY_MENU:
            answerFlag |= 0x08;
         break;
      }   //End of switch

      if (howManyKey == 2) 
      {
         if (answerFlag == requiredFlag)
         {
            printf ("GOOD!!!\r\n");
            printf ("0x%08x vs 0x%08x\r\n",requiredFlag, answerFlag);
            writeTextLcd("Perfect","",1);
            writeTextLcd("","Score up",2);
            score++;
               
            fndDisp(score,1);
            

            buzzerOn(0);
            ledOnOff(0, 1);
                 ledOnOff(1, 1);

            sleep(1);
            buzzerOn(2);
            ledOnOff(2, 1);
                 ledOnOff(3, 1);

            sleep(1);
                                buzzerOn(4);
                 ledOnOff(4, 1);
                 ledOnOff(5, 1);

            sleep(1);
            buzzerOn(7);
                 ledOnOff(6, 1);
                 ledOnOff(7, 1);

            sleep(1);   
            buzzerEnable(0);
            ledOnOff(1,0);
            ledOnOff(0,0);
            ledOnOff(2,0);
            ledOnOff(3,0);
            ledOnOff(4,0);
            ledOnOff(5,0);
            ledOnOff(6,0);
            ledOnOff(7,0);



               
   }
         else
         {
            printf ("WRONG!!!\r\n");
            printf ("0x%08x vs 0x%08x\r\n",requiredFlag, answerFlag);
            writeTextLcd("Fail","",1);
            score--;
            fndDisp(score,1);
            buzzerOn(2);
            ledOnOff(0,1);
            ledOnOff(1,1);
                                ledOnOff(2,1);
                                ledOnOff(3,1);
                                ledOnOff(4,1);
                                ledOnOff(5,1);
                                ledOnOff(6,1);
                                ledOnOff(7,1);
            sleep(1);
            ledOnOff(0,0);
            ledOnOff(1,0);
                                ledOnOff(2,0);
                                ledOnOff(3,0);
                                ledOnOff(4,0);
                                ledOnOff(5,0);
                                ledOnOff(6,0);
                                ledOnOff(7,0);
            sleep(1);
         
            buzzerEnable(0);   
         }
         break;   //Exit While.
      }   //End Of If
}                                                                                                              
sleep(1);             
 }
      ledLibExit();
return 1;                                     
                                   
} 
