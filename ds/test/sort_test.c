#include <stdio.h> /*printf*/
#include <time.h> /*time*/
#include <stdlib.h> /*srand, rand , qsort*/

#include "sort.h"

#define SIZE 5000

static void DrawSuccess(void);
static void DrawFailure(void);
static int CmpFunc2(const void *data1, const void *data2);
static int CmpFunc(const int lhs, const int rhs);
static void TestBubbleSort(void);
static void TestInsertionSort(void);
static void TestSelectionSort(void);
static void TestCountingSort(void);
static void TestRadixSort(void);
static void TestBinarySearchIterative(void);
static void TestBinarySearchRecursive(void);
static void TestMergeSort(void);
static void TestQsort(void);
static void TestHeapSort(void);

int main(void)
{
	TestBubbleSort();
	TestInsertionSort();
	TestSelectionSort();
	TestCountingSort();
	TestRadixSort();
	TestBinarySearchIterative();
	TestBinarySearchRecursive();
	TestMergeSort();
	TestQsort();
	TestHeapSort();
	return 0;
}

static int CmpFunc(const int lhs, const int rhs)
{
	return (lhs - rhs);
}

static int CmpFunc2(const void *data1, const void *data2)
{
	return (*(int *)data1 - *(int *)data2);
}

static void TestBubbleSort(void)
{
	int array1[SIZE];
	int array2[SIZE];
	size_t i = 0;
	int status = 0;
	clock_t start = 0;
	clock_t end = 0;
	double qsort_time = 0;
	double bubble_time = 0;
	
	srand(time(NULL));
	
	for (i = 0; i < SIZE; ++i)
	{
		array1[i] = rand() % ((99) + 1);
		array2[i] = array1[i];
	}
	
	start = clock();
	qsort(array1, SIZE, sizeof(int), CmpFunc2);
	end = clock();
	qsort_time = (double)(end - start) / CLOCKS_PER_SEC;
	
	start = clock();
	BubbleSort(array2, SIZE, CmpFunc);
	end = clock();
	bubble_time = (double)(end - start) / CLOCKS_PER_SEC;
	
	printf("BubbleSort :\n");
	for (i = 0; i < (SIZE - 1) && 0 == status; ++i)
	{
		if (CmpFunc(array2[i], array2[i + 1]) > 0)
		{
			status = 1;
		}
	}
	(0 == status) ? DrawSuccess() : DrawFailure();
	
	printf("Time taken by qsort: %f seconds\n", qsort_time);
    printf("Time taken by BubbleSort: %f seconds\n", bubble_time);
}

static void TestInsertionSort(void)
{
	int array1[SIZE];
	int array2[SIZE];
	size_t i = 0;
	int status = 0;
	clock_t start = 0;
	clock_t end = 0;
	double qsort_time = 0;
	double insertion_time = 0;
	
	srand(time(NULL));
	
	for (i = 0; i < SIZE; ++i)
	{
		array1[i] = rand() % ((99) + 0);
		array2[i] = array1[i];
	}
	
	start = clock();
	qsort(array1, SIZE, sizeof(int), CmpFunc2);
	end = clock();
	qsort_time = (double)(end - start) / CLOCKS_PER_SEC;
	
	start = clock();
	InsertionSort(array2, SIZE, CmpFunc);
	end = clock();
	insertion_time = (double)(end - start) / CLOCKS_PER_SEC;
	
	printf("InsertionSort :\n");
	for (i = 0; i < (SIZE - 1) && 0 == status; ++i)
	{
		if (CmpFunc(array2[i], array2[i + 1]) > 0)
		{
			status = 1;
		}
	}
	(0 == status) ? DrawSuccess() : DrawFailure();
	
	printf("Time taken by qsort: %f seconds\n", qsort_time);
    printf("Time taken by InsertionSort: %f seconds\n", insertion_time);
}

static void TestSelectionSort(void)
{
	int array1[SIZE];
	int array2[SIZE];
	size_t i = 0;
	int status = 0;
	clock_t start = 0;
	clock_t end = 0;
	double qsort_time = 0;
	double selection_time = 0;
	
	srand(time(NULL));
	
	for (i = 0; i < SIZE; ++i)
	{
		array1[i] = rand() % ((99) + 1);
		array2[i] = array1[i];
	}
	
	start = clock();
	qsort(array1, SIZE, sizeof(int), CmpFunc2);
	end = clock();
	qsort_time = (double)(end - start) / CLOCKS_PER_SEC;
	
	start = clock();
	SelectionSort(array2, SIZE, CmpFunc);
	end = clock();
	selection_time = (double)(end - start) / CLOCKS_PER_SEC;
	
	printf("SelectionSort :\n");
	for (i = 0; i < (SIZE - 1) && 0 == status; ++i)
	{
		if (CmpFunc(array2[i], array2[i + 1]) > 0)
		{
			status = 1;
		}
	}
	(0 == status) ? DrawSuccess() : DrawFailure();
	
	printf("Time taken by qsort: %f seconds\n", qsort_time);
    printf("Time taken by SelectionSort: %f seconds\n", selection_time);
}

static void TestCountingSort(void)
{
	int array1[SIZE];
	int array2[SIZE];
	size_t i = 0;
	int status = 0;
	clock_t start = 0;
	clock_t end = 0;
	double qsort_time = 0;
	double counting_time = 0;
	
	srand(time(NULL));
	
	for (i = 0; i < SIZE; ++i)
	{
		array1[i] = rand() % ((200) - 100);
		array2[i] = array1[i];
	}
	
	start = clock();
	qsort(array1, SIZE, sizeof(int), CmpFunc2);
	end = clock();
	qsort_time = (double)(end - start) / CLOCKS_PER_SEC;
	
	start = clock();
	CountingSort(array2, SIZE);
	end = clock();
	counting_time = (double)(end - start) / CLOCKS_PER_SEC;
	
	printf("CountingSort :\n");
	for (i = 0; i < (SIZE - 1) && 0 == status; ++i)
	{
		if (CmpFunc(array2[i], array2[i + 1]) > 0)
		{
			status = 1;
		}
	}
	(0 == status) ? DrawSuccess() : DrawFailure();
	
	printf("Time taken by qsort: %f seconds\n", qsort_time);
    printf("Time taken by CountingSort: %f seconds\n", counting_time);
}

static void TestRadixSort(void)
{
	int array1[SIZE];
	int array2[SIZE];
	size_t i = 0;
	int status = 0;
	clock_t start = 0;
	clock_t end = 0;
	double qsort_time = 0;
	double radix_time = 0;
	
	srand(time(NULL));
	
	for (i = 0; i < SIZE; ++i)
	{
		array1[i] = rand() % (1000000);
		array2[i] = array1[i];
	}
	
	start = clock();
	qsort(array1, SIZE, sizeof(int), CmpFunc2);
	end = clock();
	qsort_time = (double)(end - start) / CLOCKS_PER_SEC;
	
	start = clock();
	RadixSort(array2, SIZE);
	end = clock();
	radix_time = (double)(end - start) / CLOCKS_PER_SEC;
	
	printf("RadixSort :\n");
	for (i = 0; i < (SIZE - 1) && 0 == status; ++i)
	{
		if (CmpFunc(array2[i], array2[i + 1]) > 0)
		{
			status = 1;
		}
	}
	(0 == status) ? DrawSuccess() : DrawFailure();
	
	printf("Time taken by qsort: %f seconds\n", qsort_time);
    printf("Time taken by RadixSort: %f seconds\n", radix_time);
}

static void TestBinarySearchIterative(void)
{
	int arr[] = {1, 2, 3, 4, 5, 6};
	size_t size = sizeof(arr) / sizeof(arr[0]);
	int num = 1;
	int num2 = 0;
	int num3 = 5;
	int num4 = 3;
	int num5 = 8;
	
	printf("BinarySearchIterative :\n");

	(0 == BinarySearchIterative(arr, size, num)) ? DrawSuccess() : DrawFailure();
	
	(-1 == BinarySearchIterative(arr, size, num2)) ? DrawSuccess() : DrawFailure();
	
	(4 == BinarySearchIterative(arr, size, num3)) ? DrawSuccess() : DrawFailure();
	
	(2 == BinarySearchIterative(arr, size, num4)) ? DrawSuccess() : DrawFailure();
	
	(-1 == BinarySearchIterative(arr, size, num5)) ? DrawSuccess() : DrawFailure();
}

static void TestBinarySearchRecursive(void)
{
	int arr[] = {1, 2, 3, 4, 5, 6};
	size_t size = sizeof(arr) / sizeof(arr[0]);
	int num = 6;
	int num2 = 0;
	int num3 = 5;
	int num4 = 3;
	int num5 = 8;
	
	printf("BinarySearchRecursive :\n");

	(5 == BinarySearchRecursive(arr, size, num)) ? DrawSuccess() : DrawFailure();
	
	(-1 == BinarySearchRecursive(arr, size, num2)) ? DrawSuccess() : DrawFailure();
	
	(4 == BinarySearchRecursive(arr, size, num3)) ? DrawSuccess() : DrawFailure();
	
	(2 == BinarySearchRecursive(arr, size, num4)) ? DrawSuccess() : DrawFailure();
	
	(-1 == BinarySearchRecursive(arr, size, num5)) ? DrawSuccess() : DrawFailure();
}

static void TestMergeSort(void)
{
	int arr[] = {9, 6, 12, 5, 0, 4, 1};
	size_t size = sizeof(arr) / sizeof(arr[0]);
	size_t i = 0;
	int status = 0;
	
	printf("MergeSort :\n");
	MergeSort(arr, size);
	
	for (i = 0; i < (size - 1) && 0 == status; ++i)
	{
		if (CmpFunc(arr[i], arr[i + 1]) > 0)
		{
			status = 1;
		}
	}
	(0 == status) ? DrawSuccess() : DrawFailure();	
}

static void TestQsort(void)
{
	int array1[SIZE];
	int array2[SIZE];
	size_t i = 0;
	int status = 0;
	clock_t start = 0;
	clock_t end = 0;
	double qsort_time = 0;
	double Qsort_time = 0;
	
	srand(time(NULL));
	
	for (i = 0; i < SIZE; ++i)
	{
		array1[i] = rand() % ((99) + 1);
		array2[i] = array1[i];
	}
	
	start = clock();
	qsort(array1, SIZE, sizeof(int), CmpFunc2);
	end = clock();
	qsort_time = (double)(end - start) / CLOCKS_PER_SEC;
	
	start = clock();
	Qsort(array2, SIZE,sizeof(int), CmpFunc2);
	end = clock();
	Qsort_time = (double)(end - start) / CLOCKS_PER_SEC;
	
	printf("Qsort :\n");
	for (i = 0; i < (SIZE - 1) && 0 == status; ++i)
	{
		if (CmpFunc(array2[i], array2[i + 1]) > 0)
		{
			status = 1;
		}
	}
	(0 == status) ? DrawSuccess() : DrawFailure();
	
	printf("Time taken by qsort: %f seconds\n", qsort_time);
    printf("Time taken by Qsort: %f seconds\n", Qsort_time);
}

static void TestHeapSort(void)
{
	int array1[SIZE];
	int array2[SIZE];
	size_t i = 0;
	int status = 0;
	clock_t start = 0;
	clock_t end = 0;
	double qsort_time = 0;
	double heapsort_time = 0;
	
	srand(time(NULL));
	
	for (i = 0; i < SIZE; ++i)
	{
		array1[i] = rand() % ((99) + 1);
		array2[i] = array1[i];
	}
	
	start = clock();
	qsort(array1, SIZE, sizeof(int), CmpFunc2);
	end = clock();
	qsort_time = (double)(end - start) / CLOCKS_PER_SEC;
	
	start = clock();
	HeapSort(array2, SIZE);
	end = clock();
	heapsort_time = (double)(end - start) / CLOCKS_PER_SEC;
	
	printf("HeapSort :\n");
	for (i = 0; i < (SIZE - 1) && 0 == status; ++i)
	{
		if (CmpFunc(array2[i], array2[i + 1]) > 0)
		{
			status = 1;
		}
	}
	(0 == status) ? DrawSuccess() : DrawFailure();
	
	printf("Time taken by qsort: %f seconds\n", qsort_time);
    printf("Time taken by HeapSort: %f seconds\n", heapsort_time);
}

static void DrawSuccess(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;42mSUCCESS\033[0m\n\n");
}

static void DrawFailure(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;41mFailed, You should be ashamed of yourself!\033[0m\n\n");
}


