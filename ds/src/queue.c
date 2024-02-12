#include <stdlib.h> /*malloc*/
#include <stdio.h> /*printf*/
#include <assert.h> /*assert*/

#include "linked_list.h" /*SLL function*/
#include "queue.h"

struct queue 
{
    sll_t *queue;
};

struct SingleLinkedList
{
	node_t *head;
	node_t *tail;
};

/************************ Functions ************************/

queue_t *QueueCreate(void)
{
	queue_t *queue = malloc(sizeof(queue_t));
	if (NULL == queue)
    {
        printf("Memory allocation for the queue faild \n");
        return NULL;
    }
    
    queue->queue = SLLCreate();
    
    return queue; 
}
	
void QueueDestroy(queue_t *queue)
{
	assert(NULL != queue);
	
	SLLDestroy(queue->queue);
	free(queue);
}

int QueueIsEmpty(const queue_t *queue)
{
	assert(NULL != queue);
	return SLLIsEmpty(queue->queue);
}

int QueueEnqueue(queue_t *queue, void *data)
{
	assert(NULL != queue);
	return (NULL != SLLInsertBefore(queue->queue->tail, data));
}

void *QueuePeek(const queue_t *queue)
{
	assert(NULL != queue);
	return SLLGetData(queue->queue->head);
}

void QueueDequeue(queue_t *queue)
{
	assert(NULL != queue);
	SLLRemove(queue->queue->head);
}

size_t QueueSize(const queue_t *queue)
{
	assert(NULL != queue);

    return SLLCount(queue->queue);
}

queue_t *QueueAppend(queue_t *dest, queue_t *src)
{
	assert(NULL != dest);
	assert(NULL != src);
	
	dest->queue = SLLAppend(dest->queue, src->queue);
	
	return dest;	
}

