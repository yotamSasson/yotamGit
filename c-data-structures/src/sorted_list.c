#include <stdio.h> /*perror*/
#include <assert.h> /*assert*/
#include <errno.h> /*errno*/
#include <stdlib.h> /* malloc */

#include "sorted_list.h"

struct sorted_linked_list
{
	dll_t *list;
	cmp_func_st user_func;
};

typedef struct  user_func_wrapper
{
	sol_t *sol;
	void *data;
}user_func_wrapper_t;

static int WrapUserFunc(const void *data, const void *wrapper);

/************************ Functions ************************/

sol_t *SortedListCreate(cmp_func_st user_func)
{
	sol_t *sol = malloc(sizeof(sol_t));
	
	assert(NULL != user_func);
	
    if (NULL == sol)
    {
    	errno = ENOMEM; /*not enough memory available*/
        perror("Memory allocation:");
        return NULL;
    }
    
	sol->list = DLLCreate();
	if (NULL == sol->list)
    {
   		free(sol);
		errno = ENOMEM; /*not enough memory available*/
        perror("Memory allocation:");
        return NULL;
    }
    sol->user_func = user_func;
    
    return sol;   
}

void SortedListDestroy(sol_t *sol)
{
	 assert(NULL != sol);
	 
	 DLLDestroy(sol->list);
	 free(sol);
}

sol_iterator_t SortedListInsert(sol_t *sol, void *data)
{
	sol_iterator_t ret_iter = {0};
	user_func_wrapper_t wrapper = {0};
	
	assert(NULL != sol);
	
	wrapper.sol = sol;
 	wrapper.data = data;
 	
	ret_iter = SortedListFindIf(SortedListBeginIter(sol), SortedListEndIter(sol), WrapUserFunc ,&wrapper);
	ret_iter.DLLIterator = DLLInsert(ret_iter.DLLIterator, data);
	
	#ifndef NDEBUG
	ret_iter.dll = sol->list;
	#endif
	
	return ret_iter;
}

sol_iterator_t SortedListRemove(sol_iterator_t iterator)
{
	assert(NULL != iterator.DLLIterator);
	
	iterator.DLLIterator = DLLRemove(iterator.DLLIterator);
	return iterator;
}

sol_iterator_t SortedListBeginIter(const sol_t *sol)
{
	sol_iterator_t iterator = {0};
	
	assert(NULL != sol);
	
	iterator.DLLIterator = DLLBeginIter(sol->list);
	
	#ifndef NDEBUG
	iterator.dll = sol->list;
	#endif	
	
	return iterator;
}

int SortedListIsEmpty(const sol_t *sol)
{
	assert(NULL != sol);
	return DLLIsEmpty(sol->list);
}

size_t SortedListSize(const sol_t *sol)
{
	assert(NULL != sol);
	return DLLCount(sol->list);
}

sol_iterator_t SortedListEndIter(const sol_t *sol)
{
	sol_iterator_t iterator = {0};
	
	assert(NULL != sol);
	
	iterator.DLLIterator = DLLEndIter(sol->list);
	
	#ifndef NDEBUG
	iterator.dll = sol->list;
	#endif	
	
	return iterator;
}

void *SortedListGetData(sol_iterator_t iterator)
{
	assert(NULL != iterator.DLLIterator);
	return DLLGetData(iterator.DLLIterator);
}

sol_iterator_t SortedListNextIter(sol_iterator_t iterator)
{
	assert(NULL != iterator.DLLIterator);
	
	iterator.DLLIterator = DLLNextIter(iterator.DLLIterator);
	return iterator;
}

sol_iterator_t SortedListPrevIter(sol_iterator_t iterator)
{
	assert(NULL != iterator.DLLIterator);
	
	iterator.DLLIterator = DLLPrevIter(iterator.DLLIterator);
	return iterator;
}

int SortedListIsSameIter(sol_iterator_t iter1, sol_iterator_t iter2)
{
	assert(NULL != iter1.DLLIterator);
	assert(NULL != iter2.DLLIterator);
	return DLLIsSameIter(iter1.DLLIterator, iter2.DLLIterator);
}

void *SortedListPopFront(sol_t *sol)
{
	assert(NULL != sol);
	return DLLPopFront(sol->list);
}

void *SortedListPopBack(sol_t *sol)
{
	assert(NULL != sol);
	return DLLPopBack(sol->list);
}

int SortedListForEach(sol_iterator_t from, sol_iterator_t to, action_func_t user_func, void *param)
{
	assert(NULL != from.DLLIterator);
	assert(NULL != to.DLLIterator);
	assert(NULL != user_func);
	assert(from.dll == to.dll);
	
	return DLLForEach(from.DLLIterator, to.DLLIterator, user_func, param);
}

sol_iterator_t SortedListFind(sol_t *sol, sol_iterator_t from, sol_iterator_t to, const void *to_find)
{
	assert(NULL != from.DLLIterator);
	assert(NULL != to.DLLIterator);
	assert(NULL != sol);
	assert(from.dll == to.dll);
	
	while (!DLLIsSameIter(from.DLLIterator, to.DLLIterator) && 0 != sol->user_func(SortedListGetData(from), to_find))
	{			
		from.DLLIterator = DLLNextIter(from.DLLIterator);
	}
	return from;
}

sol_iterator_t SortedListFindIf(sol_iterator_t from, sol_iterator_t to, is_match_t user_func, void *param)
{
	assert(NULL != from.DLLIterator);
	assert(NULL != to.DLLIterator);
	assert(NULL != user_func);
	assert(from.dll == to.dll);
	
	from.DLLIterator = DLLFind(from.DLLIterator, to.DLLIterator, user_func, param);
	return from;
}

sol_t *SortedListMerge(sol_t *dest_sol, sol_t *src_sol)
{
	sol_iterator_t iter_from = {0};
	sol_iterator_t iter_to = {0};
	sol_iterator_t iter_merge = {0};
	sol_iterator_t iter_find = {0};
	user_func_wrapper_t wrapper = {0};
	
	assert(NULL != dest_sol);
	assert(NULL != src_sol);
	
	wrapper.sol = dest_sol;
	iter_from = SortedListBeginIter(dest_sol);
	iter_to = SortedListEndIter(dest_sol);
	iter_merge = SortedListBeginIter(src_sol);
	
	while (!SortedListIsEmpty(src_sol))
	{
		wrapper.data = SortedListGetData(iter_merge);
		iter_find = SortedListFindIf(iter_from, iter_to, WrapUserFunc, &wrapper);
		DLLSplice(iter_find.DLLIterator, iter_merge.DLLIterator, DLLNextIter(iter_merge.DLLIterator));
		iter_merge = SortedListBeginIter(src_sol);
		iter_from = iter_find;
	}
	return dest_sol;
}

static int WrapUserFunc(const void *data, const void *wrapper)
{
	const void *data1 = ((user_func_wrapper_t *) wrapper)->data;
	cmp_func_st user_func = ((user_func_wrapper_t *) wrapper)->sol->user_func;
	
	return user_func((const void*) data, data1) >= 0;
}



