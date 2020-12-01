#ifndef __FND_DRV_H__ 
#define __FND_DRV_H__


#define MAX_FND_NUM 6 
#define FND_DATA_BUFF_LEN (MAX_FND_NUM + 2)

#define FND_DRIVER_NAME "/dev/perifnd"
#define MODE_STATIC_DIS      0
#define MODE_TIME_DIS      1
#define MODE_COUNT_DIS      2
#define FND_DRIVER_NAME      "/dev/perifnd"
#define ONE_SEG_DISPLAY_TIME_USEC   1000

typedef struct FNDWriteDataForm_tag 
{ 
	char DataNumeric[FND_DATA_BUFF_LEN]; 
	char DataDot[FND_DATA_BUFF_LEN]; 
	char DataValid[FND_DATA_BUFF_LEN]; 
	}stFndWriteForm,*pStFndWriteForm;

int fndDisp(int num , int dotflag);
int fndOff();
#endif
