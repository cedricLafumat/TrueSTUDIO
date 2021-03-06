/*
 * game.c
 *
 *  Created on: 15 Apr 2020
 *      Author: cedric
 */
#include<stdio.h>
#include"game.h"
#include"game_p4.h"
#include"leds_control.h"
#include"fifo.h"
#include"debug.h"
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
#include <stdbool.h>

/*
 * -----------------------------------------------------------------------------------------------------------------------------------
 *
 *
 * 														GLOBAL VARIABILE
 *
 *
 * -----------------------------------------------------------------------------------------------------------------------------------
 */

static pthread_mutex_t mutex_timer;

static RGB actual_matrice[7][7];
static RGB matrice[7][7];
char init_matrice_is_ok = 0;
static int TabSize = 7;
static char message[5];
int actual_player;
Timer timer_blink;
Timer timer_to_play;
Timer timer_idle;
int blink_type = 0;
Timer tab_timer[NB_TIMERS];
//static int max_number = 14;
//static int number_value = 0;

const RGB Red={255,0,0};
const RGB Green={0,255,0};
const RGB Blue={0,0,255};
const RGB White={255,255,255};
const RGB Purple={255,0,255};
const RGB Yellow={255,255,0};
const RGB Black={0,0,0};

const RGB bckgrd = {0, 0, 0};
const RGB token_player_1 = {0, 0, 255};
const RGB token_player_2 = {255, 0, 0};

/*
 * -----------------------------------------------------------------------------------------------------------------------------------
 *
 *
 * 														FUNCTION
 *
 *
 * -----------------------------------------------------------------------------------------------------------------------------------
 */

void init_matrice(void){
	for (int line = 0; line < 7; line ++){
		for(int col = 0; col < 7; col ++){
			matrice[col][line] = bckgrd;
		}
	}
	matrice[3][0] = token_player_1;
	SetLedMatrice();
}

void SetLedMatrice(){
	for (int line=0; line<TabSize; line++){
		for(int col = 0; col < TabSize; col++){
			if (init_matrice_is_ok == 0){
				actual_matrice[col][line].RValue =  matrice[col][line].RValue;
				actual_matrice[col][line].GValue =  matrice[col][line].GValue;
				actual_matrice[col][line].BValue =  matrice[col][line].BValue;
				setLedColor(line+1, col+1, matrice[col][line].RValue, matrice[col][line].GValue, matrice[col][line].BValue);
			}
			else{
				if ((matrice[col][line].RValue != actual_matrice[col][line].RValue) ||
						(matrice[col][line].GValue != actual_matrice[col][line].GValue) ||
						(matrice[col][line].BValue != actual_matrice[col][line].BValue)){
					setLedColor(line+1, col+1, matrice[col][line].RValue, matrice[col][line].GValue, matrice[col][line].BValue);
					actual_matrice[col][line].RValue =  matrice[col][line].RValue;
					actual_matrice[col][line].GValue =  matrice[col][line].GValue;
					actual_matrice[col][line].BValue =  matrice[col][line].BValue;
				}
			}
		}
	}
	init_matrice_is_ok = 1;
}

void start_game(void){
	init_matrice();
	gp4_init();
	gp4_display();
	actual_player = PLAYER_1;
}





void blink_led(winner_t winner, char *message){
	if (blink_type == 0){
		matrice[winner.win_position[0].col][winner.win_position[0].line+1] = bckgrd;
		matrice[winner.win_position[1].col][winner.win_position[1].line+1] = bckgrd;
		matrice[winner.win_position[2].col][winner.win_position[2].line+1] = bckgrd;
		matrice[winner.win_position[3].col][winner.win_position[3].line+1] = bckgrd;
		SetLedMatrice();
		blink_type = 1;
	}
	else if (blink_type == 1){
		RGB token;
		if (message[1] == PLAYER_1){
			token = token_player_1;
		}
		else if (message[1] == PLAYER_2){
			token = token_player_2;
		}
		matrice[winner.win_position[0].col][winner.win_position[0].line+1] = token;
		matrice[winner.win_position[1].col][winner.win_position[1].line+1] = token;
		matrice[winner.win_position[2].col][winner.win_position[2].line+1] = token;
		matrice[winner.win_position[3].col][winner.win_position[3].line+1] = token;
		SetLedMatrice();
		blink_type = 0;
	}
}





void StartTimer(int num_timer, int delay){
	int countdown = (delay / DELAY_SLEEP_TIMER);
	/*if (num_timer > NB_TIMERS){
		debug_printf(4, "Bad number timer: %d\n", num_timer);
	}
	else{*/
		pthread_mutex_lock(&mutex_timer);
		tab_timer[num_timer].status = START;
		tab_timer[num_timer].countdown = countdown;
		pthread_mutex_unlock(&mutex_timer);
	//}
}

void StopTimer(int num_timer){
	/*if (num_timer > NB_TIMERS){
		debug_printf(4, "Bad number timer: %d\n", num_timer);
	}
	else {*/
		pthread_mutex_lock(&mutex_timer);
		tab_timer[num_timer].status = STOP;
		pthread_mutex_unlock(&mutex_timer);
	//}
}

void init_timer(void){
	// timer blink
	timer_blink.number = 0;
	StopTimer(timer_blink.number);
	timer_blink.owner = APP;
	//timer to play
	timer_to_play.number = 1;
	StartTimer(timer_to_play.number, DELAY_TO_PLAY);
	timer_to_play.owner = APP;
	//timer inactivity
	timer_idle.number = 2;
	StartTimer(timer_idle.number, DELAY_IDLE);
	timer_idle.owner = APP;
}



void compute_message(char message_send[10], pos_token_t move_token) {
	message_send[4] = move_token.beg_position.col;
	message_send[5] = move_token.beg_position.line;
	message_send[6] = move_token.end_position.col;
	message_send[7] = move_token.end_position.line;
}






void function_play_token(pos_token_t move_token, char message_send[10],
		pos_token_t move_token_next_player, char message_receive[10],
		const Timer* timer_blink, winner_t* winner) {
	//	message_send[0] = message_receive[0];
	move_token = gp4_top_play_token();
	compute_message(message_send, move_token);
	send_message(QUEUE_SEND, message_send, 1);
	*winner = gp4_check_winner();
	if (winner->status == live) {
		move_token_next_player = gp4_next_player();
		if (message_send[1] == PLAYER_1) {
			actual_player = PLAYER_2;
			message_send[1] = actual_player;
			compute_message(message_send, move_token_next_player);
			send_message(QUEUE_SEND, message_send, 1);
		}
		else if (message_send[1] == PLAYER_2) {
			actual_player = PLAYER_1;
			message_send[1] = actual_player;
			compute_message(message_send, move_token_next_player);
			send_message(QUEUE_SEND, message_send, 1);
		}
		StartTimer(timer_to_play.number, DELAY_TO_PLAY);
	}
	else if (winner->status == stop_winner) {
		StartTimer(timer_blink->number, DELAY_BLINK);
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
			if (message[0] == 112){
				command[0] = CLAVIER;
				if (message[3] == 117){
					if (message[1] == 49){
						command[1] = PLAYER_1;
					}
					else if (message[1] == 50){
						command[1] = PLAYER_2;
					}
					if (message[2] == 108){
						command[2] = left;
						send_message(QUEUE_READ, command, 1);
					}
					else if(message[2] == 114){
						command[2] = right;
						send_message(QUEUE_READ, command, 1);
					}
					else if(message[2] == 100){
						command[2] = down;
						send_message(QUEUE_READ, command, 1);
					}
					else if(message[2] == 117){
						command[2] = up;
						send_message(QUEUE_READ, command, 1);
					}
				}
			}
		}
	}
	(void) arg;
	pthread_exit(NULL);
}




void *application(void *arg){
	char message_receive_app[10];
	char message_send_app[10];
	int cpt_timer_win = 0;
	pos_token_t move_token, move_token_next_player;
	winner_t winner;
	actual_player = PLAYER_1;
	int state_game = 0;

	while(1){
		while (cpt_timer_win < 10){
			receive_message(QUEUE_READ, message_receive_app, 1);
			if (message_receive_app[0] == CLAVIER){
				if (state_game == 0){
					if (message_receive_app[1] == PLAYER_1){
						actual_player = PLAYER_1;
						//token_player_1 = {255, 0, 0};
					}
					else if (message_receive_app[1] == PLAYER_2){
						actual_player = PLAYER_2;
						//token_player_2 = {0, 0, 255};
					}
					start_game();
					state_game = 1;
					init_timer();
					winner.status = live;
				}
				else{
					if(actual_player == message_receive_app[1]){
						message_send_app[0] = message_receive_app[0];
						if (message_receive_app[1] == PLAYER_1){
							message_send_app[1] = PLAYER_1;
						}
						else if (message_receive_app[1] == PLAYER_2){
							message_send_app[1] = PLAYER_2;
						}
						if (message_receive_app[2] == left){
							move_token = gp4_top_move_token_left();
							StartTimer(timer_idle.number, DELAY_IDLE);
							compute_message(message_send_app, move_token);
							send_message(QUEUE_SEND, message_send_app, 1);
						}
						else if (message_receive_app[2] == right){
							move_token = gp4_top_move_token_right();
							StartTimer(timer_idle.number, DELAY_IDLE);
							compute_message(message_send_app, move_token);
							send_message(QUEUE_SEND, message_send_app, 1);
						}
						else if (message_receive_app[2] == down){
							function_play_token(move_token, message_send_app,
									move_token_next_player, message_receive_app, &timer_blink, &winner);
						}
					}
				}
			}
			else if((message_receive_app[0] == t) && (state_game == 1)){
				if (winner.status == stop_winner){
					message_send_app[0] = message_receive_app[0];
					message_send_app[1] = actual_player;
					blink_led(winner, message_send_app);
					cpt_timer_win ++;
					StartTimer(timer_blink.number, DELAY_BLINK);
				}
				else if (winner.status == live){
					message_send_app[0] = message_receive_app[0];
					message_send_app[1] = actual_player;
					function_play_token(move_token, message_send_app,
							move_token_next_player, message_receive_app, &timer_blink, &winner);
					StartTimer(timer_idle.number, DELAY_IDLE);
				}
			}
		}
		cpt_timer_win = 0;
		state_game = 0;

	}

	/*bool is_equal_to_equal = false;
	char valeur[10];

	FILE* config = NULL;
	config = fopen("/home/cedric/Atollic/TrueSTUDIO/STM32_workspace_9.3/101_multithread_p4/src/config.txt", "r");
	char newline[SIZELINE];
	while (fgets(newline, SIZELINE, config) != NULL){
		printf("%s", newline);
		//int index = 0;
		int index_valeur = 0;
		for (int index_line = 0; newline[index_line] != '\0'; index_line++){
			while (newline[index_line] != '=' ){
				is_equal_to_equal = false;
				index_line++;
			}
			is_equal_to_equal = true;
			if (is_equal_to_equal == true){
				valeur[index_valeur] = newline[index_line];
				index_valeur ++;
			}
		}
		printf("%s\n", valeur);
	}

	fclose(config);*/

	(void) arg;
	pthread_exit(NULL);
}





void *show_board(void *arg){
	char message[10];
	RGB token;
	SetLedMatrice();

	while (1){
		gp4_display();
		receive_message(QUEUE_SEND, message, 1);
		if((message[0] == CLAVIER) || (message[0] == t)){
			if (message[1] == PLAYER_1){
				token = token_player_1;
			}
			else if (message[1] == PLAYER_2){
				token = token_player_2;
			}
			int col_beg = message[4];
			int line_beg = message[5];
			int col_end = message[6];
			int line_end = message[7];
			matrice[col_beg][line_beg] = bckgrd;
			matrice[col_end][line_end] = token;
			SetLedMatrice();

		}
	}
	(void) arg;
	pthread_exit(NULL);
}





void *timer(void *arg){
	char message_timer[10];
	while(1){
		usleep(DELAY_SLEEP_TIMER);
		for (int i = 0; i < NB_TIMERS; i++){
			pthread_mutex_lock(&mutex_timer);
			if (tab_timer[i].status == START){
				tab_timer[i].countdown -= 1;
				if (tab_timer[i].countdown == 0){
					message_timer[0] = t;
					message_timer[1] = i;
					send_message(QUEUE_READ, message_timer, 1);
					tab_timer[i].status = STOP;
					StopTimer(i);
				}
			}
			pthread_mutex_unlock(&mutex_timer);
		}
	}
	(void) arg;
	pthread_exit(NULL);
}


/*
 * -----------------------------------------------------------------------------------------------------------------------------------
 *
 *
 * 														APPLI NUMBER
 *
 *
 * -----------------------------------------------------------------------------------------------------------------------------------
 */

/*void set_number(int number){
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
}*/


/*void *application(void *arg){
	if (message_receive[0] == NUMBER){
		if (message_receive[2] == down){
			number_value -= 1;
			if (number_value < 0){
				number_value = max_number;
			}
			message_send[2] = number_value;
			send_message(QUEUE_SEND, message_send, 1);
		}
		else if(message_receive[2] == up){
			number_value += 1;
			if (number_value > max_number){
				number_value = 0;
			}
			message_send[2] = number_value;
			send_message(QUEUE_SEND, message_send, 1);
		}
	}
}*/

/*void *show_board(void *arg){
	set_number(0);
	receive_message(QUEUE_SEND, message, 1);
	if (message[0] == NUMBER){
		//set_number(message[2]);
	}
}*/
