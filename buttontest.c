#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <linux/input.h>
#include "button.h"
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl


int main (void)
{
	
	if (buttonInit() == 0)
	{
		printf ("Button init Failed!\r\n");
		return 0;
	}
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

	
	buttonExit();
	return 1;
}

