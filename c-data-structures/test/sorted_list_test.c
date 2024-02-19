#include <stdio.h> /*printf*/
#include "sorted_list.h"

static void DrawSuccess(void);
static void DrawFailure(void);
static void TestSortedList(void);
static void TestSortedListCreate(void);
static void TestSortedListIsEmpty(void);
static void TestSortedListSize(void);
static void TestSortedListInsert(void);
static void TestSortedListRemove(void);
static void TestSortedListGetData(void);
static void TestSortedListNextIter(void);
static void TestSortedListPrevIter(void);
static void TesSortedListIsSameIter(void);
static void TestSortedListPopFront(void);
static void TestSortedListPopBack(void);
static void TestSortedListForEach(void);
static void TestSortedListFind(void);
static void TestSortedListFindIf(void);
static void TestSortedListMerge(void);
static int AddNum(void *src, void *num);
static int CmpFunc(const void *data1, const void *data2);
static int IsMatch(const void *from, const void *param);


int main(void)
{
    TestSortedList();
    
    return 0;
}

static int CmpFunc(const void *data1, const void *data2)
{
	return (*(int *)data1 - *(int *)data2);
}

static int AddNum(void *src, void *num)
{
	(*(int *)src) += (*(int *)num);
	
	return 0;
}

static int IsMatch(const void *from, const void *param)
{
	return (*(int*)from == *(int*)param) ? TRUE :FALSE; 
}

static void TestSortedList(void)
{
	TestSortedListCreate();
}

static void TestSortedListCreate(void)
{
	sol_t *sol = SortedListCreate(CmpFunc);
	printf("SortedListCreate :\n");
    if (NULL != sol)
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
	TestSortedListIsEmpty();
	
	TestSortedListSize();
	
	TestSortedListInsert();
	
	TestSortedListRemove();
	
	TestSortedListGetData();
	
	TestSortedListNextIter();
	
	TestSortedListPrevIter();
	
	TesSortedListIsSameIter();
	
	TestSortedListPopFront();
	
	TestSortedListPopBack();
	
	TestSortedListForEach();
	
	TestSortedListFind();
	
	TestSortedListFindIf();
	
	TestSortedListMerge();
	
	SortedListDestroy(sol);
}

static void TestSortedListIsEmpty(void)
{
	sol_t *sol = SortedListCreate(CmpFunc);
	
	printf("SortedListIsEmpty :\n");
    if (SortedListIsEmpty(sol))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
	SortedListDestroy(sol);
}

static void TestSortedListSize(void)
{
	sol_t *sol = SortedListCreate(CmpFunc);
	
	printf("SortedListSize :\n");
    if (0 == SortedListSize(sol))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
	SortedListDestroy(sol);
}

static void TestSortedListInsert(void)
{
	sol_t *sol = SortedListCreate(CmpFunc);
	sol_iterator_t iter_begin = {0};
	int data1 = 2;
	int data2 = 1;
	
	SortedListInsert(sol, &data1);
	SortedListInsert(sol, &data2);
	iter_begin = SortedListBeginIter(sol);
	
	printf("TestSortedListInsert :\n");
    if (2 == SortedListSize(sol) && data2 == *(int *)SortedListGetData(iter_begin))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
	SortedListDestroy(sol);
}

static void TestSortedListRemove(void)
{
	sol_t *sol = SortedListCreate(CmpFunc);
	int data1 = 1;
	int data2 = 2;
	sol_iterator_t iter_begin = {0};
	
	SortedListInsert(sol, &data1);
	SortedListInsert(sol, &data2);
	iter_begin = SortedListBeginIter(sol);
	
	SortedListRemove(iter_begin);
	iter_begin = SortedListBeginIter(sol);
	
	printf("SortedListRemove :\n");
    if (1 == SortedListSize(sol) && data2 == *(int *)SortedListGetData(iter_begin))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
	SortedListDestroy(sol);
}

static void TestSortedListGetData(void)
{
	sol_t *sol = SortedListCreate(CmpFunc);
	int data1 = 1;
	int data2 = 2;
	sol_iterator_t iter_begin = {0};
	
	SortedListInsert(sol, &data1);
	SortedListInsert(sol, &data2);
	iter_begin = SortedListBeginIter(sol);
	
	SortedListRemove(iter_begin);
	iter_begin = SortedListBeginIter(sol);
	
	printf("SortedListGetData :\n");
    if (data2 == *(int *)SortedListGetData(iter_begin))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
	SortedListDestroy(sol);
}

static void TestSortedListNextIter(void)
{
	sol_t *sol = SortedListCreate(CmpFunc);
	int data1 = 1;
	int data2 = 2;
	sol_iterator_t iter_begin = {0};
	sol_iterator_t iter_next = {0};
	
	SortedListInsert(sol, &data1);
	SortedListInsert(sol, &data2);
	iter_begin = SortedListBeginIter(sol);
	iter_next = SortedListNextIter(iter_begin);
	
	printf("SortedListNextIter :\n");
    if (data2 == *(int *)SortedListGetData(iter_next))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
	SortedListDestroy(sol);
}
static void TestSortedListPrevIter(void)
{
	sol_t *sol = SortedListCreate(CmpFunc);
	int data1 = 1;
	int data2 = 2;
	
	sol_iterator_t iter = {0};
	sol_iterator_t iter_prev = {0};
	
	SortedListInsert(sol, &data1);
	iter = SortedListInsert(sol, &data2);
	iter_prev = SortedListPrevIter(iter);
	
	printf("SortedListPrevIter :\n");
    if (data1 == *(int *)SortedListGetData(iter_prev))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
	SortedListDestroy(sol);
}

static void TesSortedListIsSameIter(void)
{
	sol_t *sol = SortedListCreate(CmpFunc);
	int data1 = 1;
	
	sol_iterator_t iter_begin = {0};
	sol_iterator_t iter_prev = {0};
	
	SortedListInsert(sol, &data1);
	iter_begin = SortedListBeginIter(sol);
	iter_prev = SortedListPrevIter(SortedListEndIter(sol));
	
	printf("SortedListIsSameIter :\n");
    if (SortedListIsSameIter(iter_begin, iter_prev))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
	SortedListDestroy(sol);
}

static void TestSortedListPopFront(void)
{
	sol_t *sol = SortedListCreate(CmpFunc);
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	
	SortedListInsert(sol, &data3);
	SortedListInsert(sol, &data1);
	SortedListInsert(sol, &data2);
	
	printf("SortedListPopFront :\n");
    if (data1 == *(int *)SortedListPopFront(sol) && 2 == SortedListSize(sol) && data2 == *(int *)SortedListPopFront(sol) )
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
	SortedListDestroy(sol);
}

static void TestSortedListPopBack(void)
{
	sol_t *sol = SortedListCreate(CmpFunc);
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	
	SortedListInsert(sol, &data3);
	SortedListInsert(sol, &data1);
	SortedListInsert(sol, &data2);
	
	printf("SortedListPopBack :\n");
    if (data1 == *(int *)SortedListPopFront(sol) && 2 == SortedListSize(sol) && data3 == *(int *)SortedListPopBack(sol) )
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
	SortedListDestroy(sol);
}

static void TestSortedListForEach(void)
{
	sol_t *sol = SortedListCreate(CmpFunc);
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int num = 1;
	sol_iterator_t iter_from = {0};
	sol_iterator_t iter_to = {0};
	
	SortedListInsert(sol, &data3);
	SortedListInsert(sol, &data1);
	SortedListInsert(sol, &data2);
	
	iter_from = SortedListBeginIter(sol);
	iter_to = SortedListEndIter(sol);
	
	SortedListForEach(iter_from, iter_to, AddNum, &num);
	
	printf("SortedListForEach :\n");
    if (2 == *(int *)SortedListPopFront(sol))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
	
    if (3 == *(int *)SortedListPopFront(sol))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    if (4 == *(int *)SortedListPopFront(sol))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
	SortedListDestroy(sol);
}

static void TestSortedListFind(void)
{
	/*sol_t *bodek_assert = SortedListCreate(CmpFunc);*/
	
	sol_t *sol = SortedListCreate(CmpFunc);
	int data1 = 1;
	int data3 = 3;
	/*int data_bodek = 4;*/
	int num = 2;
	
	sol_iterator_t iter_from = {0};
	sol_iterator_t iter_to = {0};
	sol_iterator_t iter_tmp = {0};
	
	/*sol_iterator_t bodek_to = {0};*/
	
	SortedListInsert(sol, &data3);
	SortedListInsert(sol, &data1);
	
	/*SortedListInsert(bodek_assert, &data_bodek);
	bodek_to = SortedListBeginIter(bodek_assert);*/
	
	iter_from = SortedListBeginIter(sol);
	iter_to = SortedListEndIter(sol);
	
	/*iter_tmp = SortedListFind(sol, iter_from, bodek_to, &num);*/
	
	iter_tmp = SortedListFind(sol, iter_from, iter_to, &num);
	
	printf("SortedListFind :\n");
    if (SortedListIsSameIter(iter_to, iter_tmp))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    SortedListDestroy(sol);
    /*SortedListDestroy(bodek_assert);*/
}

static void TestSortedListFindIf(void)
{
	sol_t *sol = SortedListCreate(CmpFunc);
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int num1 = 2;
	int num2 = 4;
	
	sol_iterator_t iter_from = {0};
	sol_iterator_t iter_to = {0};
	sol_iterator_t iter_tmp1 = {0};
	sol_iterator_t iter_tmp2 = {0};
	
	SortedListInsert(sol, &data3);
	SortedListInsert(sol, &data1);
	SortedListInsert(sol, &data2);
	
	iter_from = SortedListBeginIter(sol);
	iter_to = SortedListEndIter(sol);
	
	iter_tmp1 = SortedListFindIf(iter_from, iter_to, IsMatch, &num1);
	iter_tmp2 = SortedListFindIf(iter_from, iter_to, IsMatch, &num2);
	
	printf("SortedListFindIf :\n");
    if (data2 == *(int *)SortedListGetData(iter_tmp1))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    if (SortedListIsSameIter(iter_tmp2, iter_to))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    SortedListDestroy(sol);
}

static void TestSortedListMerge(void)
{
	sol_t *dest_sol = SortedListCreate(CmpFunc);
	sol_t *src_sol = SortedListCreate(CmpFunc);
	int dest_data1 = 1;
	int dest_data2 = 5;
	int dest_data3 = 7;
	int src_data1 = 2;
	int src_data2 = 4;
	int src_data3 = 6;
	int src_data4 = 8;
	size_t i = 0;
	
	SortedListInsert(dest_sol, &dest_data1);
	SortedListInsert(dest_sol, &dest_data2);
	SortedListInsert(dest_sol, &dest_data3);
	
	SortedListInsert(src_sol, &src_data1);
	SortedListInsert(src_sol, &src_data2);
	SortedListInsert(src_sol, &src_data3);
	SortedListInsert(src_sol, &src_data4);
	
	printf("SortedListMerge :\n");
	
    SortedListMerge(dest_sol, src_sol);
    
    if (7 == SortedListSize(dest_sol) && 0 == SortedListSize(src_sol))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    printf("dest_sol after merge:\n");
    for (i = 0; !SortedListIsEmpty(dest_sol); ++i)
    {
    	printf("%d\n", *(int *)SortedListPopFront(dest_sol));
    }
    
	SortedListDestroy(dest_sol);
	SortedListDestroy(src_sol);
}

static void DrawSuccess(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;42mSUCCESS\033[0m\n\n");
}

static void DrawFailure(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;41mFailed, You should be ashamed of yourself!\033[0m\n\n");
}

