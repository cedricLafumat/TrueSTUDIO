#include<stdio.h>
#include "f1.h"

//int MA_POURRIE_GLOBALE=12;

int main(void){

//	MA_POURRIE_GLOBALE++;
	f11();
	f12();

	f1_glob++;
	printf("main:f1_glob = %d (addr=%p)\n", f1_glob, & f1_glob);

	f11();
	f12();

	printf("Hello World!\n");
	fflush(stdout);

	return 0;
}
