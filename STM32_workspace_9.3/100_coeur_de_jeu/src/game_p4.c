/*
 * game_p4.c
 *
 *  Created on: 30 mars 2020
 *      Author: cedric
 */

// ---------------------------------------- INCLUDE --------------------------

#include<stdio.h>
#include"game_p4.h"
#include"debug.h"
#include<stdbool.h>

// ---------------------------------------- VARIABLE GLOBALE -----------------

static int8_t g_matrice[COL_COUNT][LINE_COUNT];
static int8_t g_token_top_selector; // entre 1 et COL_COUNT
static int8_t g_active_player = 0;


// ---------------------------------------- DECLARATION FONCTION -----------------

void gp4_init(void) {
	int8_t line = 0;
	int8_t col = 0;
	for (line = 0; line < LINE_COUNT; line++) {
		for (col = 0; col < COL_COUNT; col++) {
			g_matrice[col][line] = EMPTY_CASE;
		}
	}
	g_active_player = PLAYER_1;
	debug_printf(10, "Joueur actif : %d\n\n", g_active_player);
	g_token_top_selector = 4;
	// ------------- SET TEST EGALITE
	g_matrice[0][0] = PLAYER_1;
	g_matrice[1][0] = PLAYER_1;
	g_matrice[2][0] = PLAYER_1;
	g_matrice[3][0] = PLAYER_2;
	g_matrice[4][0] = PLAYER_1;
	g_matrice[5][0] = PLAYER_1;
	g_matrice[6][0] = PLAYER_1;
	// ------------- SET RANDOM
	/*g_matrice[0][0] = PLAYER_1;
	g_matrice[1][0] = PLAYER_1;
	g_matrice[2][0] = PLAYER_1;
	g_matrice[3][0] = PLAYER_1;
	g_matrice[0][1] = PLAYER_1;
	g_matrice[0][2] = PLAYER_1;
	g_matrice[0][3] = PLAYER_1;*/
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
			if (col == COL_COUNT){
				printf("%d", g_matrice[col-1][line-1]);
			}
			else{
				printf("%d ", g_matrice[col-1][line-1]);
			}
		}
		printf("\n");
	}
//	printf("(COL)  = 1 2 3 4 5 6 7\n");
	printf("\n");
}

pos_token_t gp4_next_player(void){
	if (g_active_player == PLAYER_1){
		g_active_player = PLAYER_2;
	}
	else{
		g_active_player = PLAYER_1;
	}
	debug_printf(3, "Changement de joueur / Joueur actif : %d\n", g_active_player);
	pos_token_t result_move;
	g_token_top_selector = 4;
	/*
	 * If column is full, the token go to the next column
	 */
	if (g_matrice[g_token_top_selector -1][0] != EMPTY_CASE){
		result_move = gp4_top_move_token_right();
		g_token_top_selector = result_move.end_position.col;
		if (result_move.is_ok == false){
			error_printf("ERROR : Grille pleine");
			return result_move;
		}
	}
	return result_move;
}

pos_token_t gp4_top_move_token_left(void){
	pos_token_t move_token;
	move_token.is_ok = true;
	move_token.beg_position.col = g_token_top_selector-1;
	move_token.beg_position.line = 0;
	move_token.end_position.line = 0;
	int cpt_to_check_infinite_loop = 0;
	g_token_top_selector -= 1;
	cpt_to_check_infinite_loop += 1;
	if (g_token_top_selector < 1){
		g_token_top_selector = COL_COUNT;
	}
	while (g_matrice[g_token_top_selector -1][0] != EMPTY_CASE ){
		g_token_top_selector -= 1;
		cpt_to_check_infinite_loop += 1;
		if (g_token_top_selector < 1){
			g_token_top_selector = COL_COUNT;
		}
		if (cpt_to_check_infinite_loop == 8){
			g_token_top_selector += 1;
			if (g_token_top_selector > COL_COUNT){
				g_token_top_selector = 1;
			}
			error_printf("ERROR : boucle infini\n");
			move_token.is_ok = false;
		}
	}
	debug_printf(3, "Mouvement du joueur %d a gauche\n\n", g_active_player);
	move_token.end_position.col = g_token_top_selector-1;
	return move_token;
}

pos_token_t gp4_top_move_token_right(void){
	pos_token_t move_token;
	move_token.is_ok = true;
	move_token.beg_position.col = g_token_top_selector-1;
	move_token.beg_position.line = 0;
	move_token.end_position.line = 0;
	int cpt_to_check_infinite_loop = 0;
	g_token_top_selector += 1;
	cpt_to_check_infinite_loop += 1;
	if (g_token_top_selector > COL_COUNT){
		g_token_top_selector = 1;
	}
	while (g_matrice[g_token_top_selector -1][0] != EMPTY_CASE ){
		g_token_top_selector += 1;
		cpt_to_check_infinite_loop += 1;
		if (g_token_top_selector > COL_COUNT){
			g_token_top_selector = 1;
		}
		if (cpt_to_check_infinite_loop == 8){
			g_token_top_selector -= 1;
			if (g_token_top_selector < 1){
				g_token_top_selector = COL_COUNT;
			}
			error_printf("ERROR : boucle infini\n");
			move_token.is_ok = false;
			return move_token;
		}
	}
	debug_printf(3, "Mouvement du joueur %d a droite\n\n", g_active_player);
	move_token.end_position.col = g_token_top_selector-1;
	return move_token;
}

pos_token_t gp4_top_play_token(void){
	int8_t play_line = LINE_COUNT -1;

	while (g_matrice[g_token_top_selector-1][play_line] != EMPTY_CASE){
		play_line -= 1;
	}
	g_matrice[g_token_top_selector-1][play_line] = g_active_player;
	pos_token_t token_played;
	token_played.is_ok = true;
	token_played.beg_position.col = g_token_top_selector-1;
	token_played.beg_position.line = 0;
	token_played.end_position.col = g_token_top_selector -1;
	token_played.end_position.line = play_line;
	debug_printf(3, "Joueur %d joue // Coordonn�es du jeton jou� "
			"[col : %d line : %d]\n", g_active_player, token_played.end_position.col, token_played.end_position.line);
	return token_played;
}


winner_t check_horizontally_win(winner_t winner, int8_t col, int8_t line){
	if ((g_matrice[col+1][line] == g_active_player) && (g_matrice[col+2][line] == g_active_player)
			&& ((g_matrice[col+3][line]) == g_active_player)){
		printf("\nJoueur %d a gagn� horizontalement\n", g_active_player);
		printf("Coordonees de jeton 1 : [col : %d line : %d]\n", col, line);
		printf("Coordonees de jeton 2 : [col : %d line : %d]\n", col+1, line);
		printf("Coordonees de jeton 3 : [col : %d line : %d]\n", col+2, line);
		printf("Coordonees de jeton 4 : [col : %d line : %d]\n", col+3, line);
		winner.status = stop_winner;
		winner.win_type = horiz;
		winner.win_player = g_active_player;
		winner.win_position[0].col = col;
		winner.win_position[0].line = line;
		winner.win_position[1].col = col+1;
		winner.win_position[1].line = line;
		winner.win_position[2].col = col+2;
		winner.win_position[2].line = line;
		winner.win_position[3].col = col+3;
		winner.win_position[3].line = line;
		return winner;
	}
	return winner;
}

winner_t check_vertically_win(winner_t winner, int8_t col, int8_t line){
	if ((g_matrice[col][line+1] == g_active_player) && (g_matrice[col][line+2] == g_active_player)
			&& (g_matrice[col][line+3] == g_active_player)){
		printf("\nJoueur %d a gagn� verticalement\n", g_active_player);
		printf("Coordonees de jeton 1 : [col : %d line : %d]\n", col, line);
		printf("Coordonees de jeton 2 : [col : %d line : %d]\n", col, line+1);
		printf("Coordonees de jeton 3 : [col : %d line : %d]\n", col, line+2);
		printf("Coordonees de jeton 4 : [col : %d line : %d]\n", col, line+3);
		winner.status = stop_winner;
		winner.win_type = vert;
		winner.win_player = g_active_player;
		winner.win_position[0].col = col;
		winner.win_position[0].line = line;
		winner.win_position[1].col = col;
		winner.win_position[1].line = line+1;
		winner.win_position[2].col = col;
		winner.win_position[2].line = line+2;
		winner.win_position[3].col = col;
		winner.win_position[3].line = line+3;
		return winner;
	}
	return winner;
}

winner_t check_left_diag_win(winner_t winner, int8_t col, int8_t line){
	if ((g_matrice[col-1][line+1] == g_active_player) && (g_matrice[col-2][line+2] == g_active_player)
							&& (g_matrice[col-3][line+3] == g_active_player)){
		printf("\nJoueur %d a gagn� en diagonale gauche\n", g_active_player);
		printf("Coordonees de jeton 1 : [col : %d line : %d]\n", col, line);
		printf("Coordonees de jeton 2 : [col : %d line : %d]\n", col-1, line+1);
		printf("Coordonees de jeton 3 : [col : %d line : %d]\n", col-2, line+2);
		printf("Coordonees de jeton 4 : [col : %d line : %d]\n", col-3, line+3);
		winner.status = stop_winner;
		winner.win_type = left_diag;
		winner.win_player = g_active_player;
		winner.win_position[0].col = col;
		winner.win_position[0].line = line;
		winner.win_position[1].col = col-1;
		winner.win_position[1].line = line+1;
		winner.win_position[2].col = col-2;
		winner.win_position[2].line = line+2;
		winner.win_position[3].col = col-3;
		winner.win_position[3].line = line+3;
		return winner;
	}
	return winner;
}

winner_t check_right_diag_win(winner_t winner, int8_t col, int8_t line){
	if ((g_matrice[col+1][line+1] == g_active_player) && (g_matrice[col+2][line+2] == g_active_player)
							&& (g_matrice[col+3][line+3] == g_active_player)){
		printf("\nJoueur %d a gagn� en diagonale gauche\n", g_active_player);
		printf("Coordonees de jeton 1 : [col : %d line : %d]\n", col, line);
		printf("Coordonees de jeton 2 : [col : %d line : %d]\n", col+1, line+1);
		printf("Coordonees de jeton 3 : [col : %d line : %d]\n", col+2, line+2);
		printf("Coordonees de jeton 4 : [col : %d line : %d]\n", col+3, line+3);
		winner.status = stop_winner;
		winner.win_type = left_diag;
		winner.win_player = g_active_player;
		winner.win_position[0].col = col;
		winner.win_position[0].line = line;
		winner.win_position[1].col = col+1;
		winner.win_position[1].line = line+1;
		winner.win_position[2].col = col+2;
		winner.win_position[2].line = line+2;
		winner.win_position[3].col = col+3;
		winner.win_position[3].line = line+3;
		return winner;
	}
	return winner;
}


winner_t gp4_check_winner(void){
	int8_t line = 0;
	int8_t col = 0;
	winner_t winner;
	winner.status = live;
	winner.win_type = 0;
	winner.win_player = 0;
	winner.win_position[0].col = 0;
	winner.win_position[0].line = 0;
	winner.win_position[1].col = 0;
	winner.win_position[1].line = 0;
	winner.win_position[2].col = 0;
	winner.win_position[2].line = 0;
	winner.win_position[3].col = 0;
	winner.win_position[3].line = 0;
	if((g_matrice[0][0] != EMPTY_CASE) && (g_matrice[1][0] != EMPTY_CASE) && (g_matrice[2][0] != EMPTY_CASE) && (g_matrice[3][0] != EMPTY_CASE)
			&& (g_matrice[4][0] != EMPTY_CASE) && (g_matrice[5][0] != EMPTY_CASE) && (g_matrice[6][0] != EMPTY_CASE)){
		debug_printf(3,"Egalite\n");
		winner.status = stop_equal;
		return winner;
	}
	for (line = 0; line < LINE_COUNT; line++) {
		for (col = 0; col < COL_COUNT; col++) {
			if (g_matrice[col][line] == g_active_player){
				// CHECK HORIZONTALEMENT
				if(col < COL_COUNT -3){
					winner = check_horizontally_win(winner, col, line);
					if (winner.status == stop_winner){
						return winner;
					}
				}
				// CHECK VERTICALEMENT
				if(line < LINE_COUNT -3){
					winner = check_vertically_win(winner, col, line);
					if (winner.status == stop_winner){
						return winner;
					}
				}
				// CHECK DIAGONALEMENT GAUCHE
				if((col >= 3) && (line < LINE_COUNT -3)){
					winner = check_left_diag_win(winner, col, line);
					if (winner.status == stop_winner){
						return winner;
					}
				}
				// CHECK DIAGONALEMENT DROITE
				if((col < COL_COUNT -3) && (line < LINE_COUNT -3)){
					winner = check_right_diag_win(winner, col, line);
					if (winner.status == stop_winner){
						return winner;
					}
				}
			}
		}
	}
	return winner;
}
