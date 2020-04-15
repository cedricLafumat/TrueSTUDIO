/*
 * game.h
 *
 *  Created on: 15 Apr 2020
 *      Author: cedric
 */

#ifndef GAME_H_
#define GAME_H_


typedef struct{
	int RValue;
	int GValue;
	int BValue;
}RGB;


typedef enum {QUEUE_READ, QUEUE_SEND} QUEUE_ID;




void SetLedMatrice(RGB **TabLine);
void set_number(int number);
void send_message(QUEUE_ID queue, int message, int message_lenght);
int receive_message(QUEUE_ID queue, int message, int message_lenght);
void *read_input(void *arg);
void *application(void *arg);
void *show_board(void *arg);


#endif /* GAME_H_ */
