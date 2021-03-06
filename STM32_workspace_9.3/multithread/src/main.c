#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include "leds_control.h"


static char message[5];
static int g_active_player;
static char *direction;
static int state_button;
static int TabSize = 7;

typedef struct{
	int RValue;
	int GValue;
	int BValue;
}RGB;

typedef struct{
	int player;
	char *direction;
	int state_button;
}Message;

const RGB Red={255,0,0};
const RGB Green={0,255,0};
const RGB Blue={0,0,255};
const RGB White={255,255,255};
const RGB Purple={255,0,255};
const RGB Yellow={255,255,0};
const RGB Black={0,0,0};

void *read_input(void *arg){
	Message message_recv;
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
				message_recv.player = g_active_player;
				printf("active player : %d\n", g_active_player);
			}
			else if (message[1] == 50){
				g_active_player = 2;
				message_recv.player = g_active_player;
				printf("active player : %d\n", g_active_player);
			}
			if (message[2] == 108){
				direction = "left";
				message_recv.direction = direction;
				printf("direction : %s\n", direction);
			}
			else if(message[2] == 114){
				direction = "right";
				message_recv.direction = direction;
				printf("direction : %s\n", direction);
			}
			else if(message[2] == 100){
				direction = "down";
				message_recv.direction = direction;
				printf("direction : %s\n", direction);
			}
			else if(message[2] == 117){
				direction = "up";
				message_recv.direction = direction;
				printf("direction : %s\n", direction);
			}
			if(message[3] == 100){
				state_button = 0;
				message_recv.state_button = state_button;
				printf("etat du bouton : down\n");
			}
			else if(message[3] == 117){
				state_button = 1;
				message_recv.state_button = state_button;
				printf("etat du bouton : up\n");
			}
		}
	}
	(void) arg;
	pthread_exit(NULL);
}

void *handle_app(void *arg){
	(void) arg;
	pthread_exit(NULL);
}

void *send_message(void *arg){

	setLedColor(1, 1, 255, 255, 255);
	(void) arg;
	pthread_exit(NULL);
}

void SetLedLine(RGB **TabLine, int TabSize){
	for (int line=0; line<TabSize; line++){
		for(int col = 0; col < TabSize; col++){
			setLedColor(line+1, col+1, TabLine[line][col].RValue, TabLine[line][col].GValue, TabLine[line][col].BValue);
		}
	}
}

void switch_number (int number_to_switch){


}

int main(void){
	openLink();
	pthread_t thread_read;
	pthread_t thread_app;
	pthread_t thread_send;
	printf("Creation thread de lecture\n");
	pthread_create(&thread_read, NULL, read_input, NULL);
	printf("Creation thread d'application\n");
	pthread_create(&thread_app, NULL, handle_app, NULL);
	printf("Creation thread d'envoi\n");
	pthread_create(&thread_send, NULL, send_message, NULL);


	(void)pthread_join (thread_read, NULL);
	(void)pthread_join (thread_app, NULL);
	(void)pthread_join (thread_send, NULL);
	closeLink();
	return 0;
}
