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
	 * gp4_top_play_token();			---- play token
	 * gp4_check_winner();				---- check_winner
	 */


	gp4_init();
	gp4_display();
	gp4_top_move_token_right();
	gp4_display();
	gp4_top_move_token_left();
	gp4_display();
	gp4_top_move_token_left();
	gp4_display();
	coordinate_t pos = gp4_top_play_token();
	gp4_display();
	gp4_next_player();
	gp4_display();
	gp4_top_play_token();
	gp4_display();
	gp4_next_player();
	gp4_display();
	gp4_top_play_token();
	gp4_display();
	gp4_next_player();
	gp4_display();
	gp4_top_move_token_right();
	gp4_display();
	gp4_top_play_token();
	gp4_display();
	gp4_next_player();
	gp4_display();
	gp4_top_play_token();
	gp4_display();
	gp4_check_winner();
}


int main(void){
	debug_setlevel(2);

	gp4_scenar_test();




	return 0;
}
