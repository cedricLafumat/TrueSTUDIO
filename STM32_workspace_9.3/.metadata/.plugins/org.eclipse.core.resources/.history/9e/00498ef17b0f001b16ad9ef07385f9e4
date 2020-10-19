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

#define SIZE_COMMAND 10

typedef struct Element
{
    char command[SIZE_COMMAND]; // contenu de mon element
    struct Element *next; // pointeur vers l'element suivant
}Element;


typedef struct Queue
{
    Element *head; // pointeur vers le 1er élément
    Element *tail; // pointeur vers le dernier élément
	pthread_mutex_t mutex;
	sem_t semaphore;
}Queue;

sem_t semaphore_input;
sem_t semaphore_display;
Queue p_queue_read;
Queue p_queue_display;

typedef enum {left, right, up, down} movement_t;



void init_queue(struct Queue *queue);
void add_element(struct Queue *queue, char *command);
int pop_element(struct Queue *queue, char* command);
void print_queue(struct Queue *queue);

#endif /* FIFO_H_ */
