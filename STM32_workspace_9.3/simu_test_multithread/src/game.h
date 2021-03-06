/*
 * game.h
 *
 *  Created on: 14 Apr 2020
 *      Author: cedric
 */

#ifndef GAME_H_
#define GAME_H_

#define TabSize 7
#define PLAYER_COLOR White
#define BACKGROUND Black
#define INIT_OK 1
#define MSG_LENGHT 1

typedef struct{
	int RValue;
	int GValue;
	int BValue;
}RGB;

typedef struct {
	RGB board[TabSize][TabSize];
	int init;
} Matrix;


#endif /* GAME_H_ */
