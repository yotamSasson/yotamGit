#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc*/

#include "recursion.h"


static void SortedPush(stack_type *stack, int data);

size_t StrLenRec(const char *dest)
{
	const char *runner = dest;
	
	assert(NULL != dest);
	
	if ('\0' == *runner)
	{
		return 0;
	}
	
	return 1 + StrLenRec(++runner);

}

int StrCmpRec( const char *s1, const char *s2)
{
	assert(NULL != s1);
	assert(NULL != s2);
	
	if ('\0' == *s1 || *s1 != *s2)
    {
        return  *s1 - *s2;
    }
    
    return StrCmpRec(++s1, ++s2);
}

char *StrCpyRec(char *dest, const char *src)
{
	char *start = dest;
	
	assert(NULL != dest);
	assert(NULL != src);
	
	if ('\0' == *src)
	{
		*start = '\0';
	}
	else
	{
		*start = *src;
		start = StrCpyRec(++start, ++src);
	}
	return start;
}

char *StrCatRec(char *dest, const char *src)
{
	char *runner = dest + StrLenRec(dest);
	
	assert(NULL != src);
	assert(NULL != dest);
	
	if ('\0' != *src)
	{
		StrCpyRec(runner, src);
	}
	
	return dest;
}

char *StrStrRec(const char *heystack, const char *needle)
{
	assert(NULL != heystack);
	assert(NULL != needle);
	
	if ('\0' == *needle)
	{
		return (char *)heystack;
	}
	
	if ('\0' == *heystack)
	{
		return NULL;
	}
	
	if (*heystack == *needle && 0 == strncmp(heystack, needle, StrLenRec(needle)))
	{
		return (char *)heystack;
	}
	
	return StrStrRec(++heystack, needle);
}

int FiboIter(int element_index)
{
	int i = 0;
	int fib = 0;
	int prev = 0;
	int curr = 1;
	
	if (1 >= element_index)
	{
		return element_index;
	}
	
	for (i = 2; i <= element_index; ++i)
	{
		fib = prev + curr;
		prev = curr;
		curr = fib;
	}
	
	return fib;
}

int FiboRec(int element_index)
{
	if (1 >= element_index)
	{
		return element_index;
	}
	
	return FiboRec(element_index - 1) + FiboRec(element_index - 2);
}

Node *FlipList(Node* node)
{
	Node *new_node = NULL;
	if (node == NULL || node->next == NULL)
	{
        return node;
    }
    
    new_node = FlipList(node->next);
    node->next->next = node;
    node->next = NULL;
    return new_node;
}

Node* AddNode(Node* head, int data)
{
	Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = head;
    return new_node;
}

void DestroyList(Node *head)
{
	Node *current = head;
	Node *next = head;
	
	while (NULL != head->next)
	{
    	while (NULL != current->next)
		{
        	next = current;
        	current = current->next;
    	}
    	next->next = NULL;
        free(current);
        current = head;
	}
	free(head);
    head = NULL;
}

void TraverseList(Node *head)
{
	Node *temp = head;
    
    if (NULL == head)
    {
        printf("List is empty.");
    }
    
    while (NULL != temp)
    {
        printf("%d\n",temp->data);
        temp = temp->next;
    }
}

void SortStack(stack_type *stack)
{
	int temp = 0;
	
	if (!StackIsEmpty(stack))
	{
        temp = *((int *)StackPeek(stack));
        StackPop(stack);
    	SortStack(stack);
    	SortedPush(stack, temp);
    }
}

static void SortedPush(stack_type *stack, int data)
{
	int temp = 0;
	
	if ((StackIsEmpty(stack)) || (data < *(int *)StackPeek(stack)))
	{
        StackPush(stack, &data);
    }
    else
    {
    	temp = *((int *)StackPeek(stack));
   	 	StackPop(stack);
    	SortedPush(stack, data);
   	 	StackPush(stack, &temp);
   	}
}
