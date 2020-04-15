/*
 * fifo.h
 *
 *  Created on: 7 Apr 2020
 *      Author: cedric
 */

#ifndef FIFO_H_
#define FIFO_H_

#include<pthread.h>
#include<semaphore.h>

typedef struct Element
{
    int number; // contenu de mon element
    struct Element *next; // pointeur vers l'element suivant
}Element;


typedef struct Queue
{
    Element *head; // pointeur vers le 1er �l�ment
    Element *tail; // pointeur vers le dernier �l�ment
	pthread_mutex_t mutex;
	sem_t semaphore;
}Queue;

typedef enum {left, right, up, down} movement_t;

typedef enum {player_1, player_2} player_t;

sem_t semaphore_input;
sem_t semaphore_display;
Queue p_queue_read;
Queue p_queue_display;

void init_queue(struct Queue *queue);
void add_element(struct Queue *queue, int number);
int pop_element(struct Queue *queue);
void print_queue(struct Queue *queue);

#endif /* FIFO_H_ */
