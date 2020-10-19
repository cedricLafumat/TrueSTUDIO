/*
 * game.h
 *
 *  Created on: 15 Apr 2020
 *      Author: cedric
 */

#ifndef GAME_H_
#define GAME_H_

#define NB_TIMERS 3
#define DELAY_BLINK 500000
#define DELAY_TO_PLAY 30000000
#define DELAY_IDLE 5000000
#define DELAY_SLEEP_TIMER 10000
#define SIZELINE 50

typedef struct{
	int RValue;
	int GValue;
	int BValue;
}RGB;

typedef struct{
	int number;
	int status;
	int countdown;
	int owner;
}Timer;


typedef enum {QUEUE_READ, QUEUE_SEND} QUEUE_ID;

typedef enum {NUMBER, P4, MORPION, CLAVIER, DEPLACEMENT, DISPLAY_TOKEN, t} COMMAND_TYPE;

typedef enum {STOP, START} STATUS_TIMER;

typedef enum {APP, DISPLAY} OWNER_TIMER;


void init_matrice(void);
void SetLedMatrice();
void start_game(void);
//void blink_led(winner_t winner, char *message);
//void compute_message(char message_send[10], pos_token_t move_token);
void send_message(QUEUE_ID queue, char *message, int message_lenght);
int receive_message(QUEUE_ID queue, char *message, int message_lenght);
//void set_number(int number);
void *read_input(void *arg);
void *application(void *arg);
void *show_board(void *arg);
void *timer(void *arg);


#endif /* GAME_H_ */