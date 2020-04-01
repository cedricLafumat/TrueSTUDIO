/*
 * game_p4.c
 *
 *  Created on: 30 mars 2020
 *      Author: cedric
 */
#include<stdio.h>
#include"game_p4.h"
#include"debug.h"




static int8_t g_matrice[COL_COUNT][LINE_COUNT];
static int8_t g_token_top_selector; // entre 1 et COL_COUNT
static int8_t g_active_player;

void gp4_init(void) {
	int8_t line = 0;
	int8_t col = 0;
	for (line = 0; line < LINE_COUNT; line++) {
		for (col = 0; col < COL_COUNT; col++) {
			g_matrice[col][line] = EMPTY_CASE;
		}
	}
	g_active_player = PLAYER_1;
	debug_printf(3, "Joueur actif : %d\n\n", g_active_player);
	g_token_top_selector = 1;
	g_matrice[1][0] = 1;
	g_matrice[2][0] = 1;
	g_matrice[5][0] = 1;
	g_matrice[6][0] = 1;
}

void gp4_display(void) {
	/*
	 * print line token position
	 */
	printf("TOP    = ");
	for (int8_t col = 1; col <= COL_COUNT; col++) {
		if (col != g_token_top_selector) {
			printf("- ");
		} else {
			printf("%d ", g_active_player);
		}
	}
	printf("\n");

	/*
	 * print matrix
	 */
	for (int line = 1; line <= LINE_COUNT; line++){
		printf("LINE %d = ", line);
		for (int col = 1; col <= COL_COUNT; col++) {
			printf("%d ", g_matrice[col-1][line-1]);
			}
		printf("\n");
	}
	printf("\n");
}

void gp4_next_player(void){
	if (g_active_player == PLAYER_1){
		g_active_player = PLAYER_2;
	}
	else{
		g_active_player = PLAYER_1;
	}
}

void gp4_top_move_token_left(void){
	g_token_top_selector -= 1;
	if (g_token_top_selector < 1){
		g_token_top_selector = COL_COUNT;
	}
	while (g_matrice[g_token_top_selector -1][0] != EMPTY_CASE ){
		g_token_top_selector -= 1;
		if (g_token_top_selector < 1){
				g_token_top_selector = COL_COUNT;
			}
	}
}

void gp4_top_move_token_right(void){
	g_token_top_selector += 1;
	if (g_token_top_selector > COL_COUNT){
		g_token_top_selector = 1;
	}
	while (g_matrice[g_token_top_selector -1][0] != EMPTY_CASE ){
		g_token_top_selector += 1;
		if (g_token_top_selector > COL_COUNT){
			g_token_top_selector = 1;
		}
	}
}

coordinate_t gp4_top_play_token(void){
	int8_t play_line = LINE_COUNT -1;
	int8_t x_coordinate = 0;
	int8_t y_coordinate = 0;

	while (g_matrice[g_token_top_selector-1][play_line] != EMPTY_CASE){
		play_line -= 1;
	}
	g_matrice[g_token_top_selector-1][play_line] = g_active_player;
	x_coordinate = g_token_top_selector-1;
	y_coordinate = play_line;
	debug_printf(2, "Joueur actif : %d\n\n", g_active_player);
	printf("x : %d y : %d\n", x_coordinate, y_coordinate);
	coordinate_t coordinates = {x_coordinate,y_coordinate};
	printf("x : %d y : %d\n", coordinates.x, coordinates.y);
	return coordinates;
}

void gp4_check_winner(void){

}

