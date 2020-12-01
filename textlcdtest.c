#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "textlcd.h"




  
void doHelp(void)
{
   printf("usage: textlcdtest <linenum> <'string'>\n");
   printf("       linenum => 1 ~ 2\n");   
   printf("  ex) textlcdtest 2 'test hello'\n");
   
}


int main(int argc , char **argv)
{
   unsigned int linenum = 0;
   int len; 
   
int lineFlag;
int lenFlag;
   
   if (argc < 3 )
   {
      perror(" Args number is less than 2\n");
      doHelp();
      return 1;
   }
   
   
   
   
   linenum = strtol(argv[1],NULL,10);
   printf("linenum :%d\n", linenum);                  // 입력 받은 값 출
   
   
   
   
   
   if ( linenum == 1) // firsst line
   {
      lineFlag =1;
   }
   else if ( linenum == 2) // second line
   {
      lineFlag=2;
   }
   else 
   {
      printf("linenum : %d  wrong .  range (1 ~ 2)\n", linenum);              
      return 1; 
   }
   
   
   
   
   printf("string:%s\n",argv[2]);                            //string 출력
   
   
   len = strlen(argv[2]);                              // 내용을 len에 저장.
   if ( len > COLUMN_NUM)                              //최대 입력 가능 숫자.
   {
      lenFlag=1;
   }
   else
   {
      lenFlag=2;
   }
   
   
   
   
//open


   lcdtextwrite(argv[2], argv[2], lineFlag,lenFlag);

   
//close
   
   return 0;
}
