
#include <stdlib.h> /* malloc */
#include <assert.h> /*assert*/

#include "heap.h"
#include "pq.h"

struct pq
{
	heap_t *heap;
};

/************************ Functions ************************/
pq_t *PQCreate(int (*priority_func)(const void *lhs, const void *rhs))
{
	pq_t *pq = malloc(sizeof(pq_t));
	
	assert(NULL != priority_func);
	
    if (NULL == pq)
    {
        return NULL;
    }
  
    pq->heap = HeapCreate(priority_func);
    
    if (NULL == pq->heap)
	{
		free(pq);
        return NULL;
	}
	
    return pq;
}

void PQDestroy(pq_t *pq)
{
	assert(NULL != pq);
	
	HeapDestroy(pq->heap);
	free(pq);
}

int PQEnqueue(pq_t *pq, void *data)
{
	assert(NULL != pq);
	
	return HeapPush(pq->heap, data);
}

void PQDequeue(pq_t *pq)
{
	assert(NULL != pq);
	
	HeapPop(pq->heap);
}

int PQIsEmpty(const pq_t *pq)
{
	assert(NULL != pq);
	
	return HeapIsEmpty(pq->heap);
}

size_t PQSize(const pq_t *pq)
{
	assert(NULL != pq);
	
	return HeapSize(pq->heap);
}

void *PQPeek(const pq_t *pq)
{
	assert(NULL != pq);
	
	return HeapPeek(pq->heap);
}

void PQClear(pq_t *pq)
{
	assert(NULL != pq);
	
	while (!PQIsEmpty(pq))
	{
		HeapPop(pq->heap);
	}
}

void *PQErase(pq_t *pq, int (*is_match)(const void *data, const void *param), void *param)
{
	assert(NULL != pq);
	assert(NULL != is_match);
	assert(NULL != param);

	return HeapRemove(pq->heap, is_match ,param);
}
