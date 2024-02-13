#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include <stdio.h> /*print*/
#include <semaphore.h> /*sem_t*/

#include "fsq.h"

struct fsq
{
    size_t size;
    size_t max_size;
    int *array;
    sem_t *sem;
    int front;
};

/************************ Functions ************************/

fsq_t *FSQCreate(size_t size, sem_t *sem)
{
    fsq_t *fsq = malloc(sizeof(fsq_t));

    if (NULL == fsq)
    {
        return NULL;
    }

    fsq->size = 0;
    fsq->max_size = size;
    fsq->front = 0;
    fsq->sem = sem;
    fsq->array = calloc(size, sizeof(int));

    if (NULL == fsq->array)
    {
        free(fsq);
        return NULL;
    }
    return fsq;
}

void FSQDestroy(fsq_t *q)
{
    assert(NULL != q);

    free(q->array);
    free(q);
}

int FSQEnqueue(fsq_t *q, int input)
{
    int index = 0;
    assert(NULL != q);
    
    if (q->size >= q->max_size)
    {
        return QUEUE_IS_FULL;
    }

    index = (q->size + q->front);
    q->array[index] = input;
    ++q->size;
    sem_post(q->sem); 
    return SUCCESS;
}

int FSQDequeue(fsq_t *q)
{
    assert(NULL != q);
    
    if (FSQIsEmpty(q))
    {
        return QUEUE_IS_EMPTY;
    }
    sem_wait(q->sem); 
    q->front = (q->front + 1);
    --q->size;
    return SUCCESS;
}

int FSQPeek(fsq_t *q)
{
    assert(NULL != q);
    if (FSQIsEmpty(q))
    {
        return QUEUE_IS_EMPTY;
    }
    return q->array[q->front];
}

int FSQIsEmpty(fsq_t *q)
{
    assert(NULL != q);

    return (0 == q->size);
}