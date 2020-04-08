#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "fifo.h"
#include<semaphore.h>
#include<pthread.h>


static sem_t semaphore;


void *thread_add(void *arg){
	Queue *p_queue = arg;
	for (int i = 0; i < 20; i++){
		add_element(p_queue, i);
		sem_post(&semaphore);
		sleep(1);
	}
	pthread_exit(NULL);
}

void *thread_del(void *arg){
	Queue *p_queue = arg;
	while(1){
		sem_wait(&semaphore);
		printf("Je supprime l'element %d // adresse %p\n", pop_element(p_queue), p_queue->head);
	}
	pthread_exit(NULL);
}


int main(void)
{
	pthread_t thread_push;
	pthread_t thread_pop;
	struct Queue queue;
	init_queue(&queue);
	sem_init(&semaphore, 0, 0);

	pthread_create(&thread_push, NULL, thread_add, &queue);
	pthread_create(&thread_pop, NULL, thread_del, &queue);

	(void) pthread_join(thread_push, NULL);
	(void) pthread_join(thread_pop, NULL);

	sem_destroy(&semaphore);


	/*add_element(&queue, 1);
	add_element(&queue, 2);
	add_element(&queue, 3);
	add_element(&queue, 5);
	add_element(&queue, 8);
	add_element(&queue, 13);
	add_element(&queue, 21);
	add_element(&queue, 34);
	print_queue(&queue);
	printf("Je supprime l'element %d // adresse %p\n", pop_element(&queue), queue.head);
	printf("Je supprime l'element %d // adresse %p\n", pop_element(&queue), queue.head);
	printf("Je supprime l'element %d // adresse %p\n", pop_element(&queue), queue.head);
	printf("Je supprime l'element %d // adresse %p\n", pop_element(&queue), queue.head);
	printf("Je supprime l'element %d // adresse %p\n", pop_element(&queue), queue.head);
	printf("Je supprime l'element %d // adresse %p\n", pop_element(&queue), queue.head);
	print_queue(&queue);
	add_element(&queue, 55);
	add_element(&queue, 89);
	print_queue(&queue);*/

	return 0;
}
