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

#define LINE_NUM 2
#define COLUMN_NUM 16
#define LINE_BUFF_NUM (COLUMN_NUM + 4) // for dummy
#define MODE_CMD 0
#define MODE_DATA 1
#define CMD_DISPLAY_MODE 0x10
#define BIT_DISPLAY_MODE_CURSOR_DISP 0x01
#define BIT_DISPLAY_MODE_CURSOR_BLINK 0x02
#define BIT_DISPLAY_MODE_DISP_ENABLE 0x04
#define CMD_CURSOR_MOVE_MODE 0x11
#define CURSOR_MOVE_MODE_ENABLE 0x01
#define CURSOR_MOVE_MODE_RIGHT_DIR 0x02
#define CMD_CURSOR_MOVE_POSITION 0x12
#define CURSOR_MOVE_X_MASK 0x3F
#define CURSOR_MOVE_Y_MASK 0xC0
#define CMD_WRITE_STRING 0x20
#define CMD_DATA_WRITE_BOTH_LINE 0
#define CMD_DATA_WRITE_LINE_1 1
#define CMD_DATA_WRITE_LINE_2 2
#define CMD_TEST_GPIO_HIGH 0x30
#define CMD_TEST_GPIO_LOW 0x31

typedef struct TextLCD_tag
{
unsigned char cmd; //
unsigned char cmdData;
unsigned char reserved[2];
char TextData[LINE_NUM][LINE_BUFF_NUM];
}stTextLCD,*pStTextLCD;


#define TEXTLCD_DRIVER_NAME  "/dev/peritextlcd"

int writeTextLcd(const char * line1, const char * line2, int whatLine)
{
	stTextLCD stlcd;
	int fd;
	int len;
	memset(&stlcd,0,sizeof(stTextLCD));
	stlcd.cmd = CMD_WRITE_STRING;
	
	if ( whatLine == 1)
	{
		stlcd.cmdData = CMD_DATA_WRITE_LINE_1;
		len = strlen(line1);
		if(len > COLUMN_NUM)
		{
			memcpy(stlcd.TextData[0], line1, COLUMN_NUM);
		}
		else
		{
			memcpy(stlcd.TextData[0], line1, len);
		}
	}
	else if ( whatLine == 2)
	{
		stlcd.cmdData = CMD_DATA_WRITE_LINE_2;
		len = strlen(line2);
		if(len > COLUMN_NUM)
		{
			memcpy(stlcd.TextData[1], line2, COLUMN_NUM);
		}
		else
		{
			memcpy(stlcd.TextData[1], line2, len);
		}
	}
	else 
	{
		stlcd.cmdData = CMD_DATA_WRITE_BOTH_LINE;
		len = strlen(line1);
		if(len > COLUMN_NUM)
		{
			memcpy(stlcd.TextData[0], line1, COLUMN_NUM);
		}
		else
		{
			memcpy(stlcd.TextData[0], line1, len);
		}
		
		len = strlen(line1);
		if(len > COLUMN_NUM)
		{
			memcpy(stlcd.TextData[1], line2, COLUMN_NUM);
		}
		else
		{
			memcpy(stlcd.TextData[1], line2, len);
		}
		
	}
	


	
	fd = open(TEXTLCD_DRIVER_NAME,O_RDWR); // open driver
	
	if ( fd < 0 )
	{
		printf("driver (//dev//peritextlcd) open error.\n");
		return 0;
	}
	write(fd,&stlcd,sizeof(stTextLCD));
	close(fd);
	return 1;
}
