#include <assert.h> /*assert*/
#include <stdio.h> /*printf*/
#include "dll.h"

static void TestDoblyLinkedList(void);
static void DrawSuccess(void);
static void DrawFailure(void);
static void TestDLLCreate(void);
static void TestDLLIsEmpty(void);
static void TestDLLInsert(void);
static void TestDLLGetData(void);
static void TestDLLRemove(void);
static void TestDLLSetData(void);
static void TestDLLPushFront(void);
static void TestDLLPopFront(void);
static void TestDLLPushBack(void);
static void TestDLLPopBack(void);
static void TestDLLCount(void);
static void TestDLLFind(void);
static int IsMatch(const void *from, const void *param);
static void TestDLLSplice(void);
static void TestDLLMultiFind(void);


int main(void)
{
    TestDoblyLinkedList();
    return 0;
}

static void TestDoblyLinkedList(void)
{
	TestDLLCreate();
}

static void TestDLLCreate(void)
{
	dll_t *d_linked_list = DLLCreate();
	
	printf("DLLCreate :\n");
    if (NULL != d_linked_list)
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    TestDLLIsEmpty();
    
	TestDLLInsert();
	
	TestDLLGetData();
	
	TestDLLRemove();
	
	TestDLLSetData();
	
	TestDLLPushFront();
	
	TestDLLPopFront();
	
	TestDLLPushBack();
	
	TestDLLPopBack();
	
	TestDLLCount();
	
	TestDLLFind();
	
	TestDLLSplice();
	
	TestDLLMultiFind();
	
	DLLDestroy(d_linked_list);
}

static void TestDLLIsEmpty(void)
{
	dll_t *d_linked_list = DLLCreate();
	
	
	printf("DLLIsEmpty :\n");
    if (DLLIsEmpty(d_linked_list))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    DLLDestroy(d_linked_list);
}

static void TestDLLInsert(void)
{
	dll_t *d_linked_list = DLLCreate();
	iterator_t iterator1 = DLLBeginIter(d_linked_list);
	int data1 = 1;
	
	printf("DLLInsert :\n");
    iterator1 = DLLInsert(iterator1, &data1);
    
    if (!DLLIsEmpty(d_linked_list) && data1 == *((int*)DLLGetData(iterator1)))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    } 
    DLLDestroy(d_linked_list);
}

static void TestDLLGetData(void)
{
	dll_t *d_linked_list = DLLCreate();
	iterator_t iterator1 = DLLBeginIter(d_linked_list);
	int data1 = 1;
	
	printf("DLLGetData :\n");
    iterator1 = DLLInsert(iterator1, &data1);
    if (data1 == *((int*)DLLGetData(iterator1)))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    } 
    DLLDestroy(d_linked_list);
}

static void TestDLLRemove(void)
{
	dll_t *d_linked_list = DLLCreate();
	iterator_t iterator1 = DLLBeginIter(d_linked_list);
	int data1 = 1;
	
	iterator1 = DLLInsert(iterator1, &data1);
	DLLRemove(iterator1);
	
	printf("DLLRemove :\n");
    if (DLLIsEmpty(d_linked_list))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    DLLDestroy(d_linked_list);
}

static void TestDLLSetData(void)
{
	dll_t *d_linked_list = DLLCreate();
	iterator_t iterator1 = DLLBeginIter(d_linked_list);
	int data1 = 1;
	int data2 = 2;
	
	iterator1 = DLLInsert(iterator1, &data1);
	
	printf("DLLSetData :\n");
    DLLSetData(iterator1, &data2);
    if (data2 == *((int*)DLLGetData(iterator1)))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    DLLDestroy(d_linked_list);
}

static void TestDLLPushFront(void)
{
	dll_t *d_linked_list = DLLCreate();
	iterator_t iterator1 = NULL;
	int data1 = 1;
	
    DLLPushFront(d_linked_list, &data1);
    iterator1 = DLLBeginIter(d_linked_list);
    
	printf("DLLPushFront :\n");
    if (!DLLIsEmpty(d_linked_list) && data1 == *((int*)DLLGetData(iterator1)))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    } 
    DLLDestroy(d_linked_list);
}

static void TestDLLPopFront(void)
{
	dll_t *d_linked_list = DLLCreate();
	int data1 = 1;
	
    DLLPushFront(d_linked_list, &data1);
    
    printf("DLLPopFront :\n");
    if (data1 == *((int*)DLLPopFront(d_linked_list)) && DLLIsEmpty(d_linked_list) )
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    } 
    DLLDestroy(d_linked_list);
}

static void TestDLLPushBack(void)
{
	dll_t *d_linked_list = DLLCreate();
	iterator_t iterator1 = NULL;
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	
    DLLPushBack(d_linked_list, &data2);
    DLLPushFront(d_linked_list, &data1);
    iterator1 = DLLEndIter(d_linked_list);
    iterator1 = DLLPrevIter(iterator1);
    
	printf("DLLPushBack :\n");
    if (data2 == *((int*)DLLGetData(iterator1)))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    } 
    
    DLLPushBack(d_linked_list, &data3);
    iterator1 = DLLEndIter(d_linked_list);
    iterator1 = DLLPrevIter(iterator1);
    
    if (data3 == *((int*)DLLGetData(iterator1)))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    } 
    
    DLLDestroy(d_linked_list);
}

static void TestDLLPopBack(void)
{
	dll_t *d_linked_list = DLLCreate();
	iterator_t iterator1 = NULL;
	int data1 = 1;
	int data2 = 2;
	
    DLLPushBack(d_linked_list, &data1);
    DLLPushBack(d_linked_list, &data2);
    iterator1 = DLLEndIter(d_linked_list);
    iterator1 = DLLPrevIter(iterator1);
    
    printf("DLLPopBack :\n");
    if (data2 == *((int*)DLLPopBack(d_linked_list)))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    } 
    DLLDestroy(d_linked_list);
}

static void TestDLLCount(void)
{
	dll_t *d_linked_list = DLLCreate();
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	size_t count = 0;
	
	DLLPushFront(d_linked_list, &data1);
	++count;
	DLLPushFront(d_linked_list, &data2);
	++count;
	DLLPushFront(d_linked_list, &data3);
	++count;
	DLLPushFront(d_linked_list, &data4);
	++count;
	
	printf("DLLCount :\n");
    if (count == DLLCount(d_linked_list))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
	
	DLLDestroy(d_linked_list);
}

static int IsMatch(const void *from, const void *param)
{
	return (*(int*)from == *(int*)param) ? SUCCESS : FAILURE; 
}

static void TestDLLFind(void)
{
	dll_t *d_linked_list = DLLCreate();
	iterator_t iterator1 = NULL;
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	
	DLLPushFront(d_linked_list, &data1);
	DLLPushFront(d_linked_list, &data2);
	DLLPushFront(d_linked_list, &data3);
	DLLPushFront(d_linked_list, &data4);

	printf("DLLFind :\n");
    iterator1 = DLLFind(DLLBeginIter(d_linked_list), DLLEndIter(d_linked_list), IsMatch, &data1);
    if (data1 == *((int*)DLLGetData(iterator1)))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    iterator1 = DLLFind(DLLBeginIter(d_linked_list), DLLEndIter(d_linked_list), IsMatch, &data2);
    if (data2 == *((int*)DLLGetData(iterator1)))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    iterator1 = DLLFind(DLLBeginIter(d_linked_list), DLLEndIter(d_linked_list), IsMatch, &data3);
    if (data3 == *((int*)DLLGetData(iterator1)))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    iterator1 = DLLFind(DLLBeginIter(d_linked_list), DLLEndIter(d_linked_list), IsMatch, &data4);
    if (data4 == *((int*)DLLGetData(iterator1)))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    DLLDestroy(d_linked_list);
}

static void TestDLLSplice(void)
{
	dll_t *src = DLLCreate();
	dll_t *dest = DLLCreate();
	
	iterator_t src_from = NULL;
	iterator_t src_to = NULL;
	iterator_t iterator_dest = NULL;
	
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	int data5 = 5;
	size_t count = 0;
	
	DLLPushFront(src, &data1);
	++count;
	DLLPushFront(src, &data2);
	++count;
	DLLPushFront(src, &data3);
	++count;
	DLLPushFront(src, &data4);
	++count;
	src_from = DLLBeginIter(src);
	src_to = DLLEndIter(src);
	
	DLLPushFront(dest, &data5);
	++count;
	iterator_dest = DLLEndIter(dest);
	
	printf("DLLSplice :\n");
    iterator_dest = DLLSplice(iterator_dest, src_from, src_to);
    if (count == DLLCount(dest) && 0 == DLLCount(src))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
	
	DLLDestroy(src);
	DLLDestroy(dest);
}

static void TestDLLMultiFind(void)
{
	dll_t *d_linked_list = DLLCreate();
	dll_t *dll_dest = DLLCreate();
	iterator_t from = NULL;
	iterator_t to = NULL;
	
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	
	DLLPushFront(d_linked_list, &data1);
	DLLPushFront(d_linked_list, &data2);
	DLLPushFront(d_linked_list, &data3);
	DLLPushFront(d_linked_list, &data4);
	
	from = DLLBeginIter(d_linked_list);
	to = DLLEndIter(d_linked_list);
	
	dll_dest = DLLMultiFind(dll_dest, from, to, IsMatch, &data3);
	printf("DLLMultiFind :\n");
    if (1 == DLLCount(dll_dest) && data3 == *((int*)DLLPopBack(dll_dest)))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
	DLLDestroy(dll_dest);
	DLLDestroy(d_linked_list);
}
static void DrawSuccess(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;42mSUCCESS\033[0m\n\n");
}

static void DrawFailure(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;41mFailed, You should be ashamed of yourself!\033[0m\n\n");
}

