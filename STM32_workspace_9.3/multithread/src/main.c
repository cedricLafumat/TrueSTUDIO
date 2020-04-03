#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

static int g_tab[5];
pthread_mutex_t mutex;



/*void *print_hello_world(void *arg){
	//int cpt = 0;
	//while(cpt < 10){
	//	cpt += 1;
		printf("Hello World! \n");
	//	sleep(2);
	//}
	(void) arg;
	pthread_exit(NULL);
}

void *print_world_is_mine(void *arg){
	//int cpt = 0;
	//while(cpt < 10){
	//	cpt += 1;
		printf("The world is mine \n");
	//	sleep(2);
	//}
	(void) arg;
	pthread_exit(NULL);
}*/


void *write_in_tab(void *arg){
	int val = 0;
	pthread_mutex_lock(&mutex);
	for (int cpt = 0; cpt<5; cpt ++){
		g_tab[cpt] = val;
		printf("Ecriture de la valeur %d dans la case [%d] du tableau\n", val, cpt);
		val += 10;
		sleep(1);
	}
	pthread_mutex_unlock (&mutex);
	(void) arg;
	pthread_exit(NULL);
}

void *print_tabl(void *arg){
	pthread_mutex_lock(&mutex);
	for (int cpt = 0; cpt<5; cpt++){
		printf("J'affiche la valeur de la case [%d] du tableau : %d\n", cpt, g_tab[cpt]);
		sleep(1);
	}
	pthread_mutex_unlock (&mutex);
	(void) arg;
	pthread_exit(NULL);
}

int main(void){

	/*pthread_t thread1;
	pthread_t thread2;

	pthread_create(&thread1, NULL, print_hello_world, NULL);
	sleep(1);
	pthread_create(&thread2, NULL, print_world_is_mine, NULL);*/

	pthread_t write_tab;
	pthread_t print_tab;

	pthread_mutex_init(&mutex, NULL);
	pthread_create(&write_tab, NULL, write_in_tab, NULL);
	pthread_create(&print_tab, NULL, print_tabl, NULL);


	(void)pthread_join (write_tab, NULL);
	(void)pthread_join (print_tab, NULL);
	return 0;
}
