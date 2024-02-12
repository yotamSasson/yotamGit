#include <stdio.h> /*printf*/
#include <assert.h> /*assert*/

#include "heap.h"

static void DrawSuccess(void);
static void DrawFailure(void);
static int CmpFunc(const void *data1, const void *data2);
static void TestHeapCreate(void);
static void TestHeapIsEmpty(void);
static void TestHeapSize(void);
static void TestHeapPush(void);
static void TestHeapPeek(void);
static void TestHeapPop(void);
static void TestHeapRemove(void);
static int IsMatch(const void *from, const void *param);

int main (void)
{
    TestHeapCreate();
    TestHeapIsEmpty();
    TestHeapSize();
    TestHeapPush();
    TestHeapPeek();
    TestHeapPop();
    TestHeapRemove();
    return 0;
}

/************************ Helper Functions ************************/
static int CmpFunc(const void *data1, const void *data2)
{
	return (*(int *)data1 - *(int *)data2);
}

static int IsMatch(const void *from, const void *param)
{
	return (*(int*)from == *(int*)param); 
}
/************************ Test Functions ************************/
static void TestHeapCreate(void)
{
    heap_t *heap = HeapCreate(CmpFunc);

    printf("HeapCreate :\n");
    (NULL != heap) ? DrawSuccess() : DrawFailure();
    assert(NULL != heap);

    HeapDestroy(heap);
}

static void TestHeapIsEmpty(void)
{
    heap_t *heap = HeapCreate(CmpFunc);

    printf("HeapIsEmpty :\n");
    (HeapIsEmpty(heap)) ? DrawSuccess() : DrawFailure();
    assert(HeapIsEmpty(heap));

    HeapDestroy(heap);
}

static void TestHeapSize(void)
{
    heap_t *heap = HeapCreate(CmpFunc);

    printf("HeapSize :\n");
    (0 == HeapSize(heap)) ? DrawSuccess() : DrawFailure();
    assert(0 == HeapSize(heap));

    HeapDestroy(heap);
}

static void TestHeapPush(void)
{
    heap_t *heap = HeapCreate(CmpFunc);
    int data1 = 9;
    int data2 = 4;
    int data3 = 5;
    int status = 0;

    printf("TestHeapPush :\n");

    status += HeapPush(heap, &data1);
    status += HeapPush(heap, &data2);
    status += HeapPush(heap, &data3);

    (!HeapIsEmpty(heap) && 3 == HeapSize(heap) && 0 == status) ? DrawSuccess() : DrawFailure();

    assert(!HeapIsEmpty(heap));
    assert(0 == status);

    HeapDestroy(heap);
}

static void TestHeapPeek(void)
{
    heap_t *heap = HeapCreate(CmpFunc);
    int data1 = 4;
    int data2 = 5;
    int data3 = 9;
    int data4 = 10;
    int status = 0;

    printf("TestHeapPeek :\n");

    status += HeapPush(heap, &data1);
    status += HeapPush(heap, &data2);
    status += HeapPush(heap, &data3);
    status += HeapPush(heap, &data4);

    (10 ==  *(int *)HeapPeek(heap)) ? DrawSuccess() : DrawFailure();

    assert(!HeapIsEmpty(heap));
    assert(0 == status);

    HeapDestroy(heap);
}

static void TestHeapPop(void)
{
    heap_t *heap = HeapCreate(CmpFunc);
    int data1 = 4;
    int data2 = 5;
    int data3 = 9;
    int data4 = 10;
    int data5 = 6;

    printf("TestHeapPop:\n");

    HeapPush(heap, &data1);
    HeapPush(heap, &data2);
    HeapPush(heap, &data3);
    HeapPush(heap, &data4);
    HeapPush(heap, &data5);

    HeapPop(heap);
    (9 == *(int *)HeapPeek(heap) && 4 == HeapSize(heap)) ? DrawSuccess() : DrawFailure();
   
    assert(4 == HeapSize(heap));
    assert(9 == *(int *)HeapPeek(heap));

    HeapPop(heap); 
    (6 == *(int *)HeapPeek(heap) && 3 == HeapSize(heap)) ? DrawSuccess() : DrawFailure();
    assert(3 == HeapSize(heap));
    assert(6 == *(int *)HeapPeek(heap));

    HeapPop(heap); 
    (5 == *(int *)HeapPeek(heap) && 2 == HeapSize(heap)) ? DrawSuccess() : DrawFailure();
    assert(2 == HeapSize(heap));
    assert(5 == *(int *)HeapPeek(heap));

    HeapPop(heap); 
    (4 == *(int *)HeapPeek(heap) && 1 == HeapSize(heap)) ? DrawSuccess() : DrawFailure();
    assert(1 == HeapSize(heap));
    assert(4 == *(int *)HeapPeek(heap));

    HeapPop(heap); 
    (0 == HeapSize(heap)) ? DrawSuccess() : DrawFailure();
    assert(0 == HeapSize(heap));

    HeapDestroy(heap);
}

static void TestHeapRemove(void)
{
    heap_t *heap = HeapCreate(CmpFunc);
    int data1 = 5;
    int data2 = 2;
    int data3 = 7;
    int data4 = 1;
    int data5 = 8;
    int data6 = 3;
    int data7 = 10;
    int data8 = 4;
    int temp = 0;
    int temp2 = 0;
    int temp3 = 0;
    int temp4 = 0;
    int temp5 = 0;
    int temp6 = 0;
    int data_to_remove = 2;
    int data_to_remove2 = 7;
    int data_to_remove3 = 1;
    int data_to_remove4 = 8;
    int data_to_remove5 = 5;
    int data_to_remove6 = 3;
    int data_to_remove7 = 20;

    printf("HeapRemove:\n");

    HeapPush(heap, &data1);
    HeapPush(heap, &data2);
    HeapPush(heap, &data3);
    HeapPush(heap, &data4);
    HeapPush(heap, &data5);
    HeapPush(heap, &data6);
    HeapPush(heap, &data7);
    HeapPush(heap, &data8);

    
    temp = *(int *)HeapRemove(heap, IsMatch, &data_to_remove);
    (2 == temp && 7 == HeapSize(heap)) ? DrawSuccess() : DrawFailure();
    assert(7 == HeapSize(heap));
    assert(2 == temp);

    temp2 = *(int *)HeapRemove(heap, IsMatch, &data_to_remove2);
    (7 == temp2) ? DrawSuccess() : DrawFailure();
    assert(7 == temp2);

    temp3 = *(int *)HeapRemove(heap, IsMatch, &data_to_remove3);
    (1 == temp3) ? DrawSuccess() : DrawFailure();
    assert(1 == temp3);

    temp4 = *(int *)HeapRemove(heap, IsMatch, &data_to_remove4);
    (8 == temp4) ? DrawSuccess() : DrawFailure();
    assert(8 == temp4);

    temp5 = *(int *)HeapRemove(heap, IsMatch, &data_to_remove5);
    (5 == temp5) ? DrawSuccess() : DrawFailure();
    assert(5 == temp5);

    temp6 = *(int *)HeapRemove(heap, IsMatch, &data_to_remove6);
    (3 == temp6) ? DrawSuccess() : DrawFailure();
    assert(3 == temp6);

    printf("HeapRemoveByKey:\n");
    
    (NULL == HeapRemoveByKey(heap,  &data_to_remove7)) ? DrawSuccess() : DrawFailure();
    HeapDestroy(heap);
}

/************************Print Functions ************************/
static void DrawSuccess(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;42mSUCCESS\033[0m\n\n");
}

static void DrawFailure(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;41mFailed, You should be ashamed of yourself!\033[0m\n\n");
}

