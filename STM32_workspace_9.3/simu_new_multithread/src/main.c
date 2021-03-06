#include"leds_control.h"
#include"game.h"
#include"debug.h"
//#include<pthread.h>
//#include<semaphore.h>

int main(void) {

	debug_setlevel(5);

	queue_push_app = queue_init();
	queue_app_display = queue_init();

	printf("intialisation mutex\n");
	pthread_mutex_init(&queue_push_app->mutex, NULL);
	pthread_mutex_init(&queue_app_display->mutex, NULL);

	printf("initialisation semaphores\n");
	sem_init(&sem_button, 0, 0);
	sem_init(&sem_display, 0, 0);
	printf("initialisation de la matrice\n");
	init_matrix();

	printf("ouverture liaison port s�rie\n");
	openLink();
	pthread_t push;
	pthread_t display;
	pthread_t app;
	if (pthread_create(&push, NULL, user_button, NULL) != 0) {
		printf("ECHEC CREATION THREAD Push\n");
	} else {
		printf("cr�ation thread reception boutons\n"); // READ
	}
	if (pthread_create(&display, NULL, show_board, NULL) != 0) {
		printf("ECHEC CREATION THREAD show_board\n");
	} else {
		printf("cr�ation thread affichage matrice\n"); // WRITE

	}
	if (pthread_create(&app, NULL, application, NULL) != 0) {
		printf("ECHEC CREATION THREAD application\n");
	} else {
		printf("cr�ation thread application\n"); // POP
	}
	pthread_join(push, NULL);
	pthread_join(display, NULL);
	pthread_join(app, NULL);
	closeLink();
}
