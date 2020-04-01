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
	g_token_top_selector = 1;
	// --------------------   SET DE JEU POUR TEST
	/*g_matrice[1][1] = 1;
	g_matrice[2][2] = 1;
	g_matrice[3][3] = 1;
	g_matrice[4][4] = 1;*/
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
	debug_printf(4, "Changement de joueur / Joueur actif : %d\n", g_active_player);
	gp4_display();
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
			return;
		}
	}
	debug_printf(3, "Mouvement du joueur %d a gauche\n", g_active_player);
	gp4_display();
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
			return;
		}
	}
	debug_printf(3, "Mouvement du joueur %d a droite\n", g_active_player);
	gp4_display();
}

coordinate_t gp4_top_play_token(void){
	int8_t play_line = LINE_COUNT -1;
	int8_t x_coordinate = 0;
	int8_t y_coordinate = 0;

	int win = 0;

	while (g_matrice[g_token_top_selector-1][play_line] != EMPTY_CASE){
		play_line -= 1;
	}
	g_matrice[g_token_top_selector-1][play_line] = g_active_player;
	x_coordinate = g_token_top_selector-1;
	y_coordinate = play_line;
	coordinate_t coordinates = {x_coordinate,y_coordinate};
	debug_printf(3, "Joueur %d joue // Coordonn�es du jeton jou� "
			"[x : %d y : %d]\n", g_active_player, coordinates.x, coordinates.y);
	gp4_display();
	win = gp4_check_winner();
	if (win == 0){
		gp4_next_player();
	}
	return coordinates;
}

/*void gp4_check_winner_horizontally(void){
	int8_t line = 0;
	int8_t col = 0;
	for (line = 0; line < LINE_COUNT; line++) {
		for (col = 0; col < COL_COUNT; col++) {
			if (g_matrice[col][line] == g_active_player){
				if (g_matrice[col+1][line] == g_active_player){
					if (g_matrice[col+2][line] == g_active_player){
						if (g_matrice[col+3][line] == g_active_player){
							printf("\nJoueur %d a gagn� horizontalement\n", g_active_player);
							printf("Coordonees de debut : [x : %d y : %d]\n", col, line);
							printf("Coordonees de fin : [x : %d y : %d]\n", col+3, line);
							return;
						}
					}
				}
			}
		}
	}
}

void gp4_check_winner_verticaly(void){
	int8_t line = 0;
	int8_t col = 0;
	for (line = 0; line < LINE_COUNT; line++) {
		for (col = 0; col < COL_COUNT; col++) {
			if (g_matrice[col][line] == g_active_player){
				if (g_matrice[col][line+1] == g_active_player){
					if (g_matrice[col][line+2] == g_active_player){
						if (g_matrice[col][line+3] == g_active_player){
							printf("\nJoueur %d a gagn� verticalement\n", g_active_player);
							printf("Coordonees de debut : [x : %d y : %d]\n", col, line);
							printf("Coordonees de fin : [x : %d y : %d]\n", col, line+3);
							return;
						}
					}
				}
			}
		}
	}
}

void gp4_check_winner_diagonally_left(void){
	int8_t line = 0;
	int8_t col = 0;
	for (line = 0; line < LINE_COUNT; line++) {
		for (col = 0; col < COL_COUNT; col++) {
			if (g_matrice[col][line] == g_active_player){
				if (g_matrice[col-1][line+1] == g_active_player){
					if (g_matrice[col-2][line+2] == g_active_player){
						if (g_matrice[col-3][line+3] == g_active_player){
							printf("\nJoueur %d a gagn� en diagonale bas gauche\n", g_active_player);
							printf("Coordonees de debut : [x : %d y : %d]\n", col, line);
							printf("Coordonees de fin : [x : %d y : %d]\n", col-3, line+3);
							return;
						}
					}
				}
			}
		}
	}
}

void gp4_check_winner_diagonally_right(void){
	int8_t line = 0;
	int8_t col = 0;
	for (line = 0; line < LINE_COUNT; line++) {
		for (col = 0; col < COL_COUNT; col++) {
			if (g_matrice[col][line] == g_active_player){
				if (g_matrice[col+1][line+1] == g_active_player){
					if (g_matrice[col+2][line+2] == g_active_player){
						if (g_matrice[col+3][line+3] == g_active_player){
							printf("Joueur %d a gagn� en diagonale bas droite\n", g_active_player);
							printf("Coordonees de debut : [x : %d y : %d]\n", col, line);
							printf("Coordonees de fin : [x : %d y : %d]\n", col+3, line+3);
							return;
						}
					}
				}
			}
		}
	}
}*/

int gp4_check_winner(void){
	int8_t line = 0;
	int8_t col = 0;
	//winner_t winner;
	int win = 0;

	for (line = 0; line < LINE_COUNT; line++) {
		for (col = 0; col < COL_COUNT; col++) {
			if (g_matrice[col][line] == g_active_player){
				// CHECK HORIZONTALEMENT
				if (g_matrice[col+1][line] == g_active_player){
					if (g_matrice[col+2][line] == g_active_player){
						if (g_matrice[col+3][line] == g_active_player){
							printf("\nJoueur %d a gagn� horizontalement\n", g_active_player);
							printf("Coordonees de debut : [x : %d y : %d]\n", col, line);
							printf("Coordonees de fin : [x : %d y : %d]\n", col+3, line);
							/*int8_t player_winner = 0;
							player_winner = g_active_player;
							coordinate_t coordinate_token1 = {col, line};
							coordinate_t coordinate_token2 = {col+1, line};
							coordinate_t coordinate_token3 = {col+2, line};
							coordinate_t coordinate_token4 = {col+3, line};
							char victory_type;
							victory_type = 'h';
							winner_t winner = { player_winner, coordinate_token1, coordinate_token2,
									coordinate_token3, coordinate_token4, victory_type};
							return winner;*/
							win = g_active_player;
							return win;
							//return;
						}
					}
				}
				// CHECK VERTICALEMENT
				else if (g_matrice[col][line+1] == g_active_player){
					if (g_matrice[col][line+2] == g_active_player){
						if (g_matrice[col][line+3] == g_active_player){
							printf("\nJoueur %d a gagn� verticalement\n", g_active_player);
							printf("Coordonees de debut : [x : %d y : %d]\n", col, line);
							printf("Coordonees de fin : [x : %d y : %d]\n", col, line+3);
							/*int8_t player_winner = 0;
							player_winner = g_active_player;
							coordinate_t coordinate_token1 = {col, line};
							coordinate_t coordinate_token2 = {col, line+1};
							coordinate_t coordinate_token3 = {col, line+2};
							coordinate_t coordinate_token4 = {col, line+3};
							char victory_type;
							victory_type = 'v';
							winner_t winner = { player_winner, coordinate_token1, coordinate_token2,
									coordinate_token3, coordinate_token4, victory_type};
							return winner;*/
							win = g_active_player;
							return win;
							//return;
						}
					}
				}
				// CHECK DIAGONALEMENT BAS GAUCHE
				else if (g_matrice[col-1][line+1] == g_active_player){
					if (g_matrice[col-2][line+2] == g_active_player){
						if (g_matrice[col-3][line+3] == g_active_player){
							printf("\nJoueur %d a gagn� en diagonale bas gauche\n", g_active_player);
							printf("Coordonees de debut : [x : %d y : %d]\n", col, line);
							printf("Coordonees de fin : [x : %d y : %d]\n", col-3, line+3);
							/*int8_t player_winner = 0;
							player_winner = g_active_player;
							coordinate_t coordinate_token1 = {col, line};
							coordinate_t coordinate_token2 = {col-1, line+1};
							coordinate_t coordinate_token3 = {col-2, line+2};
							coordinate_t coordinate_token4 = {col-3, line+3};
							char victory_type;
							victory_type = 'd';
							winner_t winner = { player_winner, coordinate_token1, coordinate_token2,
									coordinate_token3, coordinate_token4, victory_type};
							return winner;*/
							win = g_active_player;
							return win;
							//return;
						}
					}
				}
				// CHECK DIAGONALEMENT BAS DROITE
				else if (g_matrice[col+1][line+1] == g_active_player){
					if (g_matrice[col+2][line+2] == g_active_player){
						if (g_matrice[col+3][line+3] == g_active_player){
							printf("Joueur %d a gagn� en diagonale bas droite\n", g_active_player);
							printf("Coordonees de debut : [x : %d y : %d]\n", col, line);
							printf("Coordonees de fin : [x : %d y : %d]\n", col+3, line+3);
							/*int8_t player_winner = 0;
							player_winner = g_active_player;
							coordinate_t coordinate_token1 = {col, line};
							coordinate_t coordinate_token2 = {col+1, line+1};
							coordinate_t coordinate_token3 = {col+2, line+2};
							coordinate_t coordinate_token4 = {col+3, line+3};
							char victory_type;
							victory_type = 'd';
							winner_t winner = { player_winner, coordinate_token1, coordinate_token2,
									coordinate_token3, coordinate_token4, victory_type};
							return winner;*/
							win = g_active_player;
							return win;
							//return;
						}
					}
				}
			}
		}
	}
	return win;
	//return;
	/*gp4_check_winner_horizontally();
	gp4_check_winner_verticaly();
	gp4_check_winner_diagonally_left();
	gp4_check_winner_diagonally_right();*/
}

