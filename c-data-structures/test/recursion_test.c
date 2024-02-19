#include <stdlib.h> /*malloc*/

#include "recursion.h"

static void DrawSuccess(void);
static void DrawFailure(void);
static void TestStrLenRec(void);
static void TestStrCmpRec(void);
static void TestStrCpyRec(void);
static void TestStrCatRec(void);
static void TestStrStrRec(void);
static void TestFiboIter(void);
static void TestFiboRec(void);
static void TestFlipLis(void);
static void TestSortStack(void);

int main(void)
{
	TestStrLenRec();
	TestStrCmpRec();
	TestStrCpyRec();
	TestStrCatRec();
	TestStrStrRec();
	TestFiboIter();
	TestFiboRec();
	TestFlipLis();
	TestSortStack();
	return 0;
}

static void TestStrLenRec(void)
{
	char *str = "hello yotam";
	size_t rec_length = StrLenRec(str);
	size_t string_length = strlen(str);
	
	printf("StrLenRec :\n");
	(rec_length == string_length) ? DrawSuccess() : DrawFailure();
}

static void TestStrCmpRec(void)
{
	char *str1 = "aba";
	char *str2 = "abb";
	int rec_cmp = StrCmpRec(str1 ,str2);
	int string_cmp = strcmp(str1 ,str2);
	
	printf("StrCmpRec :\n");
	(0 > rec_cmp &&  0 > string_cmp) ? DrawSuccess() : DrawFailure();
}

static void TestStrCpyRec(void)
{
	char *src1 = "hello";
	size_t src1_len = StrLenRec(src1);
	char *dest = (char *)malloc((src1_len + 1) * sizeof(char));
	
	if (NULL == dest)
	{
		printf("Allocation failed \n");
	}
	
	StrCpyRec(dest, src1);
	
	printf("StrCpyRec :\n");
	(0 == StrCmpRec(dest ,src1)) ? DrawSuccess() : DrawFailure();
	
	free(dest);
}

static void TestStrCatRec(void)
{
	char dest[12] = "hello ";
	char *src = "world";
	char *bodek = "hello world";
	
	StrCatRec(dest, src);
	
	printf("StrCatRec :\n");
	(0 == StrCmpRec(dest ,bodek)) ? DrawSuccess() : DrawFailure();
}

static void TestStrStrRec(void)
{
	const char *heystack = "hello world";
	const char *needle1 = "world";
	const char *needle2 = "abc";
	
	printf("StrStrRec :\n");
	(NULL != StrStrRec(heystack, needle1)) ? DrawSuccess() : DrawFailure();
	
	(NULL == StrStrRec(heystack, needle2)) ? DrawSuccess() : DrawFailure();
}

static void TestFiboIter(void)
{
	int element_index = 6;
	
	printf("FiboIter :\n");
	(8 == FiboIter(element_index)) ? DrawSuccess() : DrawFailure();
}

static void TestFiboRec(void)
{
	int element_index = 6;
	
	printf("FiboRec :\n");
	(FiboRec(element_index) == FiboIter(element_index)) ? DrawSuccess() : DrawFailure();
}

static void TestFlipLis(void)
{
	Node* head = NULL;
    head = AddNode(head, 5);
    head = AddNode(head, 4);
    head = AddNode(head, 3);
    head = AddNode(head, 2);
    head = AddNode(head, 1);
    
    printf("Original List:\n");
    TraverseList(head);
    
    head = FlipList(head);
    printf("Flipped List:\n");
    TraverseList(head);
    
    DestroyList(head);
}

static void TestSortStack(void)
{
	size_t capacity = 5;
	size_t item_size = sizeof(int);
	int data1 = 4;
	int data2 = 2;
	int data3 = 6;
	int data4 = 3;
	
	stack_type *stack = StackCreate(capacity, item_size);
	StackPush(stack, &data1);
	StackPush(stack, &data2);
	StackPush(stack, &data3);
	StackPush(stack, &data4);
	
	SortStack(stack);
	
	printf("SortStack:\n");
	while (!StackIsEmpty(stack))
	{
		printf("%d\n", *((int*)StackPeek(stack)));
		StackPop(stack);
	}
	
	StackDestroy(stack); 
}

static void DrawSuccess(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;42mSUCCESS\033[0m\n\n");
}

static void DrawFailure(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;41mFailed, You should be ashamed of yourself!\033[0m\n\n");
}


