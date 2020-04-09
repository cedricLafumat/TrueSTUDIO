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

void add_element(struct Queue *queue, int val_number){
	//creation d'une structure 'new_element' de type Element et allocation d'un espace mémoire de la taille de la structure

	// a tester avec sizeof Element (qui est la taille de la struct)
	Element *new_element = malloc(sizeof(*new_element));
	if(queue == NULL){
		exit(EXIT_FAILURE);
		// a changer, mettre un return si ça a fonctionner ou non
	}
	pthread_mutex_lock(&mutex_queue);

	new_element->number = val_number;
	new_element->next = NULL;

	if(queue->head != NULL){ // La liste a au moins 1 élément

		// --------------- FIFO
		Element *actual_tail = queue->tail; // creation d'une structure 'actual_tail' pour avec les donnees du tail (dernier element)
		actual_tail->next = new_element; // je mets le pointeur de l'element actuel vers le nouvel element
		queue->tail = new_element; // le nouvel element devient le tail de la liste

		// --------------- LIFO
//		Element *actual_head = queue->head;
//		new_element->next = actual_head;
//		queue->head = new_element;

	}
	else{ // Le pointeur vers le 1er élément n'existe pas, ma liste est vide
		queue->head = new_element;
		queue->tail = new_element;
	}
	printf("J'ajoute %d à ma liste // adresse %p\n", val_number, queue->tail);
	pthread_mutex_unlock(&mutex_queue);

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

