
#include <stdio.h> /*printf*/
#include "stack.h"


stack_type *StackCreate(size_t capacity, size_t item_size);
void StackDestroy(stack_type *stack);
void StackPush(stack_type *stack, const void *item);
void StackPop(stack_type *stack);
void *StackPeek(const stack_type *stack);
int StackIsEmpty(const stack_type *stack);
size_t StackSize(const stack_type *stack);

int main(void)
{
    int item1 = 1;
    int item2 = 2;
    int item3 = 3;
    int item4 = 4;
    size_t capacity1 = 4;
    size_t item_size1 = sizeof(item1);
    stack_type *stack1 = StackCreate(capacity1, item_size1);

    StackPush(stack1, &item1);
    printf("%d is at the top of the stack1\n", *((int*)StackPeek(stack1)));
    StackPush(stack1, &item2);
    printf("%d is at the top of the stack1\n", *((int*)StackPeek(stack1)));
    StackPush(stack1, &item3);
    printf("%d is at the top of the stack1\n", *((int*)StackPeek(stack1)));
    StackPush(stack1, &item4);
    printf("%d is at the top of the stack1\n", *((int*)StackPeek(stack1)));
    
    if (!StackIsEmpty(stack1))
    StackDestroy(stack1); 
    
    return 0;
}
