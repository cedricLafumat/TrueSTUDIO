/*
 * game.c
 *
 *  Created on: 15 Apr 2020
 *      Author: cedric
 */
#include<stdio.h>
#include"game.h"
#include"leds_control.h"
#include"fifo.h"
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

/*
 * -----------------------------------------------------------------------------------------------------------------------------------
 *
 *
 * 														GLOBAL VARIABILE
 *
 *
 * -----------------------------------------------------------------------------------------------------------------------------------
 */


static RGB actual_matrice[7][7];
char init_matrice_is_ok = 0;
static int TabSize = 7;
static int number_value = 0;
static char message[5];
static int max_number = 14;

RGB Red={255,0,0};
RGB Green={0,255,0};
RGB Blue={0,0,255};
RGB White={255,255,255};
RGB Purple={255,0,255};
RGB Yellow={255,255,0};
RGB Black={0,0,0};


/*
 * -----------------------------------------------------------------------------------------------------------------------------------
 *
 *
 * 														FUNCTION
 *
 *
 * -----------------------------------------------------------------------------------------------------------------------------------
 */

void SetLedMatrice(RGB **TabLine){
	int cpt_change_led = 0;
	for (int line=0; line<TabSize; line++){
		for(int col = 0; col < TabSize; col++){
			if (init_matrice_is_ok == 0){
				actual_matrice[line][col].RValue =  TabLine[line][col].RValue;
				actual_matrice[line][col].GValue =  TabLine[line][col].GValue;
				actual_matrice[line][col].BValue =  TabLine[line][col].BValue;
				setLedColor(line+1, col+1, TabLine[line][col].RValue, TabLine[line][col].GValue, TabLine[line][col].BValue);
				cpt_change_led ++;
			}
			else{
				if ((TabLine[line][col].RValue != actual_matrice[line][col].RValue) ||
					(TabLine[line][col].GValue != actual_matrice[line][col].GValue) ||
					(TabLine[line][col].BValue != actual_matrice[line][col].BValue)){
					setLedColor(line+1, col+1, TabLine[line][col].RValue, TabLine[line][col].GValue, TabLine[line][col].BValue);
					actual_matrice[line][col].RValue =  TabLine[line][col].RValue;
					actual_matrice[line][col].GValue =  TabLine[line][col].GValue;
					actual_matrice[line][col].BValue =  TabLine[line][col].BValue;
					cpt_change_led ++;
				}
			}
		}
	}
	init_matrice_is_ok = 1;
//	printf("nb led mis a jour : %d\n", cpt_change_led);
}


void set_number(int number){
	if (number==14){
		RGB bckgrd = Black;
		RGB number = White;
		RGB tabline_1[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd};
		RGB tabline_2[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd};
		RGB tabline_3[7]={bckgrd,bckgrd,number,bckgrd,number,bckgrd,number};
		RGB tabline_4[7]={bckgrd,number,number,bckgrd,number,bckgrd,number};
		RGB tabline_5[7]={number,bckgrd,number,bckgrd,number,number,number};
		RGB tabline_6[7]={bckgrd,bckgrd,number,bckgrd,bckgrd,bckgrd,number};
		RGB tabline_7[7]={bckgrd,bckgrd,number,bckgrd,bckgrd,bckgrd,number};
		RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
		SetLedMatrice(matrice);
	}
	if (number==13){
		RGB bckgrd = Black;
		RGB number = White;
		RGB tabline_1[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd};
		RGB tabline_2[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd};
		RGB tabline_3[7]={bckgrd,bckgrd,number,bckgrd,number,number,number};
		RGB tabline_4[7]={bckgrd,number,number,bckgrd,bckgrd,bckgrd,number};
		RGB tabline_5[7]={number,bckgrd,number,bckgrd,number,number,number};
		RGB tabline_6[7]={bckgrd,bckgrd,number,bckgrd,bckgrd,bckgrd,number};
		RGB tabline_7[7]={bckgrd,bckgrd,number,bckgrd,number,number,number};
		RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
		SetLedMatrice(matrice);
	}
	if (number==12){
		RGB bckgrd = Black;
		RGB number = White;
		RGB tabline_1[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd};
		RGB tabline_2[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd};
		RGB tabline_3[7]={bckgrd,bckgrd,number,bckgrd,number,number,number};
		RGB tabline_4[7]={bckgrd,number,number,bckgrd,bckgrd,bckgrd,number};
		RGB tabline_5[7]={number,bckgrd,number,bckgrd,number,number,number};
		RGB tabline_6[7]={bckgrd,bckgrd,number,bckgrd,number,bckgrd,bckgrd};
		RGB tabline_7[7]={bckgrd,bckgrd,number,bckgrd,number,number,number};
		RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
		SetLedMatrice(matrice);
	}
	if (number==11){
		RGB bckgrd = Black;
		RGB number = White;
		RGB tabline_1[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd};
		RGB tabline_2[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd};
		RGB tabline_3[7]={bckgrd,bckgrd,number,bckgrd,bckgrd,bckgrd,number};
		RGB tabline_4[7]={bckgrd,number,number,bckgrd,bckgrd,number,number};
		RGB tabline_5[7]={number,bckgrd,number,bckgrd,number,bckgrd,number};
		RGB tabline_6[7]={bckgrd,bckgrd,number,bckgrd,bckgrd,bckgrd,number};
		RGB tabline_7[7]={bckgrd,bckgrd,number,bckgrd,bckgrd,bckgrd,number};
		RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
		SetLedMatrice(matrice);
	}
	if (number==10){
		RGB bckgrd = Black;
		RGB number = White;
		RGB tabline_1[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd};
		RGB tabline_2[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd};
		RGB tabline_3[7]={bckgrd,bckgrd,number,bckgrd,number,number,number};
		RGB tabline_4[7]={bckgrd,number,number,bckgrd,number,bckgrd,number};
		RGB tabline_5[7]={number,bckgrd,number,bckgrd,number,bckgrd,number};
		RGB tabline_6[7]={bckgrd,bckgrd,number,bckgrd,number,bckgrd,number};
		RGB tabline_7[7]={bckgrd,bckgrd,number,bckgrd,number,number,number};
		RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
		SetLedMatrice(matrice);
	}
	if (number==9){
		RGB bckgrd = Black;
		RGB number = White;
		RGB tabline_1[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
		RGB tabline_2[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
		RGB tabline_3[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
		RGB tabline_4[7]={bckgrd,bckgrd,number,number,number,number,bckgrd};
		RGB tabline_5[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
		RGB tabline_6[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
		RGB tabline_7[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
		RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
		SetLedMatrice(matrice);
	}
	else if (number==8){
		RGB bckgrd = Black;
		RGB number = White;
		RGB tabline_1[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
		RGB tabline_2[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
		RGB tabline_3[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
		RGB tabline_4[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
		RGB tabline_5[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
		RGB tabline_6[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
		RGB tabline_7[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
		RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
		SetLedMatrice(matrice);
	}
	else if (number==7){
		RGB bckgrd = Black;
		RGB number = White;
		RGB tabline_1[7]={bckgrd,number,number,number,number,number,bckgrd};
		RGB tabline_2[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
		RGB tabline_3[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
		RGB tabline_4[7]={bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd};
		RGB tabline_5[7]={bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd,bckgrd};
		RGB tabline_6[7]={bckgrd,bckgrd,number,bckgrd,bckgrd,bckgrd,bckgrd};
		RGB tabline_7[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd};
		RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
		SetLedMatrice(matrice);
	}
	else if (number==6){
		RGB bckgrd = Black;
		RGB number = White;
		RGB tabline_1[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
		RGB tabline_2[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
		RGB tabline_3[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd};
		RGB tabline_4[7]={bckgrd,number,number,number,number,bckgrd,bckgrd};
		RGB tabline_5[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
		RGB tabline_6[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
		RGB tabline_7[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
		RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
		SetLedMatrice(matrice);
	}
	else if (number==5){
		RGB bckgrd = Black;
		RGB number = White;
		RGB tabline_1[7]={bckgrd,number,number,number,number,number,bckgrd};
		RGB tabline_2[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd};
		RGB tabline_3[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd};
		RGB tabline_4[7]={bckgrd,number,number,number,number,bckgrd,bckgrd};
		RGB tabline_5[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
		RGB tabline_6[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
		RGB tabline_7[7]={bckgrd,number,number,number,number,bckgrd,bckgrd};
		RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
		SetLedMatrice(matrice);
	}
	else if (number==4){
		RGB bckgrd = Black;
		RGB number = White;
		RGB tabline_1[7]={bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd};
		RGB tabline_2[7]={bckgrd,bckgrd,bckgrd,number,number,bckgrd,bckgrd};
		RGB tabline_3[7]={bckgrd,bckgrd,number,bckgrd,number,bckgrd,bckgrd};
		RGB tabline_4[7]={bckgrd,number,number,number,number,bckgrd,bckgrd};
		RGB tabline_5[7]={bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd};
		RGB tabline_6[7]={bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd};
		RGB tabline_7[7]={bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd};
		RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
		SetLedMatrice(matrice);
	}
	else if (number==3){
		RGB bckgrd = Black;
		RGB number = White;
		RGB tabline_1[7]={bckgrd,number,number,number,number,bckgrd,bckgrd};
		RGB tabline_2[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
		RGB tabline_3[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
		RGB tabline_4[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
		RGB tabline_5[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
		RGB tabline_6[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
		RGB tabline_7[7]={bckgrd,number,number,number,number,bckgrd,bckgrd};
		RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
		SetLedMatrice(matrice);
	}
	else if (number==2){
		RGB bckgrd = Black;
		RGB number = White;
		RGB tabline_1[7]={bckgrd,number,number,number,number,bckgrd,bckgrd};
		RGB tabline_2[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
		RGB tabline_3[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
		RGB tabline_4[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
		RGB tabline_5[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd};
		RGB tabline_6[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd};
		RGB tabline_7[7]={bckgrd,number,number,number,number,number,bckgrd};
		RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
		SetLedMatrice(matrice);
	}
	else if (number==1){
		RGB bckgrd = Black;
		RGB number = White;
		RGB tabline_1[7]={bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd};
		RGB tabline_2[7]={bckgrd,bckgrd,bckgrd,number,number,bckgrd,bckgrd};
		RGB tabline_3[7]={bckgrd,bckgrd,number,bckgrd,number,bckgrd,bckgrd};
		RGB tabline_4[7]={bckgrd,number,bckgrd,bckgrd,number,bckgrd,bckgrd};
		RGB tabline_5[7]={bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd};
		RGB tabline_6[7]={bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd};
		RGB tabline_7[7]={bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd};
		RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
		SetLedMatrice(matrice);
	}
	else if (number==0){
		RGB bckgrd = Black;
		RGB number = White;
		RGB tabline_1[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
		RGB tabline_2[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
		RGB tabline_3[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
		RGB tabline_4[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
		RGB tabline_5[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
		RGB tabline_6[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
		RGB tabline_7[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
		RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
		SetLedMatrice(matrice);
	}
}


void send_message(QUEUE_ID queue, char *message, int message_lenght) {
	if (queue == QUEUE_READ) {
		add_element(&p_queue_read, message);
		sem_post(&p_queue_read.semaphore);
	}
	if (queue == QUEUE_SEND) {
		add_element(&p_queue_display, message);
		sem_post(&p_queue_display.semaphore);
	}
}

int receive_message(QUEUE_ID queue, char *message, int message_lenght) {
	int return_value;
	if (queue == QUEUE_READ) {
		sem_wait(&p_queue_read.semaphore);
		return_value = pop_element(&p_queue_read, message);
	}
	if (queue == QUEUE_SEND) {
		sem_wait(&p_queue_display.semaphore);
		return_value = pop_element(&p_queue_display, message);
	}
	return return_value;
}

/*
 * -----------------------------------------------------------------------------------------------------------------------------------
 *
 *
 * 														THREAD
 *
 *
 * -----------------------------------------------------------------------------------------------------------------------------------
 */

void *read_input(void *arg){
	char command[10];
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
			if (message[3] == 117){
				if (message[1] == 49){
					// joueur 1
				}
				else if (message[1] == 50){
					//joueur 2
				}
				if (message[2] == 108){
					// left
				}
				else if(message[2] == 114){
					// right
				}
				else if(message[2] == 100){
					command[0] = down;
					send_message(QUEUE_READ, command, 1);
				}
				else if(message[2] == 117){
					command[0] = up;
					send_message(QUEUE_READ, command, 1);
				}
			}
		}
	}
	(void) arg;
	pthread_exit(NULL);
}


void *application(void *arg){
	char message_receive[10];
	char message_send[10];
	while(1){
		receive_message(QUEUE_READ, message_receive, 1);
		printf("%d\n", message_receive[0]);
		if (message_receive[0] == down){
			number_value -= 1;
			if (number_value < 0){
				number_value = max_number;
			}
			message_send[0] = number_value;
			send_message(QUEUE_SEND, message_send, 1);
		}
		else if(message_receive[0] == up){
			number_value += 1;
			if (number_value > max_number){
				number_value = 0;
			}
			message_send[0] = number_value;
			send_message(QUEUE_SEND, message_send, 1);
		}
	}
	(void) arg;
	pthread_exit(NULL);
}

void *show_board(void *arg){
	char message[10];
	set_number(0);
	while (1){
		receive_message(QUEUE_SEND, message, 1);
//		printf("%d\n", message[0]);
		set_number(message[0]);
	}
	(void) arg;
	pthread_exit(NULL);
}


