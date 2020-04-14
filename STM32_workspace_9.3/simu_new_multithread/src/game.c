/*
 * game.c
 *
 *  Created on: 9 avr. 2020
 *      Author: marc
 */

#include "game.h"
#include "leds_control.h"

static Matrix matrix;
static Matrix actual_display;

queue *queue_init(void) {
	queue *list = malloc(sizeof(*list));
	list->first = NULL;
	list->last = NULL;
	return list;
}

void init_matrix(void) {
	for (int row = 0; row < TAB_SIZE; row++) {
		for (int col = 0; col < TAB_SIZE; col++) {
			matrix.board[row][col].RValue = black.RValue;
			matrix.board[row][col].GValue = black.GValue;
			matrix.board[row][col].BValue = black.BValue;
			actual_display.board[row][col].RValue = black.RValue;
			actual_display.board[row][col].GValue = black.GValue;
			actual_display.board[row][col].BValue = black.BValue;
		}
	}
	matrix.init = INIT_OK;
	actual_display.init = INIT_OK;
}

void set_number(int nbr) {
	color nbr_color = PLAYER_COLOR;
	color bckgrnd_color = BACKGROUND;
	for (int row = 0; row < TAB_SIZE; row++) {
		for (int col = 0; col < TAB_SIZE; col++) {
			if (nbr == 1) { /*Ensemble de conditions pour afficher le chiffre 1*/
				if ((col == 4) || (row == 3 && col == 1)
						|| (row == 2 && col == 2) || (row == 1 && col == 3)) {
					matrix.board[row][col] = nbr_color;
				} else
					matrix.board[row][col] = bckgrnd_color;
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
					matrix.board[row][col] = nbr_color;
				} else
					matrix.board[row][col] = bckgrnd_color;
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
					matrix.board[row][col] = nbr_color;
				} else
					matrix.board[row][col] = bckgrnd_color;
			}
			if (nbr == 4) { /*Ensemble de conditions pour afficher le chiffre 4*/
				if ((row == 0 && col == 4) || (row == 1 && col == 3)
						|| (row == 1 && col == 4) || (row == 2 && col == 2)
						|| (row == 2 && col == 4) || (row == 3 && col == 1)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 3 && col == 5)
						|| (row == 4 && col == 4) || (row == 5 && col == 4)
						|| (row == 6 && col == 4)) {
					matrix.board[row][col] = nbr_color;
				} else
					matrix.board[row][col] = bckgrnd_color;
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
					matrix.board[row][col] = nbr_color;
				} else
					matrix.board[row][col] = bckgrnd_color;
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
					matrix.board[row][col] = nbr_color;
				} else
					matrix.board[row][col] = bckgrnd_color;
			}
			if (nbr == 7) { /*Ensemble de conditions pour afficher le chiffre 7*/
				if ((row == 0 && col == 1) || (row == 0 && col == 2)
						|| (row == 0 && col == 3) || (row == 0 && col == 4)
						|| (row == 0 && col == 5) || (row == 1 && col == 5)
						|| (row == 2 && col == 5) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 3 && col == 5)
						|| (row == 4 && col == 5) || (row == 5 && col == 5)
						|| (row == 6 && col == 5)) {
					matrix.board[row][col] = nbr_color;
				} else
					matrix.board[row][col] = bckgrnd_color;
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
					matrix.board[row][col] = nbr_color;
				} else
					matrix.board[row][col] = bckgrnd_color;
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
					matrix.board[row][col] = nbr_color;
				} else
					matrix.board[row][col] = bckgrnd_color;
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
					matrix.board[row][col] = nbr_color;
				} else
					matrix.board[row][col] = bckgrnd_color;
			}
		}
	}
}

void push(queue *queue, char *input) {
	user_input *new_input = malloc(sizeof(*new_input));
	if (new_input == NULL) {
		printf("erreur alloc mémoire push\n");
	}
	new_input->value = *input;
	new_input->next = NULL;
	pthread_mutex_lock(&queue->mutex);
	if (queue->first != NULL) {
		user_input *first_input = queue->last;
		first_input->next = new_input;
		queue->last = new_input;
	} else {
		queue->first = new_input;
		queue->last = new_input;
	}
	pthread_mutex_unlock(&queue->mutex);
}

int pop_element(queue *queue, char *value) {
	if (queue->first == NULL) { // retourne -1 si liste vide
		printf("liste vide (pop)\n");
		return -1;
	}
	pthread_mutex_lock(&queue->mutex);
	user_input *first_input = queue->first;
	*value = first_input->value;
	queue->first = first_input->next;
	pthread_mutex_unlock(&queue->mutex);
	free(first_input);
	return 0;
}

void send_message(queue *queue, char *message, int message_lenght) {
	push(queue, message);
	sem_post(&queue->semaphore);
}

int receive_message(queue *queue, char *message, int message_lenght) {
	sem_wait(&queue->semaphore);
	int return_value = pop_element(queue, message);
	return return_value;
}

/*-----------------------------------------------------------------------------------
 *
 *
 *                                     THREAD
 *
 *
 * -----------------------------------------------------------------------------------
 */

/*THREAD POUR AFFICHER LA MATRICE*/
void *show_board(void *arg) {
	while (1) {
		printf("lancement thread affichage\n");
		int user_input = 0;
		if (receive_message(queue_app_display, (char *) &user_input, MSG_LENGHT)
				== 0) {
//		sem_wait(&sem_display);
//		pop_element(queue_app_display, &user_input);
			set_number(user_input);
			printf("affichage numéro %d\n", user_input);
			for (int row = 0; row < TAB_SIZE; row++) {
				for (int col = 0; col < TAB_SIZE; col++) {
					if ((matrix.board[row][col].RValue
							== actual_display.board[row][col].RValue)
							&& (matrix.board[row][col].GValue
									== actual_display.board[row][col].GValue)
							&& (matrix.board[row][col].BValue
									== actual_display.board[row][col].BValue)) {
					} else {
						setLedColor(row + 1, col + 1,
								matrix.board[row][col].RValue,
								matrix.board[row][col].GValue,
								matrix.board[row][col].BValue);
						actual_display.board[row][col] = matrix.board[row][col];
					}
				}
			}
		}
	}
	return NULL;
}

/*THREAD APP*/
void *application(void *arg) {
	if (matrix.init == INIT_OK) {
		int user_input = 0;
		static int number_value = 0;
		send_message(queue_app_display, (char *) &number_value, MSG_LENGHT);
//		push(queue_app_display, number_value);
//		sem_post(&sem_display);
		while (1) {
//			pop_element(queue_push_app, &user_input);
//			sem_wait(&sem_button);
			if (receive_message(queue_push_app, (char *) &user_input,
					MSG_LENGHT) == 0) {
				printf("application - réception valeur : %d\n", user_input);
				if (user_input == UP) {
					number_value++;
					if (number_value > MAX_NUMBER) {
						number_value = MIN_NUMBER;
					}
				}
				if (user_input == DOWN) {
					number_value--;
					if (number_value < MIN_NUMBER) {
						number_value = MAX_NUMBER;
					}
				}
				printf("application - envoi valeur %d\n", number_value);
				send_message(queue_app_display, (char *) &number_value,
						MSG_LENGHT);
//				push(queue_push_app, number_value);
//				sem_post(&sem_display);
			}
		}
	}
	return NULL;
}

/*THREAD POUR GÉRER LES COMMANDES ENTRANTES*/
void *user_button(void *arg) {
	if (matrix.init == INIT_OK) {
		char input[5] = { 0 };
		while (1) {
			if (readbutton(input, 5) == LCRC_OK) {
				int user_input = 0;
				if (input[3] == 100) {
					printf("\nnouvelle entrée\n");
					for (int i = 0; i < 4; i++) {
						printf("%d ", input[i]);
					}
					printf("\n");
					if (input[2] == 117) {
						// HAUT
						user_input = UP;
					}
					if (input[2] == 100) {
						// BAS
						user_input = DOWN;
					}
					if (input[2] == 114) {
						// DROITE
						user_input = RIGHT;
					}
					if (input[2] == 108) {
						// GAUCHE
						user_input = LEFT;
					}
					send_message(queue_push_app, (char *) &user_input,
							MSG_LENGHT);
//					push(queue_push_app, user_input);
//					sem_post(&sem_button);
				}
			}
		}
	}
	return NULL;
}
