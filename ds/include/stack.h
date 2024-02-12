#ifndef MY_PROJECT__stack_H__
#define MY_PROJECT__stack_H__

#include <stddef.h> /*size_t*/

typedef struct Stack stack_type;

/*
**************Limitation**********
#poping an empty stack will result an error
#pushing to full stack will result an error

*************basic instructions*********
check the stack current capacity before executing a command*/

/*
DESCRIPTION: The function creates a stack data structure by allocating memory, initializing its properties
RETURN VALUE :pointer to the stack 
COMPLEXITY: O(1)
*/
stack_type *StackCreate(size_t capacity, size_t item_size);
/*
DESCRIPTION: The function frees the memory allocated to a stack
RETURN VALUE ::no return value
COMPLEXITY: O(1)
*/
void StackDestroy(stack_type *stack);
/*
DESCRIPTION: The function adds an element to the top of a stack
RETURN VALUE :no return value
COMPLEXITY: O(1)
*/
void StackPush(stack_type *stack, const void *item);
/*
DESCRIPTION: The function removes the top element from a stack*
RETURN VALUE :no return value
COMPLEXITY: O(1)
*/
void StackPop(stack_type *stack);
/*
DESCRIPTION: The function returns a pointer to the top element of a stack without removing it
RETURN VALUE :pointer to the stack
COMPLEXITY: O(1)
*/
void *StackPeek(const stack_type *stack);
/*
DESCRIPTION: The function checks if a stack is empty and returns a boolean value.
RETURN VALUE : int 1 or int 0
COMPLEXITY: O(1)
*/
int StackIsEmpty(const stack_type *stack);
/*
DESCRIPTION: The function returns the number of elements in a stack
RETURN VALUE : size_t */
size_t StackSize(const stack_type *stack);

size_t StackCapacity(const stack_type *stack);

#endif

