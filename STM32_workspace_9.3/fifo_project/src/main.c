#include <stdio.h>
#include <stdlib.h>
#include "file.h"

int main(void)
{
	struct Queue queue;
	init_queue(&queue);
	add_element(&queue, 1);
	add_element(&queue, 2);
	add_element(&queue, 3);
	add_element(&queue, 5);
	add_element(&queue, 8);
	add_element(&queue, 13);
	add_element(&queue, 21);
	add_element(&queue, 34);
	print_queue(&queue);
	printf("Je supprime l'element %d\n", pop_element(&queue));
	printf("Je supprime l'element %d\n", pop_element(&queue));
	printf("Je supprime l'element %d\n", pop_element(&queue));
	print_queue(&queue);

    return 0;
}
