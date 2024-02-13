#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include <stdio.h> /*print*/

#include "fsq2.h"

struct fsq
{
    size_t max_size;
    int *array;
    pthread_mutex_t *front_mtx;
    pthread_mutex_t *rear_mtx;
    int front;
    int rear;
};

/************************ Functions ************************/

fsq_t *FSQCreate(size_t size, pthread_mutex_t *front_mutex,  pthread_mutex_t *rear_mutex)
{
    fsq_t *fsq = malloc(sizeof(fsq_t));

    if (NULL == fsq)
    {
        return NULL;
    }

    fsq->max_size = size;
    fsq->rear = 0;
    fsq->front = 0;
    fsq->front_mtx = front_mutex;
    fsq->rear_mtx = rear_mutex;
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
    assert(NULL != q);
    
    pthread_mutex_lock(q->rear_mtx);
    q->array[q->rear] = input;
    ++q->rear;
    pthread_mutex_unlock(q->rear_mtx);
    
    return SUCCESS;
}

int FSQDequeue(fsq_t *q)
{
    int ret = 0;
    assert(NULL != q);
    
    pthread_mutex_lock(q->front_mtx);
    ret = q->array[q->front];
    ++q->front;
    pthread_mutex_unlock(q->front_mtx);

    return ret;
}

int FSQPeek(fsq_t *q)
{
    assert(NULL != q);
    
    return q->array[q->front];
}

