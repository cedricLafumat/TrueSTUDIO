#include<stdio.h>
#include"game_p4.h"
#include"debug.h"



void gp4_scenar_test(void){
	/*
	 * -------------------- LIST FUNCTION ------------------------------
	 * gp4_init();  					---- init matrix
	 * gp4_display();					---- print matrix
	 * gp4_next_player();				---- change player
	 * gp4_top_move_token_left();		---- move left
	 * gp4_top_move_token_right();		---- move right
	 * pos = gp4_top_play_token();		---- play token
	 * gp4_check_winner();				---- check_winner
	 *
	 * ------------------ COMBINAISON PLAY TOKEN
	 * 	pos = gp4_top_play_token();
	 * 	gp4_display();
	 * 	gp4_check_winner();
	 * 	gp4_next_player();
	 *
	 *
	 */


	/*gp4_init();
	gp4_display();
	coordinate_t token_coordinates;
	gp4_top_move_token_right();
	token_coordinates = gp4_top_play_token();
	gp4_top_move_token_left();
	token_coordinates = gp4_top_play_token();
	gp4_top_move_token_right();
	token_coordinates = gp4_top_play_token();
	gp4_top_move_token_left();
	token_coordinates = gp4_top_play_token();
	gp4_top_move_token_right();
	token_coordinates = gp4_top_play_token();
	gp4_top_move_token_left();
	token_coordinates = gp4_top_play_token();
	gp4_top_move_token_right();
	token_coordinates = gp4_top_play_token();*/

	coordinate_t token_coordinates;
	int move;
	printf("\n(4) gauche // (5) validation // (6) droite : ");
	scanf("%d", &move);
	fflush(stdout);
	if (move == 4){
		gp4_top_move_token_left();
	}
	if(move == 5){
		token_coordinates = gp4_top_play_token();
	}
	if (move == 6){
		gp4_top_move_token_right();
	}

}


int main(void){
	debug_setlevel(4);

	gp4_init();
	gp4_display();
	while(1){
		gp4_scenar_test();
	}


	return 0;
}
