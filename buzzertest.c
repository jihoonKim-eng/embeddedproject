#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <linux/input.h>
#include <unistd.h>
#include "buzzer.h"



int main(void)
{
	
        buzzerInit();
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
        buzzerExit();

	return 1;
}
