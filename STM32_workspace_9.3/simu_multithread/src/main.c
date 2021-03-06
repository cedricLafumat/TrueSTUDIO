#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
#include"game.h"
#include"leds_control.h"
#include "fifo.h"



int main(void){
	openLink();
	pthread_t thread_read;
	pthread_t thread_app;
	pthread_t thread_send;
	init_queue(&p_queue_read);
	init_queue(&p_queue_display);
	sem_init(&semaphore_input, 0, 0);
	sem_init(&semaphore_display, 0, 0);

	printf("Creation thread de lecture\n");
	pthread_create(&thread_read, NULL, read_input, NULL);
	printf("Creation thread d'application\n");
	pthread_create(&thread_app, NULL, application, NULL);
	printf("Creation thread d'envoi\n");
	pthread_create(&thread_send, NULL, show_board, NULL);


	(void)pthread_join(thread_read, NULL);
	(void)pthread_join(thread_app, NULL);
	(void)pthread_join(thread_send, NULL);

	sem_destroy(&semaphore_input);
	sem_destroy(&semaphore_display);
	closeLink();
	return 0;
}
