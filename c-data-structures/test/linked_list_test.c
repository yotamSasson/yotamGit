#include <stdio.h> /*printf*/

#include "linked_list.h"

static void TestLinked_list(void);
static void DrawSuccess(void);
static void DrawFailure(void);
static int IsMatch(void *from, const void *param);

int main(void)
{
    TestLinked_list();
    return 0;
}

static void TestLinked_list(void)
{
	sll_t *linkedList = SLLCreate();
	iterator_t iterator1 = SLLBeginIter(linkedList);
	iterator_t iterator2 = SLLBeginIter(linkedList);
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	size_t count = 0;
	
	printf("SLLCreate :\n");
    if (1 == SLLIsEmpty(linkedList))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    printf("SLLInsertBefore :\n");
    iterator1 = SLLInsertBefore(iterator1, &data1);
    ++count;
    if (1 != SLLIsEmpty(linkedList))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    printf("SLLGetData :\n");
    if (data1 == *((int*)SLLGetData(iterator1)))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    
    iterator1 = SLLInsertBefore(iterator1, &data2);
     ++count;
    iterator2 = SLLNextIter(iterator1);
    printf("SLLNextIter :\n");
    if (data1 == *((int*)SLLGetData(iterator2)))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    printf("SLLIsEmpty :\n");
    if (1 != SLLIsEmpty(linkedList))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    printf("SLLIsSameIter :\n");
    if (1 != SLLIsSameIter(iterator1, iterator2))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    printf("SLLSetData :\n");
    SLLSetData(iterator2, &data3);
    if (data3 == *((int*)SLLGetData(iterator2)))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
	iterator1 =  SLLInsertBefore(iterator2, &data1);
     ++count;
    printf("SLLFind :\n");
    iterator1 = SLLFind(SLLBeginIter(linkedList), SLLEndIter(linkedList), IsMatch, &data3);
    if (data3 == *((int*)SLLGetData(iterator1)))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    printf("SLLCount :\n");
    if (count == SLLCount(linkedList))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    printf("SLLForEach :\n");
    if (count == SLLCount(linkedList))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    SLLDestroy(linkedList);
}

static int IsMatch(void *from, const void *param)
{
	return (*(int*)from == *(int*)param) ? 0 : 1; 
}

static void DrawSuccess(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;42mSUCCESS\033[0m\n\n");
}

static void DrawFailure(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;41mFailed, You should be ashamed of yourself!\033[0m\n\n");
}

