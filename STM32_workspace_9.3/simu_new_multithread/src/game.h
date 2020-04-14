/*
 * game.h
 *
 *  Created on: 9 avr. 2020
 *      Author: marc
 */

#ifndef GAME_H_
#define GAME_H_

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>

#define TAB_SIZE 7
#define PLAYER_COLOR blue
#define BACKGROUND black
#define MAX_NUMBER 9
#define MIN_NUMBER 0
#define INIT_OK 1
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4
#define MSG_LENGHT 1

typedef struct User_input user_input;
struct User_input {
	int value;
	user_input *next;
};

typedef struct Queue queue;
struct Queue {
	user_input *first;
	user_input *last;
	pthread_mutex_t mutex;
	sem_t semaphore;
};

typedef struct {
	int RValue;
	int GValue;
	int BValue;
} color;

typedef struct {
	color board[TAB_SIZE][TAB_SIZE];
	int init;
} Matrix;

static color white = { 255, 255, 255 }, green = { 0, 255, 0 }, blue = { 0, 0,
		255 }, red = { 255, 0, 0 }, purple = { 255, 0, 255 }, yellow = { 255,
		255, 0 }, black = { 0, 0, 0 };

sem_t sem_button;
sem_t sem_display;
queue *queue_push_app;
queue *queue_app_display;

/* THREAD */
void *user_button(void *arg);
void *show_board(void *arg);
void *application(void *arg);
/* FUNCTION */
void set_number(int nbr);
void init_matrix(void);
queue *queue_init(void);
void push(queue *queue, char *input);
int pop_element(queue *queue, char *value);

#endif /* GAME_H_ */