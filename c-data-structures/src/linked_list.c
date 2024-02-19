#include <stdlib.h> /*malloc*/
#include <stdio.h> /*printf*/
#include <assert.h> /*assert*/

#include "linked_list.h"

struct Node
{
    void *data;
    node_t *next;
};

struct SingleLinkedList
{
	node_t *head;
	node_t *tail;
};

/************************ Functions ************************/

sll_t *SLLCreate(void)
{
	sll_t *linkedList = malloc(sizeof(sll_t));
	if (NULL == linkedList)
    {
        printf("Memory allocation for the linkedList faild \n");
        return NULL;
    }
    
	linkedList->head = malloc(sizeof(node_t));
	if (NULL == linkedList->head)
    {
        printf("Memory allocation for the linkedList->head faild \n");
        free(linkedList);
        return NULL;
    }
    
    linkedList->head->data = linkedList ;
    linkedList->head->next = NULL;
    linkedList->tail = linkedList->head;
    
    return linkedList;
}

void SLLDestroy(sll_t *sll)
{
	assert(NULL != sll);
	
	while (!SLLIsEmpty(sll))
	{
		sll->head = SLLRemove(sll->head);
	}
	free(sll->head);
	free(sll);
}


iterator_t SLLRemove(iterator_t iterator)
{
	iterator_t iter_to_remove = NULL;

    assert(NULL != iterator);
    
    if (NULL != iterator->next)
    {
		iter_to_remove = SLLNextIter(iterator);
    	SLLSetData(iterator, iter_to_remove->data);
		iterator->next = SLLNextIter(iter_to_remove);
		free(iter_to_remove);
    }
    	
	if (NULL == iterator->next)
	{
		((sll_t*)iterator->data)->tail = iterator;
	}
	
	return iterator;
}

iterator_t SLLInsertBefore(iterator_t iterator, void *data)
{
	node_t *new_node = malloc(sizeof(node_t));
	sll_t *list = NULL;
	assert(NULL != iterator->data);
	
	if (NULL == new_node)
    {
        printf("Memory allocation for the new_node faild \n");
        while (NULL != iterator->next)
		{
			iterator = iterator->next;
		}
		
		return iterator;
    }
	
	if (NULL == iterator->next)
	{
		list = iterator->data;
		list->tail = new_node;	
	}
	
    new_node->data = iterator->data;
    iterator->data = data;
    new_node->next = iterator->next;
    iterator->next = new_node;
    
    return iterator;
}

int SLLIsEmpty(const sll_t *sll)
{
	assert(NULL != sll);
	
	return (NULL == sll->head->next);
}

iterator_t SLLBeginIter(const sll_t *sll)
{
	assert(NULL != sll);
	
	return sll->head;
}

iterator_t SLLEndIter(const sll_t *sll)
{
	assert(NULL != sll);
	
	return sll->tail;
}

void *SLLGetData(iterator_t iterator)
{
	assert(NULL != iterator);
	
	return iterator->data;
}

iterator_t SLLNextIter(const iterator_t iterator)
{
	assert(NULL != iterator);

	return iterator->next;
}

int SLLIsSameIter(const iterator_t iter1, const iterator_t iter2)
{
	assert(NULL != iter1);
	assert(NULL != iter2);
	
	return(iter1 == iter2);
}

void SLLSetData(const iterator_t iterator, void *data)
{
	assert(NULL != data);
	if (NULL != iterator->next)
	{
		iterator->data = data;
	}
}

iterator_t SLLFind(iterator_t from, iterator_t to, is_match user_func, void *param)
{
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != user_func);
	
	while (!SLLIsSameIter(from, to) && 0 != user_func(from->data,param))
	{
		from = SLLNextIter(from);
	} 
	return from;
}

static int MyCount(void *data, void *counter)
{
	assert(NULL != data);
	
	++(*(size_t*)counter);
	
	return 0;
}

int SLLForEach(iterator_t from, const iterator_t to, action_func user_func, void *param)
{
	int flag = 0;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != user_func);
	
	while (!SLLIsSameIter(from, to))
	{
		flag = user_func(from->data, param);
		from = SLLNextIter(from);
		
	}
	return flag;
}

size_t SLLCount(const sll_t *sll)
{
	
	iterator_t iter_begin = SLLBeginIter(sll);
	iterator_t iter_end = SLLEndIter(sll);
	size_t count = 0;
		
	assert(NULL != sll);
	
	SLLForEach(iter_begin, iter_end, MyCount, &count);
	
	return count;
}

sll_t *SLLAppend(sll_t *dest ,sll_t *src)
{
	assert (NULL != dest);
	assert (NULL != src);
	
	src->tail->data = dest->tail->data;
    dest->tail->data = src->head->data;
    dest->tail->next = src->head->next;
    dest->tail = src->tail;
    src->head->data = src;
    src->head->next = NULL;
    src->tail = src->head;
    return dest;
}



