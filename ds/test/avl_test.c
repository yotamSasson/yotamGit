#include <stdio.h> /*printf*/
#include <stdlib.h> /* malloc */
#include "avl.h"

static void DrawSuccess(void);
static void DrawFailure(void);
static int CmpFunc(const void *data1, const void *data2);
static int AddNum(void *src, void *num);
static void Print(const void *data);
static void TestAVLCreate(void);
static void TestAVLIsEmpty(void);
static void TestAVLHeight(void);
static void TestAVLCount(void);
static void TestAVLInsert(void);
static void TestAVLFind(void);
static void TestAVLRemove(void);
static void TestAVLForEach(void);

int main(void)
{
	TestAVLCreate();
	TestAVLIsEmpty();
	TestAVLHeight();
	TestAVLCount();
	TestAVLInsert();
	TestAVLFind();
	TestAVLRemove();
	TestAVLForEach();
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

static void Print(const void *data)
{
	printf("%d\n", *((int *)data));
}

static void TestAVLCreate(void)
{
	avl_t *avl = AVLCreate(CmpFunc);
	
	printf("AVLCreate :\n");
	(NULL != avl) ? DrawSuccess() : DrawFailure();

	AVLDestroy(avl);
}

static void TestAVLIsEmpty(void)
{
	avl_t *avl = AVLCreate(CmpFunc);
	
	printf("AVLIsEmpt :\n");
	(AVLIsEmpty(avl)) ? DrawSuccess() : DrawFailure();
	
	AVLDestroy(avl);
}

static void TestAVLHeight(void)
{
	avl_t *avl = AVLCreate(CmpFunc);
	
	printf("AVLHeight :\n");
	(0 == AVLHeight(avl)) ? DrawSuccess() : DrawFailure();

	AVLDestroy(avl);
}

static void TestAVLCount(void)
{
	avl_t *avl = AVLCreate(CmpFunc);
	
	printf("AVLCount :\n");
	(0 == AVLCount(avl)) ? DrawSuccess() : DrawFailure();

	AVLDestroy(avl);
}

static void TestAVLInsert(void)
{
	avl_t *avl = AVLCreate(CmpFunc);
	int data1 = 10;
	int data2 = 20;
	int data3 = 7;
	int data4 = 2;
	int data5 = 6;
	int data6 = 1;
	int data7 = 3;
	int data8 = 8;
	int data9 = 9;
	int data10 = 5;
	int data11 = 30;
	int status = 0;
	
	status += AVLInsert(avl, &data1);
	status += AVLInsert(avl, &data2);
	status += AVLInsert(avl, &data3);
	status += AVLInsert(avl, &data4);
	status += AVLInsert(avl, &data5);
	status += AVLInsert(avl, &data6);
	status += AVLInsert(avl, &data7);
	status += AVLInsert(avl, &data8);
	status += AVLInsert(avl, &data9);
	status += AVLInsert(avl, &data10);
	status += AVLInsert(avl, &data11);
	
	printf("AVLInsert :\n");
	(0 == status) ? DrawSuccess() : DrawFailure();
	(11 == AVLCount(avl)) ? DrawSuccess() : DrawFailure();
	(4 == AVLHeight(avl)) ? DrawSuccess() : DrawFailure();
	
	AVLPrintTree(avl);
	
	AVLDestroy(avl);
}

static void TestAVLFind(void)
{
	avl_t *avl = AVLCreate(CmpFunc);
	int data1 = 10;
	int data2 = 5;
	int data3 = 7;
	int data4 = 2;
	int data5 = 6;
	int data6 = 1;
	int data7 = 3;
	int data8 = 8;
	int data9 = 9;
	int data10 = 20;
	int data11 = 30;
	int status = 0;
	int key = 9;
	
	status += AVLInsert(avl, &data1);
	status += AVLInsert(avl, &data2);
	status += AVLInsert(avl, &data3);
	status += AVLInsert(avl, &data4);
	status += AVLInsert(avl, &data5);
	status += AVLInsert(avl, &data6);
	status += AVLInsert(avl, &data7);
	status += AVLInsert(avl, &data8);
	status += AVLInsert(avl, &data9);
	status += AVLInsert(avl, &data10);
	status += AVLInsert(avl, &data11);
	
	printf("AVLFind :\n");
	(9 == *(int*)AVLFind(avl, &key)) ? DrawSuccess() : DrawFailure();
	
	AVLPrintTree(avl);
	
	AVLDestroy(avl);
}

static void TestAVLRemove(void)
{	
	avl_t *avl = AVLCreate(CmpFunc);
	int data1 = 10;
	int data2 = 5;
	int data3 = 7;
	int data4 = 2;
	int data5 = 6;
	int data6 = 1;
	int data7 = 3;
	int data8 = 8;
	int data9 = 9;
	int data10 = 20;
	int data11 = 30;
	int key1 = 10;
	int key2 = 30;
	int key3 = 20;
	int key4 = 8;
	int key5 = 0;
	int key6 = 5;
	int key7 = 7;
	int key8 = 9;
	
	AVLInsert(avl, &data1);
	AVLInsert(avl, &data2);
	AVLInsert(avl, &data3);
	AVLInsert(avl, &data4);
	AVLInsert(avl, &data5);
	AVLInsert(avl, &data6);
	AVLInsert(avl, &data7);
	AVLInsert(avl, &data8);
	AVLInsert(avl, &data9);
	AVLInsert(avl, &data10);
	AVLInsert(avl, &data11);
	
	printf("AVLRemove :\n");
	
	AVLRemove(avl, &key1);
	(NULL == AVLFind(avl, &key1)) ? DrawSuccess() : DrawFailure();
	(10 == AVLCount(avl)) ? DrawSuccess() : DrawFailure();
	
	AVLPrintTree(avl);
	
	AVLRemove(avl, &key2);
	(NULL == AVLFind(avl, &key2)) ? DrawSuccess() : DrawFailure();
	(9 == AVLCount(avl)) ? DrawSuccess() : DrawFailure();
	
	AVLPrintTree(avl);
	
	AVLRemove(avl, &key3);
	(NULL == AVLFind(avl, &key3)) ? DrawSuccess() : DrawFailure();
	(8 == AVLCount(avl)) ? DrawSuccess() : DrawFailure();
	
	AVLPrintTree(avl);
	
	AVLRemove(avl, &key4);
	(NULL == AVLFind(avl, &key4)) ? DrawSuccess() : DrawFailure();
	(7 == AVLCount(avl)) ? DrawSuccess() : DrawFailure();
	AVLPrintTree(avl);
	
	AVLRemove(avl, &key5);
	(NULL == AVLFind(avl, &key5)) ? DrawSuccess() : DrawFailure();
	(7 == AVLCount(avl)) ? DrawSuccess() : DrawFailure();
	AVLPrintTree(avl);
	
	AVLRemove(avl, &key6);
	(NULL == AVLFind(avl, &key6)) ? DrawSuccess() : DrawFailure();
	(6 == AVLCount(avl)) ? DrawSuccess() : DrawFailure();
	
	AVLPrintTree(avl);
	
	AVLRemove(avl, &key7);
	(NULL == AVLFind(avl, &key7)) ? DrawSuccess() : DrawFailure();
	(5 == AVLCount(avl)) ? DrawSuccess() : DrawFailure();
	
	AVLPrintTree(avl);
	
	AVLRemove(avl, &key8);
	(NULL == AVLFind(avl, &key8)) ? DrawSuccess() : DrawFailure();
	(4 == AVLCount(avl)) ? DrawSuccess() : DrawFailure();
	
	AVLPrintTree(avl);
	
	AVLDestroy(avl);
	
}

static void TestAVLForEach(void)
{
	avl_t *avl = AVLCreate(CmpFunc);
	int data1 = 10;
	int data2 = 5;
	int data10 = 20;
	int num_to_add = 1;
	
	AVLInsert(avl, &data1);
	AVLInsert(avl, &data2);
	AVLInsert(avl, &data10);
	
	
	printf("AVLForEach In order:\n");
	AVLForEach(avl, AddNum, &num_to_add, IN_ORDER);
	AVLPrintInOrder(avl, Print);
	
	printf("AVLForEach Post order:\n");
	AVLForEach(avl, AddNum, &num_to_add, POST_ORDER);
	AVLPrintPostOrder(avl, Print);
	
	printf("AVLForEach Pre order:\n");
	AVLForEach(avl, AddNum, &num_to_add, PRE_ORDER);
	AVLPrintPreOrder(avl, Print);
	
	AVLDestroy(avl);
}

static void DrawSuccess(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;42mSUCCESS\033[0m\n\n");
}

static void DrawFailure(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;41mFailed, You should be ashamed of yourself!\033[0m\n\n");
}

