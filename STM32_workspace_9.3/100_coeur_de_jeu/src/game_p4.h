/*
 * game_p4.h
 *
 *  Created on: 31 mars 2020
 *      Author: cedric
 */


#ifndef GAME_P4_H_
#define GAME_P4_H_

#include<stdint.h>

#define EMPTY_CASE 0
#define LINE_COUNT 6
#define COL_COUNT 7
#define INIT_PLAYER 0
#define PLAYER_1 1
#define PLAYER_2 2


typedef struct{
	int8_t x;
	int8_t y;
}coordinate_t;

typedef struct{
	int8_t player_winner;
	coordinate_t token1;
	coordinate_t token2;
	coordinate_t token3;
	coordinate_t token4;
	char victory_type;
}winner_t;


void gp4_init(void);
void gp4_display(void);
void gp4_next_player(void);
void gp4_top_move_token_left(void);
void gp4_top_move_token_right(void);
coordinate_t gp4_top_play_token(void);
int gp4_check_winner(void);


#endif /* GAME_P4_H_ */