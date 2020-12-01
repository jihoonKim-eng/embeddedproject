 #include <fcntl.h>
 #include <unistd.h> 
 #include <linux/input.h>
 #include <stdio.h> 
 #include <stdlib.h> 
 #include <string.h>
 #include <sys/ioctl.h> 
 #include <ctype.h>
 #include <sys/ipc.h>
 #include <sys/types.h>
 #include <sys/stat.h> 
 #include <pthread.h>
 #include <sys/mman.h>
#include <sys/msg.h>
#include "textlcd.h"

 static int fd = 0; 

int lcdtextwrite(char *str1, char *str2, int lineFlag,int lenFlag)
{
    stTextLCD  stlcd; 
    memset(&stlcd,0,sizeof(stTextLCD));
      

   
      if ( lineFlag == 1) // firsst line
   {
      stlcd.cmdData = CMD_DATA_WRITE_LINE_1;

   }
   else if ( lineFlag == 2) // second line
   {
      stlcd.cmdData = CMD_DATA_WRITE_LINE_2;
   }

   printf ("Str1: %s, str2: %s\r\n",str1, str2);
   
      if ( lenFlag==1)                          
   {
      memcpy(stlcd.TextData[lineFlag-1],str1,COLUMN_NUM);
      printf("lenfla=1\n");
   }
   else
   {
      memcpy(stlcd.TextData[lineFlag-1],str2,strlen(str2));
      printf("lenfla=2,strlen:%d\n",strlen(str2));
   }
   printf ("LineFlag:%d\r\n",lineFlag);
   printf ("\t\t%c%c%c%c%c\r\n",stlcd.TextData[0][0], 
   stlcd.TextData[0][1], 
   stlcd.TextData[0][2], 
   stlcd.TextData[0][3], 
   stlcd.TextData[0][4]); 
   
   
      stlcd.cmd = CMD_WRITE_STRING;
   
      fd=open (BUTTON_DRIVER_NAME, O_WRONLY); 
    
         if ( fd < 0 )
      {
      perror("driver (//dev//peritextlcd) open error.\n");
      return 1;
      }
   
   
   
   write(fd,&stlcd,sizeof(stTextLCD));    //FAILED!    
   
   close(fd);
   
}
