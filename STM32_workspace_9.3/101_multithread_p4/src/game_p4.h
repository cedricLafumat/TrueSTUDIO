/*
 * game_p4.h
 *
 *  Created on: 31 mars 2020
 *      Author: cedric
 */


#ifndef GAME_P4_H_
#define GAME_P4_H_

#include<stdint.h>
#include<stdbool.h>

#define EMPTY_CASE 0
#define LINE_COUNT 6
#define COL_COUNT 7
#define INIT_PLAYER 0


typedef enum { live, stop_winner, stop_equal } status_t;

typedef enum { horiz , vert , right_diag , left_diag } victory_t;

typedef enum { NO_PLAYER, PLAYER_1, PLAYER_2} player_t;

typedef struct{
	int8_t col;
	int8_t line;
}point_t;

typedef struct{
	status_t status; // status of winner
	victory_t win_type; //victory_type
	player_t win_player; // winner player
	point_t win_position[4]; // position of 4 winner token
}winner_t;

typedef struct{
	bool is_ok;
	point_t beg_position;
	point_t end_position;
}pos_token_t;


void gp4_init(void);
void gp4_display(void);
pos_token_t gp4_next_player(void);
pos_token_t gp4_top_move_token_left(void);
pos_token_t gp4_top_move_token_right(void);
pos_token_t gp4_top_play_token(void);
winner_t gp4_check_winner(void);


#endif /* GAME_P4_H_ */
