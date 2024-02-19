#include <stdio.h> /*printf*/
#include <stdlib.h> /* malloc */
#include "bst.h"

static void DrawSuccess(void);
static void DrawFailure(void);
static int CmpFunc(const void *data1, const void *data2);
static int AddNum(void *src, void *num);
static void TestBSTCreate(void);
static void TestBSTIsEmpty(void);
static void TestBSTInsert(void);
static void TestBSTBeginIter(void);
static void TestBSTBeginIter(void);
static void TestBSTFind(void);
static void TestBSTPrevIter(void);
static void TestBSTRemove(void);
static void TestBSTForEach(void);
static void TestBSTHeight(void);

int main(void)
{
	TestBSTCreate();
	TestBSTIsEmpty();
	TestBSTInsert();
	TestBSTBeginIter();
	TestBSTFind();
	TestBSTPrevIter();
	TestBSTRemove();
	TestBSTForEach();
	TestBSTHeight();
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

static void TestBSTCreate(void)
{
	bst_t *bst = BSTCreate(CmpFunc);
	
	printf("BSTCreate :\n");
	(NULL != bst) ? DrawSuccess() : DrawFailure();
	
	BSTDestroy(bst);
}

static void TestBSTIsEmpty(void)
{
	bst_t *bst = BSTCreate(CmpFunc);
	
	printf("BSTIsEmpty :\n");
	(BSTIsEmpty(bst)) ? DrawSuccess() : DrawFailure();
	
	BSTDestroy(bst);
}

static void TestBSTInsert(void)
{
	bst_t *bst = BSTCreate(CmpFunc);
	int data1 = 8;
	int data2 = 6;
	int data3 = 3;
	int data4 = 13;
	 
	BSTInsert(bst, &data1);
	BSTInsert(bst, &data2);
	BSTInsert(bst, &data3);
	BSTInsert(bst, &data4);
	
	printf("BSTInsert :\n");
	(!BSTIsEmpty(bst) && 4 == BSTSize(bst)) ? DrawSuccess() : DrawFailure();
		
	BSTDestroy(bst);
}

static void TestBSTBeginIter(void)
{
	bst_t *bst = BSTCreate(CmpFunc);
	int data1 = 20;
	int data2 = 10;
	int data3 = 5;
	int data4 = 7;
	int data5 = 2;
	int data6 = 1;
	int data7 = 3;
	int data8 = 6;
	int data9 = 8;
	int data10 = 9;
	int data11 = 15;
	int data12 = 30;

	BSTInsert(bst, &data1);
	BSTInsert(bst, &data2);
	BSTInsert(bst, &data3);
	BSTInsert(bst, &data4);
	BSTInsert(bst, &data5);
	BSTInsert(bst, &data6);
	BSTInsert(bst, &data7);
	BSTInsert(bst, &data8);
	BSTInsert(bst, &data9);
	BSTInsert(bst, &data10);
	BSTInsert(bst, &data11);
	BSTInsert(bst, &data12);
	
	printf("BSTBeginIter :\n");
	(1 == *(int*)BSTGetData(BSTBeginIter(bst))) ? DrawSuccess() : DrawFailure();
	
	BSTDestroy(bst);
}

static void TestBSTFind(void)
{
	bst_t *bst = BSTCreate(CmpFunc);
	bst_iter_t iter = NULL;
	int data1 = 20;
	int data2 = 10;
	int data3 = 5;
	int data4 = 7;
	int data5 = 2;
	int data6 = 1;
	int data7 = 3;
	int data8 = 6;
	int data9 = 8;
	int data10 = 9;
	int data11 = 15;
	int data12 = 30;
	int key = 9;
	
	BSTInsert(bst, &data1);
	BSTInsert(bst, &data2);
	BSTInsert(bst, &data3);
	BSTInsert(bst, &data4);
	BSTInsert(bst, &data5);
	BSTInsert(bst, &data6);
	BSTInsert(bst, &data7);
	BSTInsert(bst, &data8);
	BSTInsert(bst, &data9);
	BSTInsert(bst, &data10);
	BSTInsert(bst, &data11);
	BSTInsert(bst, &data12);
	
	printf("BSTFind :\n");
	iter = BSTFind(bst, &key);
	(9 == *(int*)BSTGetData(iter)) ? DrawSuccess() : DrawFailure();
	
	BSTDestroy(bst);
}

static void TestBSTPrevIter(void)
{
	bst_t *bst = BSTCreate(CmpFunc);
	int data1 = 20;
	int data2 = 10;
	int data3 = 5;
	int data4 = 7;
	int data5 = 2;
	int data6 = 1;
	int data7 = 3;
	int data8 = 6;
	int data9 = 8;
	int data10 = 9;
	int data11 = 15;
	int data12 = 30;
	
	BSTInsert(bst, &data1);
	BSTInsert(bst, &data2);
	BSTInsert(bst, &data3);
	BSTInsert(bst, &data4);
	BSTInsert(bst, &data5);
	BSTInsert(bst, &data6);
	BSTInsert(bst, &data7);
	BSTInsert(bst, &data8);
	BSTInsert(bst, &data9);
	BSTInsert(bst, &data10);
	BSTInsert(bst, &data11);
	BSTInsert(bst, &data12);
	
	printf("BSTPrevIter :\n");
	(30 == *(int*)BSTGetData(BSTPrevIter(BSTEndIter(bst)))) ? DrawSuccess() : DrawFailure();
	
	BSTDestroy(bst);
}

static void TestBSTRemove(void)
{
	bst_t *bst = BSTCreate(CmpFunc);
	bst_iter_t iter = NULL;
	int data1 = 20;
	int data2 = 10;
	int data3 = 5;
	int data4 = 7;
	int data5 = 2;
	int data6 = 1;
	int data7 = 3;
	int data8 = 6;
	int data9 = 8;
	int data10 = 9;
	int data11 = 15;
	int data12 = 30;
	
	BSTInsert(bst, &data1);
	BSTInsert(bst, &data2);
	BSTInsert(bst, &data3);
	BSTInsert(bst, &data4);
	BSTInsert(bst, &data5);
	BSTInsert(bst, &data6);
	BSTInsert(bst, &data7);
	BSTInsert(bst, &data8);
	BSTInsert(bst, &data9);
	BSTInsert(bst, &data10);
	BSTInsert(bst, &data11);
	iter = BSTInsert(bst, &data12);
	
	printf("BSTRemove :\n");
	BSTRemove(iter);
	
	(11 == BSTSize(bst)) ? DrawSuccess() : DrawFailure();
	(20 == *(int*)BSTGetData(BSTPrevIter(BSTEndIter(bst)))) ? DrawSuccess() : DrawFailure();
	
	BSTRemove(BSTBeginIter(bst));
	(2 == *(int*)BSTGetData(BSTBeginIter(bst))) ? DrawSuccess() : DrawFailure();
	
	BSTDestroy(bst);
}

static void TestBSTForEach(void)
{
	bst_t *bst = BSTCreate(CmpFunc);
	bst_iter_t iter_from = NULL;
	bst_iter_t iter_to = NULL;
	bst_iter_t curr_node = NULL;
	int data1 = 20;
	int data2 = 10;
	int data3 = 5;
	int data4 = 7;
	int data5 = 2;
	int data6 = 1;
	int data7 = 3;
	int data8 = 6;
	int data9 = 8;
	int data10 = 9;
	int data11 = 15;
	int data12 = 30;
	int num_to_add = 1;
	int status = 0;
	
	BSTInsert(bst, &data1);
	BSTInsert(bst, &data2);
	BSTInsert(bst, &data3);
	BSTInsert(bst, &data4);
	BSTInsert(bst, &data5);
	BSTInsert(bst, &data6);
	BSTInsert(bst, &data7);
	BSTInsert(bst, &data8);
	BSTInsert(bst, &data9);
	BSTInsert(bst, &data10);
	BSTInsert(bst, &data11);
	BSTInsert(bst, &data12);
	
	iter_from = BSTBeginIter(bst);
	iter_to = BSTEndIter(bst);
	
	status = BSTForEach(iter_from, iter_to, AddNum, &num_to_add);
	printf("BSTForEach :\n");
	(0 == status) ? DrawSuccess() : DrawFailure();
	
	for (curr_node = iter_from; !BSTIsSameIter(curr_node, iter_to); curr_node = BSTNextIter(curr_node))
	{
		
		printf("%d\n", *(int*)BSTGetData(curr_node));
	}
	
	BSTDestroy(bst);
}

static void TestBSTHeight(void)
{
	bst_t *bst = BSTCreate(CmpFunc);
	bst_t *bst2 = BSTCreate(CmpFunc);
	
	int data1 = 20;
	int data2 = 10;
	int data3 = 5;
	int data4 = 7;
	int data5 = 2;
	int data6 = 1;
	int data7 = 3;
	int data8 = 6;
	int data9 = 8;
	int data10 = 9;
	int data11 = 15;
	int data12 = 30;
	size_t hight = 6;
	
	BSTInsert(bst, &data1);
	BSTInsert(bst, &data2);
	BSTInsert(bst, &data3);
	BSTInsert(bst, &data4);
	BSTInsert(bst, &data5);
	BSTInsert(bst, &data6);
	BSTInsert(bst, &data7);
	BSTInsert(bst, &data8);
	BSTInsert(bst, &data9);
	BSTInsert(bst, &data10);
	BSTInsert(bst, &data11);
	BSTInsert(bst, &data12);
	
	printf("BSTHeight :\n");
	(hight == BSTHeight(bst)) ? DrawSuccess() : DrawFailure();
	
	(0 == BSTHeight(bst2)) ? DrawSuccess() : DrawFailure();
	
	BSTDestroy(bst);
	BSTDestroy(bst2);
}

static void DrawSuccess(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;42mSUCCESS\033[0m\n\n");
}

static void DrawFailure(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;41mFailed, You should be ashamed of yourself!\033[0m\n\n");
}

