#include<stdio.h>
#include"game_p4.h"
#include"debug.h"

/*
 * -------------------- LIST FUNCTION ------------------------------
 * gp4_init();  					---- init matrix
 * gp4_display();					---- print matrix
 * gp4_next_player();				---- change player
 * gp4_top_move_token_left();		---- move left
 * gp4_top_move_token_right();		---- move right
 * gp4_top_play_token();			---- play token
 * gp4_check_winner();				---- check_winner
 *
 * ------------------ COMBINAISON PLAY TOKEN
 * 	gp4_top_play_token();
 * 	gp4_display();
 * 	gp4_check_winner();
 * 	gp4_next_player();
 *
 */

int gp4_pilot(void){

	int move;
	winner_t winner;
	int state_party = 0;
	pos_token_t pilot_move;
	printf("\n(4) gauche // (5) validation // (6) droite : ");
	scanf("%d", &move);
	if (move == 4){
		pilot_move = gp4_top_move_token_left();
		if (pilot_move.is_ok == false){
			state_party = 1;
			return state_party;
		}
		gp4_display();
	}
	if(move == 5){
		gp4_top_play_token();
		gp4_display();
		winner = gp4_check_winner();
		if (winner.status == live){
			gp4_next_player();
			gp4_display();
		}
		else{
			state_party = 1;
		}
	}
	if (move == 6){
		pilot_move = gp4_top_move_token_right();
		if (pilot_move.is_ok == false){
			state_party = 1;
			return state_party;
		}
		gp4_display();
	}
	return state_party;

}


int main(void){
	debug_setlevel(3);

	int choice = 1;
	while (choice == 1){
		printf("Nouvelle partie !\n\n");
		int state_party = 0;
		gp4_init();
		gp4_display();
		while(state_party == 0){
			state_party = gp4_pilot();
		}
		printf("Partie fini !!\n");
		printf("Voulez-vous recommencer une partie? (0) non  / (1) oui : ");
		scanf("%d", &choice);
	}
	printf("\nFin du jeu, passage en mode animation");

	return 0;
}
