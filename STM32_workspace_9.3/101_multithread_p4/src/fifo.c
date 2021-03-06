/*
 * fifo.c
 *
 *  Created on: 7 Apr 2020
 *      Author: cedric
 */

#include <stdio.h>
#include <stdlib.h>
#include "fifo.h"
#include <pthread.h>
#include <string.h>

static pthread_mutex_t mutex_element;


void init_queue(struct Queue *queue){
	queue-> head = NULL;
	queue-> tail = NULL;
}

void add_element(struct Queue *queue, char *command){

	Element *new_element = malloc(sizeof(*new_element));

	pthread_mutex_lock(&mutex_element);

	memcpy(new_element->command, command, SIZE_COMMAND);
	new_element->next = NULL;


	if(queue->head != NULL){ // La liste a au moins 1 �l�ment

		// --------------- FIFO
		Element *actual_tail = queue->tail;
		actual_tail->next = new_element;
		queue->tail = new_element;

		// --------------- LIFO
//		Element *actual_head = queue->head;
//		new_element->next = actual_head;
//		queue->head = new_element;

	}
	else{
		queue->head = new_element;
		queue->tail = new_element;
	}

	pthread_mutex_unlock(&mutex_element);

}

int pop_element(struct Queue *queue, char *command){
	if (queue == NULL)
	{
		return -1;
	}

	//char command[SIZE_COMMAND];

	if (queue->head != NULL){
		pthread_mutex_lock(&mutex_element);
		Element *element_to_remove = queue->head;
		memcpy(command, element_to_remove->command, SIZE_COMMAND);
		queue->head = element_to_remove->next;
		pthread_mutex_unlock(&mutex_element);
		free(element_to_remove);
	}
	return 0;
}


/*void print_queue(struct Queue *queue){

	Element *element_to_print = queue->head;
	printf("J'affiche ma liste dans l'ordre\n");
	while (element_to_print != NULL){
		printf("%c -> ", element_to_print->command[0]);
		element_to_print = element_to_print->next;
	}
	printf("NULL\n");
}*/

