#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#define MAX_SCALE_STEP		8
#define BUZZER_BASE_SYS_PATH	"/sys/bus/platform/devices/"
#define BUZZER_FILENAME  "peribuzzer"
#define BUZZER_ENABLE_NAME		"enable"
#define BUZZER_FREQUENCY_NAME	"frequency"
char gBuzzerBaseSysDir[128];
static int Enable;
static int Freq;
const int musicScale[MAX_SCALE_STEP] =
{
	262, /*do*/
	294,
	330,
	349,
	392,
	440,
	494,  /*si*/
	523
};

int findBuzzerSysPath()
{
	DIR * dir_info = opendir(BUZZER_BASE_SYS_PATH);
	int ifFound = 0;
	if(dir_info != NULL)
	{
		while (1)
		{	
			struct dirent  *dir_entry;
			dir_entry = readdir (dir_info);
			if(dir_entry == NULL)	break;
			if(strncasecmp(BUZZER_FILENAME, dir_entry->d_name, strlen(BUZZER_FILENAME)) == 0)
			{
				ifFound = 1;
				sprintf(gBuzzerBaseSysDir,"%s%s/",BUZZER_BASE_SYS_PATH,dir_entry->d_name);
			}
		}
	}
	printf("find %s\n",gBuzzerBaseSysDir);

	return ifFound; 
}

int buzzerInit(void)
{
	if( findBuzzerSysPath()==0 )	return 0;

	char path[200];
	sprintf(path,"%s%s",gBuzzerBaseSysDir,BUZZER_ENABLE_NAME);
	Enable=open(path,O_WRONLY);

	sprintf(path,"%s%s",gBuzzerBaseSysDir,BUZZER_FREQUENCY_NAME);
	Freq=open(path,O_WRONLY);

	return 1;
}
void buzzerEnable(int bEnable)
{
	if(bEnable)	write(Enable, &"1", 1);
	else 			write(Enable, &"0", 1);
}

void setFrequency(int frequency) 
{
	dprintf(Freq, "%d", frequency);
}
int buzzerExit(void)
{
	buzzerEnable(0);
	close(Enable);
	close(Freq);
	return 0;
}
int buzzerPlaySong(int scale)
{
	setFrequency(musicScale[scale]);
	buzzerEnable(1);
	return 0;
}
int buzzerStopSong(void)
{
	buzzerEnable(0);
	return 0;
}

