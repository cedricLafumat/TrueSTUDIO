#ifndef H_FILE
#define H_FILE

//typedef struct Element Element;
struct Element
{
    int number;
    struct Element *next;
};

//typedef struct Queue Queue;
struct Queue
{
    struct Element *head; // pointeur vers le 1er élément
    struct Element *tail; // pointeur vers le dernier élément
};

void init_queue(struct Queue *queue);
void add_element(struct Queue *queue, int number);
int pop_element(struct Queue *queue);
void print_queue(struct Queue *queue);


#endif
