#ifndef MY_PROJECT_FSQ
#define MY_PROJECT_FSQ

#include <stddef.h>

#define PEEK_ERROR ((size_t)-1)

typedef struct fsq fsq_t; 

enum status
{
    SUCCESS = 0,
    QUEUE_IS_FULL = -1,
    QUEUE_IS_EMPTY = -2
};

fsq_t *FSQCreate(size_t size, sem_t *sem);
int FSQEnqueue(fsq_t *q, int input);
int FSQDequeue(fsq_t *q);
int FSQPeek(fsq_t *q);
int FSQIsEmpty(fsq_t *q);
void FSQDestroy(fsq_t *q);

#endif


 