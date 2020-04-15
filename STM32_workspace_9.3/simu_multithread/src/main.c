#include<stdio.h>
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


static int TabSize = 7;
static int number_value = 0;
static char message[5];
static int max_number = 14;
static pthread_mutex_t mutex_number;


typedef struct{
	int RValue;
	int GValue;
	int BValue;
}RGB;


typedef enum {QUEUE_READ, QUEUE_SEND} QUEUE_ID;

const RGB Red={255,0,0};
const RGB Green={0,255,0};
const RGB Blue={0,0,255};
const RGB White={255,255,255};
const RGB Purple={255,0,255};
const RGB Yellow={255,255,0};
const RGB Black={0,0,0};

static RGB actual_matrice[7][7];
char init_matrice_is_ok = 0;



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
	printf("nb led mis a jour : %d\n", cpt_change_led);
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


void send_message(QUEUE_ID queue, int message, int message_lenght) {
	if (queue == QUEUE_READ) {
		add_element(&p_queue_read, message);
		sem_post(&p_queue_read.semaphore);
	}
	if (queue == QUEUE_SEND) {
		add_element(&p_queue_display, message);
		sem_post(&p_queue_display.semaphore);
	}
}

int receive_message(QUEUE_ID queue, int message, int message_lenght) {
	int return_value;
	if (queue == QUEUE_READ) {
		sem_wait(&p_queue_read.semaphore);
		return_value = pop_element(&p_queue_read);
	}
	if (queue == QUEUE_SEND) {
		sem_wait(&p_queue_display.semaphore);
		return_value = pop_element(&p_queue_display);
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
	//	Queue *p_queue = arg;
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
					send_message(QUEUE_READ, down, 1);
				}
				else if(message[2] == 117){
					send_message(QUEUE_READ, up, 1);
				}
			}
		}
	}
	(void) arg;
	pthread_exit(NULL);
}


void *application(void *arg){
	int instruction = 0;
	int message = 0;
	while(1){
		instruction = receive_message(QUEUE_READ, message, 1);
		if (instruction == down){
			pthread_mutex_lock(&mutex_number);
			number_value -= 1;
			if (number_value < 0){
				number_value = max_number;
			}
			pthread_mutex_unlock(&mutex_number);
			send_message(QUEUE_SEND, number_value, 1);
		}
		else if(instruction == up){
			pthread_mutex_lock(&mutex_number);
			number_value += 1;
			if (number_value > max_number){
				number_value = 0;
			}
			pthread_mutex_unlock(&mutex_number);
			send_message(QUEUE_SEND, number_value, 1);
		}
	}
	(void) arg;
	pthread_exit(NULL);
}

void *show_board(void *arg){
	int number_to_display = 0;
	int message = 0;
	set_number(0);
	while (1){
		number_to_display = receive_message(QUEUE_SEND, message, 1);
		set_number(number_to_display);
	}
	(void) arg;
	pthread_exit(NULL);
}

int main(void){
	openLink();
	pthread_t thread_read;
	pthread_t thread_app;
	pthread_t thread_send;
	init_queue(&p_queue_read);
	init_queue(&p_queue_display);
	sem_init(&semaphore_input, 0, 0);
	sem_init(&semaphore_display, 0, 0);

	printf("Creation thread de lecture\n");
	pthread_create(&thread_read, NULL, read_input, NULL);
	printf("Creation thread d'application\n");
	pthread_create(&thread_app, NULL, application, NULL);
	printf("Creation thread d'envoi\n");
	pthread_create(&thread_send, NULL, show_board, NULL);


	(void)pthread_join(thread_read, NULL);
	(void)pthread_join(thread_app, NULL);
	(void)pthread_join(thread_send, NULL);

	sem_destroy(&semaphore_input);
	sem_destroy(&semaphore_display);
	closeLink();
	return 0;
}
