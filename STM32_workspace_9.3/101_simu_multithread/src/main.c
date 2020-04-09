#include<stdio.h>
#include"leds_control.h"
#include"fifo.h"
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

static pthread_mutex_t mutex_number;
static sem_t semaphore_input;
static sem_t semaphore_display;

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


void set_number(int TabSize){
	for(int compteur=9 ; compteur>=0; compteur--){
		if (compteur==9){
			RGB bckgrd = Black;
			RGB number = Red;
			RGB tabline_1[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
			RGB tabline_2[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_3[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_4[7]={bckgrd,bckgrd,number,number,number,number,bckgrd};
			RGB tabline_5[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_6[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_7[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
			RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			SetLedLine(matrice,TabSize);
		}
		if (compteur==8){
			RGB bckgrd = Black;
			RGB number = White;
			RGB tabline_1[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
			RGB tabline_2[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_3[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_4[7]={bckgrd,bckgrd,number,number,number,number,bckgrd};
			RGB tabline_5[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_6[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_7[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
			RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			SetLedLine(matrice,TabSize);
		}
		if (compteur==7){
			RGB bckgrd = Black;
			RGB number = Green;
			RGB tabline_1[7]={bckgrd,number,number,number,number,number,bckgrd};
			RGB tabline_2[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_3[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_4[7]={bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd};
			RGB tabline_5[7]={bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd,bckgrd};
			RGB tabline_6[7]={bckgrd,bckgrd,number,bckgrd,bckgrd,bckgrd,bckgrd};
			RGB tabline_7[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd};
			RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			SetLedLine(matrice,TabSize);
		}
		if (compteur==6){
			RGB bckgrd = Black;
			RGB number = Blue;
			RGB tabline_1[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
			RGB tabline_2[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_3[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd};
			RGB tabline_4[7]={bckgrd,number,number,number,number,bckgrd,bckgrd};
			RGB tabline_5[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_6[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_7[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
			RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			SetLedLine(matrice,TabSize);
		}
		if (compteur==5){
			RGB bckgrd = Black;
			RGB number = Yellow;
			RGB tabline_1[7]={bckgrd,number,number,number,number,number,bckgrd};
			RGB tabline_2[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd};
			RGB tabline_3[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd};
			RGB tabline_4[7]={bckgrd,number,number,number,number,bckgrd,bckgrd};
			RGB tabline_5[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_6[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_7[7]={bckgrd,number,number,number,number,bckgrd,bckgrd};
			RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			SetLedLine(matrice,TabSize);
		}
		if (compteur==4){
			RGB bckgrd = Black;
			RGB number = Purple;
			RGB tabline_1[7]={bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd};
			RGB tabline_2[7]={bckgrd,bckgrd,bckgrd,number,number,bckgrd,bckgrd};
			RGB tabline_3[7]={bckgrd,bckgrd,number,bckgrd,number,bckgrd,bckgrd};
			RGB tabline_4[7]={bckgrd,number,number,number,number,bckgrd,bckgrd};
			RGB tabline_5[7]={bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd};
			RGB tabline_6[7]={bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd};
			RGB tabline_7[7]={bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd};
			RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			SetLedLine(matrice,TabSize);
		}
		if (compteur==3){
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
			SetLedLine(matrice,TabSize);
		}
		if (compteur==2){
			RGB bckgrd = Black;
			RGB number = Green;
			RGB tabline_1[7]={bckgrd,number,number,number,number,bckgrd,bckgrd};
			RGB tabline_2[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_3[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_4[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
			RGB tabline_5[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd};
			RGB tabline_6[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd};
			RGB tabline_7[7]={bckgrd,number,number,number,number,number,bckgrd};
			RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			SetLedLine(matrice,TabSize);
		}
		if (compteur==1){
			RGB bckgrd = Black;
			RGB number = Blue;
			RGB tabline_1[7]={bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd};
			RGB tabline_2[7]={bckgrd,bckgrd,bckgrd,number,number,bckgrd,bckgrd};
			RGB tabline_3[7]={bckgrd,bckgrd,number,bckgrd,number,bckgrd,bckgrd};
			RGB tabline_4[7]={bckgrd,number,bckgrd,bckgrd,number,bckgrd,bckgrd};
			RGB tabline_5[7]={bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd};
			RGB tabline_6[7]={bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd};
			RGB tabline_7[7]={bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd};
			RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			SetLedLine(matrice,TabSize);
		}
		if (compteur==0){
			RGB bckgrd = Black;
			RGB number = Red;
			RGB tabline_1[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
			RGB tabline_2[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_3[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_4[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_5[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_6[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_7[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
			RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			SetLedLine(matrice,TabSize);
		}
		sleep(3);
	}
}



void *read_input(void *queue){
	char message[5];
	if ((readbutton(message, 5)) == LCRC_OK){
		for (int i = 0; i < 4; i++){
			if (message[1] == 49){
				// joueur 1
			}
			else if (message[1] == 50){
				// joueur 2
			}
			if (message[2] == 100){
				// left
			}
			else if (message[2] == 114){
				// right
			}
			else if (message[2] == 100){
				add_element(queue, 0);
				sem_post(&semaphore_input);

			}
			else if (message[2] == 117){
				add_element(queue, 1);
				sem_post(&semaphore_input);
			}
			if (message[3] == 100){
				// bouton appuyer
			}
			if (message[3] == 117){
				// bouton relacher
			}

		}
	}
	pthread_exit(NULL);
}

void *change_number_app(void *queue){
	sem_wait(&semaphore_input);
	int instruction;
	instruction = pop_element(queue);
	if (instruction == 0){
		set_number();
	}
	else if(instruction == 1){
		set_number();
	}
	sem_post(&semaphore_display);
	pthread_exit(NULL);
}

void *send_message(void *arg){
	sem_wait(&semaphore_display);

	pthread_exit(NULL);
}

int main(void){

	pthread_t thread_read, thread_app, thread_send;
	Queue queue;
	init_queue(&queue);
	sem_init(&semaphore_input, 0, 0);
	sem_init(&semaphore_display, 0, 0);

	pthread_create(&thread_read, NULL, read_input, &queue);
	pthread_create(&thread_app, NULL, change_number_app, NULL);
	pthread_create(&thread_send, NULL, send_message, NULL);

	(void)pthread_join(thread_read, NULL);
	(void)pthread_join(thread_app, NULL);
	(void)pthread_join(thread_send, NULL);

	sem_destroy(&semaphore_input);
	sem_destroy(&semaphore_display);

	return 0;
}
