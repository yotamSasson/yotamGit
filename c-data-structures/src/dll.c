#include <stdio.h> /*perror*/
#include <assert.h> /*assert*/
#include <errno.h> /*errno*/
#include <stdlib.h> /*malloc*/
#include "dll.h"

typedef struct node node_t;

struct node
{
	void *data;
	node_t *next;
	node_t *prev;
};

struct doubly_linked_list
{
	node_t *head;
	node_t *tail;
};
static node_t *CreateNode(void *data);

/************************ Functions ************************/

dll_t *DLLCreate(void)
{
    dll_t *d_linked_list = malloc(sizeof(dll_t));
    if (NULL == d_linked_list)
    {
    	errno = ENOMEM; /*not enough memory available*/
        perror("Memory allocation:");
        return NULL;
    }
    
    d_linked_list->head = CreateNode(d_linked_list);
    
    if (NULL == d_linked_list->head)
    {
        free(d_linked_list);
        return NULL;
    }
    
    d_linked_list->tail = CreateNode(d_linked_list);
    
    if (NULL == d_linked_list->tail)
    {
        free(d_linked_list->head);
        free(d_linked_list);
        return NULL;
    }
    
    d_linked_list->head->next = d_linked_list->tail;
    d_linked_list->tail->prev = d_linked_list->head;
    
    return d_linked_list;
}

static node_t *CreateNode(void *data)
{
	node_t *new_node = NULL;
	new_node = malloc(sizeof(node_t));
        
	if (NULL == new_node)
	{
    	errno = ENOMEM; /*not enough memory available*/
       	perror("Memory allocation:");
        return NULL;
	}
	
	new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
        
	return new_node;
}

void DLLDestroy(dll_t *dll)
{
    assert(NULL != dll);
    
    while (!DLLIsEmpty(dll))
    {
        DLLPopFront(dll);
    }
    
    free(dll->head);
    free(dll->tail);
    free(dll);
}

int DLLIsEmpty(const dll_t *dll)
{
    assert(NULL != dll);
    
    return (NULL == DLLBeginIter(dll)->next);
}

iterator_t DLLBeginIter(const dll_t *dll)
{
	assert(NULL != dll);
	
    return dll->head->next;
}

iterator_t DLLEndIter(const dll_t *dll)
{
    assert(NULL != dll);
    return dll->tail;
}

int DLLIsSameIter(const iterator_t iter1, const iterator_t iter2)
{
	assert(NULL != iter1);
	assert(NULL != iter2);
	
	return(iter1 == iter2);
}

void DLLSetData(const iterator_t iterator, void *data)
{
	assert(NULL != iterator);
	assert(NULL != DLLNextIter(iterator));
	assert(NULL != DLLPrevIter(iterator));
	
	iterator->data = data;
}

iterator_t DLLNextIter(const iterator_t iterator)
{
    assert(NULL != iterator);
    
    return iterator->next;
}

iterator_t DLLPrevIter(const iterator_t iterator)
{
    assert(NULL != iterator);

    return iterator->prev;
}

iterator_t DLLInsert(iterator_t iterator, void *data)
{
	node_t *new_node = CreateNode(data);
	assert(NULL != iterator);
	
    if (NULL == new_node)
    {
        while (NULL != DLLNextIter(iterator))
        {
            iterator = DLLNextIter(iterator);
        }

        return iterator;
    }
    
    new_node->prev = DLLPrevIter(iterator);
    new_node->next = iterator;
    iterator->prev = new_node;
    new_node->prev->next = new_node;
    iterator = new_node;
    
    return iterator;
}

iterator_t DLLRemove(iterator_t iterator)
{
	iterator_t iter_to_ret = DLLNextIter(iterator);
	
	assert(NULL != DLLPrevIter(iterator));
	assert(NULL != DLLNextIter(iterator));
	assert(NULL != iterator);
	
	DLLPrevIter(iterator)->next = DLLNextIter(iterator);
	DLLNextIter(iterator)->prev = DLLPrevIter(iterator);

	free(iterator);
	
	return iter_to_ret;
}

void *DLLGetData(iterator_t iterator)
{
	assert(NULL != iterator);
	
	return iterator->data;
}

iterator_t DLLPushFront(dll_t *dll, void *data)
{
	assert(NULL != dll);
	
	return DLLInsert(DLLBeginIter(dll) , data);
}

void *DLLPopFront(dll_t *dll)
{
	void *temp = NULL;
	
	assert(NULL != dll);
	assert(!DLLIsEmpty(dll));
	
	temp = DLLGetData(DLLBeginIter(dll));
	DLLRemove(DLLBeginIter(dll));
	
	return temp;
}

iterator_t DLLPushBack(dll_t *dll, void *data)
{
	assert(NULL != dll);
	
	return DLLInsert(DLLEndIter(dll) , data);
}

void *DLLPopBack(dll_t *dll)
{
	void *temp = NULL;
	iterator_t iterator = NULL;
	
	assert(NULL != dll);
	assert(!DLLIsEmpty(dll));
	
	iterator = DLLEndIter(dll);
	iterator = DLLPrevIter(iterator);
	
	temp = DLLGetData(iterator);
	DLLRemove(iterator);
	
	return temp;
}

/******************** Traverse Functions**************************/

static int MyCount(void *data, void *counter)
{
	assert(NULL != data);
	
	++(*(size_t*)counter);
	
	return 0;
}

int DLLForEach(iterator_t from, const iterator_t to, action_func_t user_func, void *param)
{
	int flag = 0;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != user_func);
	
	while (!DLLIsSameIter(from, to))
	{
		flag += user_func(from->data, param);
		from = DLLNextIter(from);
		
	}
	return flag;
}

size_t DLLCount(const dll_t *dll)
{
	
	iterator_t iter_begin = NULL;
	iterator_t iter_end = NULL;
	size_t count = 0;
		
	assert(NULL != dll);
	
	iter_begin = DLLBeginIter(dll);
	iter_end = DLLEndIter(dll);
	DLLForEach(iter_begin, iter_end, MyCount, &count);
	
	return count;
}

iterator_t DLLFind(iterator_t from, iterator_t to, is_match_t user_func, const void *param)
{
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != user_func);
	
	while (!DLLIsSameIter(from, to) && SUCCESS != user_func(from->data,param))
	{
		from = DLLNextIter(from);
	} 
	return from;
}

iterator_t DLLSplice(iterator_t dest, iterator_t src_from ,iterator_t src_to)
{
	iterator_t tmp_src_from_prev = NULL;
	
	assert (NULL != dest);
	assert(NULL != src_from);
	assert(NULL != src_to);
	
	tmp_src_from_prev = DLLPrevIter(src_from);
	DLLPrevIter(src_from)->next = src_to;
	DLLPrevIter(src_to)->next = dest;
	DLLPrevIter(dest)->next = src_from;
	src_from->prev = DLLPrevIter(dest);
	dest->prev = DLLPrevIter(src_to);
	src_to->prev = tmp_src_from_prev;

    return dest;
}

dll_t *DLLMultiFind(dll_t *dll_dest, iterator_t from, iterator_t to, is_match_t user_func, void *param)
{
	assert (NULL != dll_dest);
	assert(NULL != from);
	assert(NULL != to);
	
	while (!DLLIsSameIter(from, to))
	{
		if (SUCCESS == user_func(from->data,param))
		{
			DLLPushFront(dll_dest, DLLGetData(from));
		}
		
		from = DLLNextIter(from);
	} 
	return dll_dest;	
}


