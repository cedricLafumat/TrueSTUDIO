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

// ---------------------------------------- VARIABLE GLOBALE -----------------

static int8_t g_matrice[COL_COUNT][LINE_COUNT];
static int8_t g_token_top_selector; // entre 1 et COL_COUNT
static int8_t g_active_player;


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
	// ------------- SET BUG WINNER HORIZONTAL
	/*g_matrice[4][1] = PLAYER_1;
	g_matrice[5][1] = PLAYER_1;
	g_matrice[6][1] = PLAYER_1;
	g_matrice[0][0] = PLAYER_1;*/
	// ------------- SET BUG WINNER VERTICAL
	/*g_matrice[0][3] = PLAYER_1;
	g_matrice[0][4] = PLAYER_1;
	g_matrice[0][5] = PLAYER_1;
	g_matrice[1][0] = PLAYER_1;*/
	// ------------- SET BUG WINNER DIAG GAUCHE
	/*g_matrice[3][3] = PLAYER_1;
	g_matrice[2][4] = PLAYER_1;
	g_matrice[1][5] = PLAYER_1;
	g_matrice[1][0] = PLAYER_1;*/
	// ------------- SET BUG WINNER DIAG DROITE
	/*g_matrice[2][3] = PLAYER_1;
	g_matrice[3][4] = PLAYER_1;
	g_matrice[4][5] = PLAYER_1;
	g_matrice[6][0] = PLAYER_1;*/
	// ------------- SET RANDOM
	/*g_matrice[0][0] = PLAYER_1;
	g_matrice[1][0] = PLAYER_1;
	g_matrice[2][0] = PLAYER_1;
	g_matrice[3][0] = PLAYER_1;*/
}

void gp4_display(void) {
	/*
	 * print line token position
	 */
	printf("\nTOP    = ");
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
	printf("(COL)  = 1 2 3 4 5 6 7\n");
	printf("\n");
}

void gp4_next_player(void){
	if (g_active_player == PLAYER_1){
		g_active_player = PLAYER_2;
	}
	else{
		g_active_player = PLAYER_1;
	}
	debug_printf(4, "Changement de joueur / Joueur actif : %d\n", g_active_player);
	g_token_top_selector = 4;
	while (g_matrice[g_token_top_selector -1][0] != EMPTY_CASE){
		g_token_top_selector += 1;
		if (g_token_top_selector > COL_COUNT){
			g_token_top_selector = 1;
		}
	}
}

void gp4_top_move_token_left(void){
	int cpt_to_check_infinite_loop = 0;
	g_token_top_selector -= 1;
	cpt_to_check_infinite_loop += 1;
	if (g_token_top_selector < 1){
		g_token_top_selector = COL_COUNT;
	}
	while ((g_matrice[g_token_top_selector -1][0] != EMPTY_CASE ) && (cpt_to_check_infinite_loop <= 8)){
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
			/*
			 * retour code erreur si boucle infini ???
			 *
			 */
			return;
		}
	}
	debug_printf(3, "Mouvement du joueur %d a gauche\n\n", g_active_player);
}

void gp4_top_move_token_right(void){
	int cpt_to_check_infinite_loop = 0;
	g_token_top_selector += 1;
	cpt_to_check_infinite_loop += 1;
	if (g_token_top_selector > COL_COUNT){
		g_token_top_selector = 1;
	}
	while ((g_matrice[g_token_top_selector -1][0] != EMPTY_CASE ) && (cpt_to_check_infinite_loop <= 8)){
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
			/*
			 * retour code erreur si boucle infini ???
			 *
			 */
			return;
		}
	}
	debug_printf(3, "Mouvement du joueur %d a droite\n\n", g_active_player);
	gp4_display();
}

coordinate_t gp4_top_play_token(void){
	int8_t play_line = LINE_COUNT -1;

	while (g_matrice[g_token_top_selector-1][play_line] != EMPTY_CASE){
		play_line -= 1;
	}
	g_matrice[g_token_top_selector-1][play_line] = g_active_player;
	coordinate_t coordinates = {(g_token_top_selector-1),play_line};
	debug_printf(3, "Joueur %d joue // Coordonn�es du jeton jou� "
			"[x : %d y : %d]\n", g_active_player, coordinates.x, coordinates.y);
	return coordinates;
}


winner_t gp4_check_winner(void){
	int8_t line = 0;
	int8_t col = 0;
	winner_t winner = {0, {0,0}, {0,0}, {0,0}, {0,0}, non_victory};
	if((g_matrice[0][0] && g_matrice[1][0] && g_matrice[2][0] && g_matrice[3][0] && g_matrice[4][0]
					&& g_matrice[5][0]&& g_matrice[6][0]) != EMPTY_CASE){
		debug_printf(3,"Egalite\n");
		winner.type_victory = egalite;
		return winner;
	}

	for (line = 0; line < LINE_COUNT; line++) {
		for (col = 0; col < COL_COUNT; col++) {
			if (g_matrice[col][line] == g_active_player){
				// CHECK HORIZONTALEMENT
				if ((g_matrice[col+1][line] == g_active_player) && (g_matrice[col+2][line] == g_active_player)
						&& ((g_matrice[col+3][line]) == g_active_player)){
					if ((col+3) >= COL_COUNT){
						return winner;
					}
					printf("\nJoueur %d a gagn� horizontalement\n", g_active_player);
					printf("Coordonees de jeton 1 : [x : %d y : %d]\n", col, line);
					printf("Coordonees de jeton 2 : [x : %d y : %d]\n", col+1, line);
					printf("Coordonees de jeton 3 : [x : %d y : %d]\n", col+2, line);
					printf("Coordonees de jeton 4 : [x : %d y : %d]\n", col+3, line);
					int8_t player_winner = 0;
					player_winner = g_active_player;
					coordinate_t coordinate_token1 = {col, line};
					coordinate_t coordinate_token2 = {col+1, line};
					coordinate_t coordinate_token3 = {col+2, line};
					coordinate_t coordinate_token4 = {col+3, line};
					winner_t winner = { player_winner, coordinate_token1, coordinate_token2,
							coordinate_token3, coordinate_token4, horizontal};
					return winner;
				}
				// CHECK VERTICALEMENT
				else if ((g_matrice[col][line+1] == g_active_player) && (g_matrice[col][line+2] == g_active_player)
						&& (g_matrice[col][line+3] == g_active_player)){
					if ((line+3) >= LINE_COUNT){
							return winner;
					}
					printf("\nJoueur %d a gagn� verticalement\n", g_active_player);
					printf("Coordonees de jeton 1 : [x : %d y : %d]\n", col, line);
					printf("Coordonees de jeton 2 : [x : %d y : %d]\n", col, line+1);
					printf("Coordonees de jeton 3 : [x : %d y : %d]\n", col, line+2);
					printf("Coordonees de jeton 4 : [x : %d y : %d]\n", col, line+3);
					int8_t player_winner = 0;
					player_winner = g_active_player;
					coordinate_t coordinate_token1 = {col, line};
					coordinate_t coordinate_token2 = {col, line+1};
					coordinate_t coordinate_token3 = {col, line+2};
					coordinate_t coordinate_token4 = {col, line+3};
					winner_t winner = { player_winner, coordinate_token1, coordinate_token2,
							coordinate_token3, coordinate_token4, vertical};
					return winner;
				}
				// CHECK DIAGONALEMENT BAS GAUCHE
				else if ((g_matrice[col-1][line+1] == g_active_player) && (g_matrice[col-2][line+2] == g_active_player)
						&& (g_matrice[col-3][line+3] == g_active_player)){
					if (((col-3) < 0) || ((line+3)>= LINE_COUNT)){
						return winner;
					}
					printf("\nJoueur %d a gagn� en diagonale gauche\n", g_active_player);
					printf("Coordonees de jeton 1 : [x : %d y : %d]\n", col, line);
					printf("Coordonees de jeton 2 : [x : %d y : %d]\n", col-1, line+1);
					printf("Coordonees de jeton 3 : [x : %d y : %d]\n", col-2, line+2);
					printf("Coordonees de jeton 4 : [x : %d y : %d]\n", col-3, line+3);
					int8_t player_winner = 0;
					player_winner = g_active_player;
					coordinate_t coordinate_token1 = {col, line};
					coordinate_t coordinate_token2 = {col-1, line+1};
					coordinate_t coordinate_token3 = {col-2, line+2};
					coordinate_t coordinate_token4 = {col-3, line+3};
					winner_t winner = { player_winner, coordinate_token1, coordinate_token2,
										coordinate_token3, coordinate_token4, diagonale_gauche};
					return winner;
				}
				// CHECK DIAGONALEMENT BAS DROITE
				else if ((g_matrice[col+1][line+1] == g_active_player) && (g_matrice[col+2][line+2] == g_active_player)
						&& (g_matrice[col+3][line+3] == g_active_player)){
					if (((col+3) >= COL_COUNT) || ((line+3)>= LINE_COUNT)){
						return winner;
					}
					printf("Joueur %d a gagn� en diagonale droite\n", g_active_player);
					printf("Coordonees de jeton 1 : [x : %d y : %d]\n", col, line);
					printf("Coordonees de jeton 2 : [x : %d y : %d]\n", col+1, line+1);
					printf("Coordonees de jeton 3 : [x : %d y : %d]\n", col+2, line+2);
					printf("Coordonees de jeton 4 : [x : %d y : %d]\n", col+3, line+3);
					int8_t player_winner = 0;
					player_winner = g_active_player;
					coordinate_t coordinate_token1 = {col, line};
					coordinate_t coordinate_token2 = {col+1, line+1};
					coordinate_t coordinate_token3 = {col+2, line+2};
					coordinate_t coordinate_token4 = {col+3, line+3};
					winner_t winner = { player_winner, coordinate_token1, coordinate_token2,
										coordinate_token3, coordinate_token4, diagonale_droite};
					return winner;
				}
			}
		}
	}
	return winner;
}
