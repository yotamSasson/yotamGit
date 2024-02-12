#ifndef MY_PROJECT_RECURSION_H__
#define MY_PROJECT_RECURSION_H__

#include <stddef.h>	/* size_t */
#include <stdio.h> /*printf*/
#include <string.h> /*strlen, strcmp, strcpy*/

#include "stack.h"

typedef struct Node
{
    int data;
    struct Node* next;
}Node;

size_t StrLenRec(const char *dest);
int StrCmpRec( const char *s1, const char *s2);
char *StrCpyRec(char *dest, const char *src);
char *StrCatRec(char *dest, const char *src);
char *StrStrRec(const char *heystack, const char *needle);
int FiboIter(int element_index);
int FiboRec(int element_index);
Node* FlipList(Node *node);
Node* AddNode(Node *head, int data);
void DestroyList(Node *head);
void TraverseList(Node *head);
void SortStack(stack_type *stack);
#endif
