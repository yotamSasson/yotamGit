#include <stdlib.h> /* malloc */
#include <assert.h> /*assert*/
#include <string.h> /*memcpy*/

#include <stdio.h> /*printf*/
#include "dynamic_vector.h"
#include "heap.h"

struct heap 
{
	vector_t *vec;
    int (*cmp_func)(const void *, const void *);
};

typedef enum {EQUALS, MATCH} success_t;

/************************ Macro ************************/
#define GET_ELEMENT(heap, index) ((void **)VectorGetAccessToElement(heap->vec, index))
#define LAST_INDEX(heap) (VectorSize(heap->vec) - 1)
#define WORD_SIZE (sizeof(void *))
#define CAPACITY (3)
#define PARENT_INDEX(index) ((index - 1) / 2)
#define LEFT_CHILD_INDEX(index) ((2 * index) + 1)
#define RIGHT_CHILD_INDEX(index) ((2 * index) + 2)
#define CMP_MACRO(cmp_func, data1, data2) ((*cmp_func)(data1, data2))
#define ROOT_INDEX (0)
#define GET_ROOT_ELEMENT(heap) (((void **)VectorGetAccessToElement(heap->vec, ROOT_INDEX)))
#define VEC_SIZE(heap) (VectorSize(heap->vec))
/************************ Helper functions ************************/
static void Swap(void **ptr1, void **ptr2);
static void HeapifyUp(heap_t *heap , size_t index);
static void HeapifyDown(heap_t *heap , size_t index);
static void *MultyRemove(heap_t *heap, int(*act_func)(const void *, const void *), const void *param, success_t success);

/************************ Functions ************************/

heap_t *HeapCreate (int (*cmp_func)(const void *, const void *))
{
    heap_t *heap = malloc(sizeof(heap_t));
    size_t element_size = sizeof(size_t *);

    assert(NULL != cmp_func);

    if (NULL == heap)
    {
        return NULL;
    }

    heap->vec = VectorCreate(CAPACITY, element_size);
    heap->cmp_func = cmp_func;

    if (NULL == heap->vec)
    {
        free(heap);
        return NULL;
    }

    return heap;
}

void HeapDestroy(heap_t *heap)
{
    assert(NULL != heap);

    VectorDestroy(heap->vec);
    free(heap);
}

int HeapPush(heap_t *heap, void *data)
{
    size_t status = 0;
    size_t index = 0;

    assert(NULL != heap);
    assert(NULL != data);

    status = VectorPushBack(heap->vec, data);
    index = LAST_INDEX(heap);

    HeapifyUp(heap, index);

    return status;
}

void HeapPop(heap_t *heap)
{
    assert(NULL != heap);
    assert(!HeapIsEmpty(heap));

    Swap(GET_ELEMENT(heap, ROOT_INDEX), GET_ELEMENT(heap, LAST_INDEX(heap)));
    VectorPopBack(heap->vec);
    HeapifyDown(heap, ROOT_INDEX);
}

void *HeapPeek(const heap_t *heap)
{
    assert(NULL != heap);
    assert(!HeapIsEmpty(heap));

    return *GET_ROOT_ELEMENT(heap);
}

void *HeapRemove(heap_t *heap, int (*is_match_func)(const void *data, const void *param), const void *param)
{
    assert(NULL != heap);
    assert(NULL != param);
    
    return MultyRemove(heap, is_match_func, param, MATCH);
}

void *HeapRemoveByKey(heap_t *heap, void *data)
{
    assert(NULL != heap);
    assert(NULL != data);
    
    return MultyRemove(heap, heap->cmp_func, data, EQUALS);
}

int HeapIsEmpty(const heap_t *heap)
{
    assert(NULL != heap);

    return VectorIsEmpty(heap->vec);
}

size_t HeapSize(const heap_t *heap)
{
    assert(NULL != heap);

    return VEC_SIZE(heap);
}

/************************ Helper functions ************************/

static void Swap(void **ptr1, void **ptr2)
{
    void *temp = NULL;

    assert(NULL != ptr1);
    assert(NULL != ptr2);

    temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

static void HeapifyUp(heap_t *heap , size_t index)
{
    assert(NULL != heap);

    while (index > 0 && 0 < CMP_MACRO(heap->cmp_func, *GET_ELEMENT(heap, index), *GET_ELEMENT(heap, PARENT_INDEX(index))))
    {
        Swap(GET_ELEMENT(heap, index), GET_ELEMENT(heap, PARENT_INDEX(index)));
        index = PARENT_INDEX(index);
    }
}

static void HeapifyDown(heap_t *heap , size_t index)
{
    size_t size = 0;
    size_t max_index = 0;

    assert(NULL != heap);

    size = VEC_SIZE(heap);

    while (index < size / 2)
    {
        if (RIGHT_CHILD_INDEX (index) < size)
        {
                
            max_index = CMP_MACRO(heap->cmp_func, *GET_ELEMENT(heap, LEFT_CHILD_INDEX(index)), *GET_ELEMENT(heap, RIGHT_CHILD_INDEX(index))) > 0 ? LEFT_CHILD_INDEX(index) : RIGHT_CHILD_INDEX(index);
        }
        else
        {
            max_index = LEFT_CHILD_INDEX (index);
        }

        if (CMP_MACRO(heap->cmp_func, *GET_ELEMENT(heap, max_index), *GET_ELEMENT(heap, index)) > 0)
        {
            Swap(GET_ELEMENT(heap, max_index), GET_ELEMENT(heap, index));
            index = max_index;
        }
        else
        {
            break;
        }       
    }
}

static void *MultyRemove(heap_t *heap, int(*act_func)(const void *, const void *), const void *param, success_t success)
{
    void **ret_val = NULL;
    size_t i = 0;
    int found_flag = 0;

    for (i = 0; i < VEC_SIZE(heap) && (int)success != act_func(*GET_ELEMENT(heap, i), param); ++i){}

    if (i != VEC_SIZE(heap))
    {   
        Swap(GET_ELEMENT(heap, i), GET_ELEMENT(heap, LAST_INDEX(heap)));
        ret_val = *GET_ELEMENT(heap, LAST_INDEX(heap)); 
        VectorPopBack(heap->vec);
        HeapifyDown(heap, i);
        HeapifyUp(heap, i);
        found_flag = 1; 
    }
    
    return found_flag ? ret_val : NULL;
}
