#include <stdio.h> /*perror*/
#include <assert.h> /*assert*/
#include <errno.h> /*errno*/
#include <stdlib.h> /* malloc */


#include "sorted_list.h"
#include "pq.h"

struct pq
{
	sol_t *sorted_list;
};

/************************ Functions ************************/

pq_t *PQCreate(int (*priority_func)(const void *lhs, const void *rhs))
{
	pq_t *pq = malloc(sizeof(pq_t));
	
	assert(NULL != priority_func);
	
    if (NULL == pq)
    {
    	errno = ENOMEM; /*not enough memory available*/
        perror("Memory allocation:");
        return NULL;
    }
  
    pq->sorted_list = SortedListCreate(priority_func);
    
    if (NULL == pq->sorted_list)
	{
		free(pq);
		pq = NULL;
	}
	
    return pq;
}

void PQDestroy(pq_t *pq)
{
	assert(NULL != pq);
	
	SortedListDestroy(pq->sorted_list);
	free(pq);
}

int PQEnqueue(pq_t *pq, void *data)
{
	assert(NULL != pq);
	
	return SortedListIsSameIter(SortedListInsert(pq->sorted_list, data), SortedListEndIter(pq->sorted_list));
}

void PQDequeue(pq_t *pq)
{
	assert(NULL != pq);
	
	SortedListPopFront(pq->sorted_list);
}

int PQIsEmpty(const pq_t *pq)
{
	assert(NULL != pq);
	
	return SortedListIsEmpty(pq->sorted_list);
}

size_t PQSize(const pq_t *pq)
{
	assert(NULL != pq);
	
	return SortedListSize(pq->sorted_list);
}

void *PQPeek(const pq_t *pq)
{
	assert(NULL != pq);
	
	return SortedListGetData(SortedListBeginIter(pq->sorted_list));
}

void PQClear(pq_t *pq)
{
	assert(NULL != pq);
	
	while (!PQIsEmpty(pq))
	{
		SortedListPopFront(pq->sorted_list);
	}
}

void *PQErase(pq_t *pq, int (*is_match)(const void *data, const void *param), void *param)
{
	void *data_to_return = NULL;
	sol_iterator_t iterator = {0};
	
	assert(NULL != pq);
	assert(NULL != is_match);
	
	iterator = SortedListFindIf(SortedListBeginIter(pq->sorted_list), SortedListEndIter(pq->sorted_list), is_match, param);
	
	if (!SortedListIsSameIter(iterator, SortedListEndIter(pq->sorted_list)))
	{
		data_to_return = SortedListGetData(iterator);
		SortedListRemove(iterator);
	}
	
	return data_to_return;
}

pq_t *PQMerge(pq_t *pq_dest, pq_t *pq_src)
{
	assert(NULL != pq_dest);
	assert(NULL != pq_src);
	
	SortedListMerge(pq_dest->sorted_list, pq_src->sorted_list);
	
	return pq_dest;
}


