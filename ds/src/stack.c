
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include <stdio.h> /*printf*/
#include <string.h> /*memcpy*/
#include "stack.h"

struct Stack
{
    void *data;
    size_t top;
	size_t capacity;
	size_t i_size;
};

stack_type *StackCreate(size_t capacity, size_t item_size)
{
    stack_type *stack = (stack_type*)malloc(sizeof(stack_type));
    if (NULL == stack)
    {
        printf("Memory allocation for the satck faild \n");
        return NULL;
    }
    
    stack->capacity = capacity;
    stack->top = 0;
    stack->i_size = item_size;
    
    stack->data = malloc(capacity * item_size);
    if (NULL == stack->data)
    {
        printf("Memory allocation for the data array faild \n");
        return NULL;
    }
    return stack;
}

void StackDestroy(stack_type *stack)
{
    free(stack->data);
    stack->data = NULL;
    
    free(stack);
    stack = NULL;
}

size_t StackSize(const stack_type *stack)
{
    return stack->top;
}

int StackIsEmpty(const stack_type *stack)
{
    return (0 == stack->top);
}

void StackPop(stack_type *stack)
{
    assert(NULL != stack);
    assert(!StackIsEmpty(stack));
    
    --stack->top;
}

void StackPush(stack_type *stack, const void *item)
{
 
    assert(NULL != stack);
    assert(NULL != item);
    assert(stack->top != stack->capacity);
 
    memcpy((char*)stack->data + (stack->top * stack->i_size), item, stack->i_size);   
    ++stack->top;
}

void* StackPeek(const stack_type *stack)
{
    assert(NULL != stack);
   assert(!StackIsEmpty(stack));
    
    return (void *)((char*)stack->data + ((stack->top  - 1) * stack->i_size));
    
}

size_t StackCapacity(const stack_type *stack)
{
	assert(NULL != stack);
	
	return stack->capacity;
}
