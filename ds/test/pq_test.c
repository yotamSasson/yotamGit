#include <stdio.h> /*printf*/
#include "pq.h"

static int IsMatch(const void *from, const void *param);
static int priority_func(const void *lhs, const void *rhs);
static void DrawSuccess(void);
static void DrawFailure(void);
static void TestPQ(void);
static void TestPQCreate(void);
static void TestPQEnqueue(void);
static void TestPQIsEmpty(void);
static void TestPQDequeue(void);
static void TestPQSize(void);
static void TestPQPeek(void);
static void TestPQClear(void);
static void TestPQErase(void);
static void TestPQMerge(void);

int main(void)
{
	TestPQ();
	
	return 0;
}
static int priority_func(const void *lhs, const void *rhs)
{
	return (*(int *)rhs - *(int *)lhs);
}

static int IsMatch(const void *from, const void *param)
{
	return (*(int*)from == *(int*)param); 
}

static void TestPQ(void)
{
	TestPQCreate();
	TestPQEnqueue();
	TestPQDequeue();
	TestPQIsEmpty();
	TestPQSize();
	TestPQPeek();
	TestPQClear();
	TestPQErase();
	/*TestPQMerge();*/
}

static void TestPQCreate(void)
{
	pq_t *pq = PQCreate(priority_func);
	printf("PQCreatee :\n");
    (NULL != pq) ? DrawSuccess() : DrawFailure();
    
    PQDestroy(pq);
}

static void TestPQEnqueue(void)
{
	pq_t *pq = PQCreate(priority_func);
	int data = 4;
	
	printf("PQEnqueue :\n");
    (0 == PQEnqueue(pq, &data)) ? DrawSuccess() : DrawFailure();
    
	PQDestroy(pq);
}

static void TestPQDequeue(void)
{
	pq_t *pq = PQCreate(priority_func);
	int data = 4;
	
	PQEnqueue(pq, &data);
	PQDequeue(pq);
	
	printf("PQDequeue :\n");
    (PQIsEmpty(pq)) ? DrawSuccess() :  DrawFailure();
    
	PQDestroy(pq);
}

static void TestPQIsEmpty(void)
{
	pq_t *pq = PQCreate(priority_func);
	
	printf("PQIsEmpty :\n");
    (PQIsEmpty(pq)) ?  DrawSuccess() : DrawFailure();
    
	PQDestroy(pq);
}

static void TestPQSize(void)
{
	pq_t *pq = PQCreate(priority_func);
	int data = 1;
	int data2 = 2;
	int data3 = 3;
	
	PQEnqueue(pq, &data);
	PQEnqueue(pq, &data2);
	PQEnqueue(pq, &data3);
	
	printf("PQSize :\n");
    (3 == PQSize(pq)) ?  DrawSuccess() : DrawFailure();
    
	PQDestroy(pq);
}

static void TestPQPeek(void)
{
	pq_t *pq = PQCreate(priority_func);
	int data = 1;
	int data2 = 2;
	int data3 = 3;
	
	PQEnqueue(pq, &data);
	PQEnqueue(pq, &data2);
	PQEnqueue(pq, &data3);
	
	printf("PQPeek :\n");
    (3 == *((int*)PQPeek(pq))) ? DrawSuccess() : DrawFailure();
    
	PQDequeue(pq);
	printf("PQPeek :\n");
    (2 == *((int*)PQPeek(pq))) ?  DrawSuccess() : DrawFailure();
    
	PQDestroy(pq);
}

static void TestPQClear(void)
{
	pq_t *pq = PQCreate(priority_func);
	int data = 1;
	int data2 = 2;
	int data3 = 3;
	
	PQEnqueue(pq, &data);
	PQEnqueue(pq, &data2);
	PQEnqueue(pq, &data3);
	
	PQClear(pq);
	
	printf("PQClear :\n");
    (PQIsEmpty(pq)) ? DrawSuccess() : DrawFailure();
    
	PQEnqueue(pq, &data);
	(1 == PQSize(pq)) ?  DrawSuccess() : DrawFailure();

	PQDestroy(pq);
}

static void TestPQErase(void)
{
	pq_t *pq = PQCreate(priority_func);
	int data = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	int data5 = 5;
	int data6 = 0;

	int num_to_erase = 2;
	
	
	PQEnqueue(pq, &data);
	PQEnqueue(pq, &data2);
	PQEnqueue(pq, &data3);
	PQEnqueue(pq, &data4);
	PQEnqueue(pq, &data5);
	PQEnqueue(pq, &data6);
	
	printf("PQErase :\n");
    (num_to_erase == (*(int*)PQErase(pq, IsMatch, &num_to_erase))) ? DrawSuccess() : DrawFailure();

	PQDequeue(pq);
	PQDequeue(pq);
	(3 == *((int*)PQPeek(pq))) ?  DrawSuccess() : DrawFailure();
    
	PQDestroy(pq);
}

/*static void TestPQMerge(void)
{
	pq_t *pq_dest = PQCreate(priority_func);
	pq_t *pq_src = PQCreate(priority_func);
	int dest_data1 = 1;
	int dest_data2 = 5;
	int dest_data3 = 7;
	int src_data1 = 2;
	int src_data2 = 4;
	int src_data3 = 6;
	int src_data4 = 8;
	
	PQEnqueue(pq_dest, &dest_data1);
	PQEnqueue(pq_dest, &dest_data2);
	PQEnqueue(pq_dest, &dest_data3);
	
	PQEnqueue(pq_src, &src_data1);
	PQEnqueue(pq_src, &src_data2);
	PQEnqueue(pq_src, &src_data3);
	PQEnqueue(pq_src, &src_data4);
	
	printf("PQMerge :\n");
	
   PQMerge(pq_dest, pq_src);
    
    if (7 == PQSize(pq_dest) && 0 == PQSize(pq_src))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
	
	PQDestroy(pq_dest);
	PQDestroy(pq_src);
}*/

static void DrawSuccess(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;42mSUCCESS\033[0m\n\n");
}

static void DrawFailure(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;41mFailed, You should be ashamed of yourself!\033[0m\n\n");
}

