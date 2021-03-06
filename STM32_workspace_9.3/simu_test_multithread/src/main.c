#include<stdio.h>
#include"leds_control.h"
#include"fifo.h"
#include"game.h"
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


static pthread_mutex_t mutex_number;
static sem_t semaphore_input;
static sem_t semaphore_display;
static int number_value = 0;
static char message[5];
static Queue p_queue_read;
static Queue p_queue_display;

/*sem_t sem_button;
sem_t sem_display;
queue *queue_push_app;
queue *queue_app_display;*/



const RGB Red={255,0,0};
const RGB Green={0,255,0};
const RGB Blue={0,0,255};
const RGB White={255,255,255};
const RGB Purple={255,0,255};
const RGB Yellow={255,255,0};
const RGB Black={0,0,0};

static Matrix matrice;
static Matrix actual_matrice;


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
	for (int line=0; line<TabSize; line++){
		for(int col = 0; col < TabSize; col++){
			setLedColor(line+1, col+1, TabLine[line][col].RValue, TabLine[line][col].GValue, TabLine[line][col].BValue);
		}
	}
}

void init_matrix(void) {
	for (int row = 0; row < TabSize; row++) {
		for (int col = 0; col < TabSize; col++) {
			matrice.board[row][col].RValue = Black.RValue;
			matrice.board[row][col].GValue = Black.GValue;
			matrice.board[row][col].BValue = Black.BValue;
			actual_matrice.board[row][col].RValue = Black.RValue;
			actual_matrice.board[row][col].GValue = Black.GValue;
			actual_matrice.board[row][col].BValue = Black.BValue;
		}
	}
	matrice.init = INIT_OK;
	actual_matrice.init = INIT_OK;
}

void set_number(int nbr) {
	RGB nbr_color = PLAYER_COLOR;
	RGB bckgrnd_color = BACKGROUND;
	for (int row = 0; row < TabSize; row++) {
		for (int col = 0; col < TabSize; col++) {
			if (nbr == 1) { /*Ensemble de conditions pour afficher le chiffre 1*/
				if ((col == 4) || (row == 3 && col == 1)
						|| (row == 2 && col == 2) || (row == 1 && col == 3)) {
					matrice.board[row][col] = nbr_color;
				} else
					matrice.board[row][col] = bckgrnd_color;
			}
			if (nbr == 2) { /*Ensemble de conditions pour afficher le chiffre 2*/
				if ((row == 0 && col == 2) || (row == 0 && col == 3)
						|| (row == 0 && col == 4) || (row == 1 && col == 1)
						|| (row == 1 && col == 5) || (row == 2 && col == 5)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 4 && col == 1)
						|| (row == 5 && col == 1) || (row == 6 && col == 2)
						|| (row == 5 && col == 5) || (row == 6 && col == 3)
						|| (row == 6 && col == 4)) {
					matrice.board[row][col] = nbr_color;
				} else
					matrice.board[row][col] = bckgrnd_color;
			}
			if (nbr == 3) { /*Ensemble de conditions pour afficher le chiffre 3*/
				if ((row == 0 && col == 2) || (row == 0 && col == 3)
						|| (row == 0 && col == 4) || (row == 1 && col == 1)
						|| (row == 1 && col == 5) || (row == 2 && col == 5)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 4 && col == 5)
						|| (row == 5 && col == 5) || (row == 6 && col == 2)
						|| (row == 6 && col == 3) || (row == 6 && col == 4)
						|| (row == 5 && col == 1)) {
					matrice.board[row][col] = nbr_color;
				} else
					matrice.board[row][col] = bckgrnd_color;
			}
			if (nbr == 4) { /*Ensemble de conditions pour afficher le chiffre 4*/
				if ((row == 0 && col == 4) || (row == 1 && col == 3)
						|| (row == 1 && col == 4) || (row == 2 && col == 2)
						|| (row == 2 && col == 4) || (row == 3 && col == 1)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 3 && col == 5)
						|| (row == 4 && col == 4) || (row == 5 && col == 4)
						|| (row == 6 && col == 4)) {
					matrice.board[row][col] = nbr_color;
				} else
					matrice.board[row][col] = bckgrnd_color;
			}
			if (nbr == 5) { /*Ensemble de conditions pour afficher le chiffre 5*/
				if ((row == 0 && col == 1) || (row == 0 && col == 2)
						|| (row == 0 && col == 3) || (row == 0 && col == 4)
						|| (row == 0 && col == 5) || (row == 1 && col == 1)
						|| (row == 2 && col == 1) || (row == 3 && col == 1)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 4 && col == 5)
						|| (row == 5 && col == 5) || (row == 6 && col == 1)
						|| (row == 6 && col == 2) || (row == 6 && col == 3)
						|| (row == 6 && col == 4)) {
					matrice.board[row][col] = nbr_color;
				} else
					matrice.board[row][col] = bckgrnd_color;
			}
			if (nbr == 6) { /*Ensemble de conditions pour afficher le chiffre 6*/
				if ((row == 0 && col == 2) || (row == 0 && col == 3)
						|| (row == 0 && col == 4) || (row == 1 && col == 1)
						|| (row == 2 && col == 1) || (row == 3 && col == 1)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 4 && col == 1)
						|| (row == 4 && col == 5) || (row == 5 && col == 1)
						|| (row == 5 && col == 5) || (row == 6 && col == 2)
						|| (row == 6 && col == 3) || (row == 6 && col == 4)
						|| (row == 1 && col == 5)) {
					matrice.board[row][col] = nbr_color;
				} else
					matrice.board[row][col] = bckgrnd_color;
			}
			if (nbr == 7) { /*Ensemble de conditions pour afficher le chiffre 7*/
				if ((row == 0 && col == 1) || (row == 0 && col == 2)
						|| (row == 0 && col == 3) || (row == 0 && col == 4)
						|| (row == 0 && col == 5) || (row == 1 && col == 5)
						|| (row == 2 && col == 5) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 3 && col == 5)
						|| (row == 4 && col == 5) || (row == 5 && col == 5)
						|| (row == 6 && col == 5)) {
					matrice.board[row][col] = nbr_color;
				} else
					matrice.board[row][col] = bckgrnd_color;
			}
			if (nbr == 8) { /*Ensemble de conditions pour afficher le chiffre 8*/
				if ((row == 0 && col == 2) || (row == 0 && col == 3)
						|| (row == 0 && col == 4) || (row == 1 && col == 1)
						|| (row == 2 && col == 1) || (row == 2 && col == 5)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 4 && col == 1)
						|| (row == 4 && col == 5) || (row == 5 && col == 1)
						|| (row == 5 && col == 5) || (row == 6 && col == 2)
						|| (row == 6 && col == 3) || (row == 6 && col == 4)
						|| (row == 1 && col == 5)) {
					matrice.board[row][col] = nbr_color;
				} else
					matrice.board[row][col] = bckgrnd_color;
			}
			if (nbr == 9) { /*Ensemble de conditions pour afficher le chiffre 9*/
				if ((row == 0 && col == 2) || (row == 0 && col == 3)
						|| (row == 0 && col == 4) || (row == 1 && col == 1)
						|| (row == 2 && col == 1) || (row == 2 && col == 5)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 3 && col == 5)
						|| (row == 4 && col == 5) || (row == 5 && col == 1)
						|| (row == 5 && col == 5) || (row == 6 && col == 2)
						|| (row == 6 && col == 3) || (row == 6 && col == 4)
						|| (row == 1 && col == 5)) {
					matrice.board[row][col] = nbr_color;
				} else
					matrice.board[row][col] = bckgrnd_color;
			}
			if (nbr == 0) { /*Ensemble de conditions pour afficher le chiffre 0*/
				if ((row == 0 && col == 2) || (row == 0 && col == 3)
						|| (row == 0 && col == 4) || (row == 1 && col == 1)
						|| (row == 2 && col == 1) || (row == 2 && col == 5)
						|| (row == 3 && col == 5) || (row == 4 && col == 1)
						|| (row == 4 && col == 5) || (row == 5 && col == 1)
						|| (row == 5 && col == 5) || (row == 6 && col == 2)
						|| (row == 6 && col == 3) || (row == 6 && col == 4)
						|| (row == 1 && col == 5) || (row == 3 && col == 1)) {
					matrice.board[row][col] = nbr_color;
				} else
					matrice.board[row][col] = bckgrnd_color;
			}
		}
	}
}


void send_message(Queue *queue, char *message, int message_lenght) {
	add_element(queue, message);
	sem_post(&queue->semaphore);
}

int receive_message(Queue *queue, char *message, int message_lenght) {
	sem_wait(&queue->semaphore);
	int return_value = pop_element(queue, message);
	return return_value;
}

Queue *queue_init(void) {
	Queue *list = malloc(sizeof(*list));
	list->first = NULL;
	list->last = NULL;
	return list;
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
					add_element(&p_queue_read, down);
					sem_post(&semaphore_input);
				}
				else if(message[2] == 117){
					add_element(&p_queue_read, up);
					sem_post(&semaphore_input);
				}
			}
		}
	}
	(void) arg;
	pthread_exit(NULL);
}


void *change_number_app(void *arg){
	//	Queue *p_queue_read = arg;
	//	Queue *p_queue_send = arg2;
	int instruction;
//	int number_value = begin_number;
	while(1){
		sem_wait(&semaphore_input);
		instruction = pop_element(&p_queue_read);
		if (instruction == down){
			pthread_mutex_lock(&mutex_number);
			number_value -= 1;
			if (number_value < 0){
				number_value = 9;
			}
			add_element(&p_queue_display, number_value);
			pthread_mutex_unlock(&mutex_number);
			sem_post(&semaphore_display);
		}
		else if(instruction == up){
			pthread_mutex_lock(&mutex_number);
			number_value += 1;
			if (number_value > 9){
				number_value = 0;
			}
			add_element(&p_queue_display, number_value);
			pthread_mutex_unlock(&mutex_number);
			sem_post(&semaphore_display);
		}
	}
	(void) arg;
	pthread_exit(NULL);
}

void *send_message(void *arg){
	/*Queue *p_queue = arg;
	int number_to_display = 0;
	set_number(0);
	while (1){
		sem_wait(&semaphore_display);
		number_to_display = pop_element(&p_queue_display);
		set_number(number_to_display);
	}*/

	while (1) {
		printf("lancement thread affichage\n");
		int user_input = 0;
		if (receive_message(p_queue_display, (char *) &user_input, MSG_LENGHT)
				== 0) {
//		sem_wait(&sem_display);
//		pop_element(queue_app_display, &user_input);
			set_number(user_input);
			printf("affichage numéro %d\n", user_input);
			for (int row = 0; row < TabSize; row++) {
				for (int col = 0; col < TabSize; col++) {
					if ((matrice.board[row][col].RValue
							== actual_matrice.board[row][col].RValue)
							&& (matrice.board[row][col].GValue
									== actual_matrice.board[row][col].GValue)
							&& (matrice.board[row][col].BValue
									== actual_matrice.board[row][col].BValue)) {
					} else {
						setLedColor(row + 1, col + 1,
								matrice.board[row][col].RValue,
								matrice.board[row][col].GValue,
								matrice.board[row][col].BValue);
						actual_matrice.board[row][col] = matrice.board[row][col];
					}
				}
			}
		}
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
	pthread_create(&thread_app, NULL, change_number_app, NULL);
	printf("Creation thread d'envoi\n");
	pthread_create(&thread_send, NULL, send_message, NULL);


	(void)pthread_join(thread_read, NULL);
	(void)pthread_join(thread_app, NULL);
	(void)pthread_join(thread_send, NULL);

	sem_destroy(&semaphore_input);
	sem_destroy(&semaphore_display);
	closeLink();
	return 0;
}
