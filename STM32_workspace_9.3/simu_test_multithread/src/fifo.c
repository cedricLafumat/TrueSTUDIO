/*
 * fifo.c
 *
 *  Created on: 7 Apr 2020
 *      Author: cedric
 */

#include <stdio.h>
#include <stdlib.h>
#include "fifo.h"
#include<pthread.h>

static pthread_mutex_t mutex_queue;

void init_queue(struct Queue *queue){
	queue-> head = NULL;
	queue-> tail = NULL;
}

void push(queue *queue, char *input) {
	user_input *new_input = malloc(sizeof(*new_input));
	if (new_input == NULL) {
		printf("erreur alloc mÃ©moire push\n");
	}
	new_input->value = *input;
	new_input->next = NULL;
	pthread_mutex_lock(&queue->mutex);
	if (queue->first != NULL) {
		user_input *first_input = queue->last;
		first_input->next = new_input;
		queue->last = new_input;
	} else {
		queue->first = new_input;
		queue->last = new_input;
	}
	pthread_mutex_unlock(&queue->mutex);
}

int pop_element(struct Queue *queue){
	if (queue == NULL)
	{
		exit(EXIT_FAILURE);
		// a changer, mettre un return si ça a fonctionner ou non
	}

	int content_element = 0;

	if (queue->head != NULL){  //  verification qu'il y ai un element à enlever
		pthread_mutex_lock(&mutex_queue);
		Element *element_to_remove = queue->head; // mettre la tete de la pile dans element_to_remove
		content_element = element_to_remove->number; // je recupère le contenu de l'element
		queue->head = element_to_remove->next; // l'element suivant devient la tete
		pthread_mutex_unlock(&mutex_queue);
		free(element_to_remove); // libere l'espace alloue pour cet element
	}
	return content_element;
}


void print_queue(struct Queue *queue){

	if (queue == NULL)
	{
		exit(EXIT_FAILURE);
		// a changer, mettre un return si ça a fonctionner ou non
	}

	Element *element_to_print = queue->head;
	printf("J'affiche ma liste dans l'ordre\n");
	while (element_to_print != NULL){ // tant que j'ai un element à afficher
		printf("%d -> ", element_to_print->number); // j'affiche le contenu de mon element
		element_to_print = element_to_print->next; // l'element a afficher prend l'adresse du suivant
	}
	printf("NULL\n");
}

