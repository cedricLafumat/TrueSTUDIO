#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include "leds_control.h"


static char message[5];
static int g_active_player;
static char *direction;

typedef struct{
	int RValue;
	int GValue;
	int BValue;
}RGB;

const RGB Red={255,0,0};
const RGB Green={0,255,0};
const RGB Blue={0,0,255};
const RGB White={255,255,255};
const RGB Purple={255,0,255};
const RGB Yellow={255,255,0};
const RGB Black={0,0,0};

void *read_input(void *arg){
	while(1){
		if ((readbutton(message, 5)) == LCRC_OK){
			for (int i = 0; i<4; i++){
				if(i == 3){
					printf("%d", message[i]);
				}
				else{
				printf("%d-", message[i]);
				}
			}
			printf("\n");
			if (message[1] == 49){
				g_active_player = 1;
			}
			else if (message[1] == 50){
				g_active_player = 2;
			}
			if (message[2] == 108){
				direction = "left";
			}
			else if(message[2] == 114){
				direction = "right";
			}
			else if(message[2] == 100){
				direction = "low";
			}
			else if(message[2] == 117){
				direction = "high";
			}
		}
	}
	(void) arg;
	pthread_exit(NULL);
}

void *send_message(void *arg){
	setLedColor(1, 1, 255, 255, 255);
	(void) arg;
	pthread_exit(NULL);
}

int main(void){
	openLink();
	pthread_t thread_read;
	pthread_t thread_send;
	printf("Creation thread de lecture\n");
	pthread_create(&thread_read, NULL, read_input, NULL);
	printf("Creation thread d'envoi\n");
	pthread_create(&thread_send, NULL, send_message, NULL);


	(void)pthread_join (thread_read, NULL);
	(void)pthread_join (thread_send, NULL);
	closeLink();
	return 0;
}
