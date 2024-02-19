#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc*/
#include <string.h> /*memcpy*/

#include "sort.h"

#define WORD_SIZE (sizeof(size_t))
#define MAX2(lindex, rindex, heap) (heap[lindex] > heap[rindex] ? lindex : rindex)

static void Swap(int *val1, int *val2);
static int ArrayRange(int array[], size_t size, int *min);
static void CountingSortRadix(int array[], size_t size, int exp, int output[]);
static int Merge(int *arr_to_sort, size_t left, size_t mid, size_t right);
static int MergeSortHelper(int *arr_to_sort, size_t left, size_t right);
static size_t Partion(void *base ,size_t num_elements, size_t size, int (*compar)(const void *, const void *), size_t index);
static void PartionSwap(unsigned char *val1, unsigned char *val2 , size_t size);
static void HeapifyDown(int *heap, int index, int num_elements);

/************************ Functions ************************/

void BubbleSort(int array[], size_t size, int (*cmp_func)(const int lhs, const int rhs))
{
	size_t i = 0;
	size_t j = 0;
	size_t swapped = 1;
	
	assert(NULL != cmp_func);
	
	for (i = 0; i < size - 1 && 1 == swapped; ++i)
	{
		swapped = 0;
		
		for (j = 0; j < (size - 1 - i); ++j)
		{
			if (cmp_func(array[j], array[j + 1]) > 0)
			{
				Swap(array + j, array + j + 1);
				swapped = 1;
			}
		}
	}
}

void InsertionSort(int array[], size_t size, int (*cmp_func)(const int lhs, const int rhs))
{
	size_t i = 0;
	size_t j = 0;
	
	assert(NULL != cmp_func);
	
	for (i = 1; i < size; ++i)
	{
		j = i;
		
		while (j > 0 && cmp_func(array[j - 1], array[j]) > 0)
		{
			Swap(array + j - 1, array + j);
			--j;
		}
	}
}

void SelectionSort(int array[], size_t size, int (*cmp_func)(const int lhs, const int rhs))
{
	size_t i = 0;
	size_t j = 0;
	size_t min = 0;
	
	assert(NULL != cmp_func);
	
	for (i = 0; i < size - 1; ++i)
	{
		min = i;
		for (j = i + 1; j < size; ++j)
		{
			if (cmp_func(array[min], array[j]) > 0)
			{
				min = j;
			}
		}
		
		if (min != i)
		{
			Swap(array + i, array + min);
		}
	}
}

int CountingSort(int array[], size_t size)
{
	int min = 0;
	int range = ArrayRange(array, size, &min);
	size_t i = 0;
	size_t j = 0;
		
	int *count = (int *)calloc(range, sizeof(int));
	if (NULL == count)
	{
		return 1;
	}
	
	for (i = 0; i < size; ++i)
	{
		++count[array[i] - min];
	}
	
	for (i = 0; i < (size_t)range; ++i)
	{
		while (0 < count[i]--)
		{
			array[j++] = i + min;
		}
	}
	
	free(count);
	return 0;
}

int RadixSort(int array[], size_t size)
{
	int min = 0;
	int max = (ArrayRange(array, size, &min) - 1) + min;
	int exp = 0;
	int *output = (int *)calloc(size, sizeof(int));
	
	if (NULL == output)
	{
		return 1;
	}
	
	for (exp = 1; 0 < (max / exp); exp *= 10)
	{
		CountingSortRadix(array, size, exp ,output);
	}
	
	free(output);
	return 0;
}

ssize_t BinarySearchIterative(int *arr, size_t size, int num)
{
    ssize_t left = 0;
    ssize_t right = size - 1;
    ssize_t mid = 0;
    
    assert(NULL != arr);
    
    while (left <= right) 
    {
        mid = left + (right - left) / 2;
        if (arr[mid] == num) 
        {
            return mid;
        }
        else if (arr[mid] < num) 
        {
            left = mid + 1;
        }
        else 
        {
            right = mid - 1;
        }
    }
    return -1;
}

ssize_t BinarySearchRecursive(int *arr, size_t size, int num)
{
    size_t high = size - 1; 
    size_t low = 0;
    size_t mid = 0;
    ssize_t res = 0;
    
    if (size >= 1)
    {
        mid = (high + low) / 2;
        if (num == arr[mid])
        {
            return mid;
        }
        if (arr[mid] > num)
        {
            return BinarySearchRecursive(arr, mid, num);
        }
        
        if (arr[mid] < num)
        {
            res = BinarySearchRecursive(arr + mid + 1, size - mid - 1 ,num);
            return (-1 == res) ? res : (ssize_t)(mid + 1 + res);
        }
    }
    
    return -1;
}

int MergeSort(int *arr_to_sort, size_t num_elements)
{
	assert(NULL != arr_to_sort); 
	
	if (1 > num_elements)
	{
		return 1;
	}
	
	return MergeSortHelper(arr_to_sort, 0, num_elements - 1);
}

void HeapSort(int *arr_to_sort, int num_elements)
{
	int i = 0;

	assert(NULL != arr_to_sort);
	assert(0 != num_elements);

	for (i = (num_elements / 2) - 1; i >= 0; --i)
    {
        HeapifyDown(arr_to_sort, i, num_elements);
    }

	for (i = num_elements - 1; i > 0; --i)
    {
        Swap(&arr_to_sort[0], &arr_to_sort[i]);
        HeapifyDown(arr_to_sort, 0, i);
    }
}

/*============================== Helper functions ==============================*/

static void HeapifyDown(int *heap, int index, int num_elements)
{
    int lchild_index = 0;
    int rchild_index = 0;
    int max_index = 0;

    assert(NULL != heap);

    while (index < num_elements / 2)
    {
        lchild_index = (2 * index) + 1;
        rchild_index = (2 * index) + 2;

        if (rchild_index < num_elements)
        {
				
            max_index = MAX2(lchild_index, rchild_index, heap);
        }
        else
        {
            max_index = lchild_index;
        }

        if (heap[max_index] > heap[index])
        {
            Swap(&heap[max_index], &heap[index]);
            index = max_index;
        }
        else
        {
            break;
        }       
    }
}

void Qsort(void *base, size_t num_elements, size_t size, int (*compar)(const void *, const void *))
{
	size_t pivot = 0;
	
	assert(NULL != base); 
	
	if (1 >= num_elements)
	{
		return;
	}
	
	pivot = num_elements - 1;
	pivot = Partion(base, num_elements, size, compar, pivot);
	Qsort((char *)base, pivot, size, compar);
	Qsort((char *)base + (pivot + 1) * size, num_elements - pivot - 1, size, compar);
}

static size_t Partion(void *base ,size_t num_elements, size_t size, int (*compar)(const void *, const void *), size_t index)
{	
	size_t count = 0;
	size_t last_index = num_elements - 1;
	size_t i = 0;
	unsigned char *base_ptr = NULL;
	unsigned char *pivot  = NULL;
	
	assert(NULL != base); 
	
	base_ptr = (unsigned char *)base;
	pivot  = base_ptr + index * size;
	
	for (i = 0; i < last_index; ++i)
	{
		if (compar(base_ptr + i * size, pivot) <= 0)
		{
			PartionSwap(base_ptr + count * size, base_ptr + i * size, size);
	     	++count;
		}
	}
	
	PartionSwap(base_ptr + last_index * size, base_ptr + count * size, size);
	return count;
}

static void PartionSwap(unsigned char *val1, unsigned char *val2 , size_t size)
{
	size_t i = 0;
	
	assert( NULL != val1 && NULL != val2);
	
	if (0 != memcmp(val1, val2, size))
	{
    	for ( i = 0; i < size; ++i)
    	{
        	val1[i] ^= val2[i];
        	val2[i] ^= val1[i];
        	val1[i] ^= val2[i];
    	}
    }
}  
 
static int MergeSortHelper(int *arr_to_sort, size_t left, size_t right)
{
	size_t mid = 0;
	int status = 0;
	
	if (left < right)
	{
		mid = (right + left) / 2;
		if (0 != MergeSortHelper(arr_to_sort, left, mid))
		{
			return 1;
		}
		if (0 != MergeSortHelper(arr_to_sort, mid + 1, right))
		{
			return 1;
		}
		status =  Merge(arr_to_sort, left, mid, right);
	}
	
	return status;
}

static int Merge(int *arr_to_sort, size_t left, size_t mid, size_t right)
{
	int *temp_arr = NULL;
	size_t left_index = left;
	size_t right_index = mid + 1;
	size_t i = 0;
	size_t temp_size = right - left + 1;
	
	assert(NULL != arr_to_sort);
	
	temp_arr = (int*)malloc(sizeof(int) * temp_size);
	
	if (NULL == temp_arr)
	{
		return 1;
	}
	
	while (left_index <= mid && right_index <= right)
	{
		if (arr_to_sort[left_index] <= arr_to_sort[right_index])
		{
			temp_arr[i++] = arr_to_sort[left_index++];
		}
		else 
		{
			temp_arr[i++] = arr_to_sort[right_index++];
		}
	}
	
	while (left_index <= mid)
	{
		temp_arr[i++] = arr_to_sort[left_index++];
	}
	
	while (right_index <= right)
	{
		temp_arr[i++] = arr_to_sort[right_index++];
	}
	
	memcpy(arr_to_sort + left, temp_arr, temp_size * sizeof(int));
	
	free(temp_arr);
	return 0;
}

static void CountingSortRadix(int array[], size_t size, int exp, int output[])
{
	size_t i = 0;
	int count[10] = {0};
	
	for (i = 0; i < size; ++i)
	{
		++count[(array[i] / exp) % 10];
	}
	
	for (i = 1; i < 10; ++i)
	{
		count[i] += count[i - 1];
	}
	
	for (i = size - 1; (int)i >= 0; --i) 
	{
		output[count[(array[i] / exp) % 10] - 1] = array[i];
        --count[(array[i] / exp) % 10];
	}
	
	for (i = 0; i < size; ++i) 
    {
        array[i] = output[i];
    }
}

static int ArrayRange(int array[], size_t size, int *min)
{
	size_t i = 0;
	int max = array[0];
	*min = array[0];
	
	for (i = 1; i < size; ++i)
	{
		if (array[i] < *min)
		{
			*min = array[i];
		}
		else if (array[i] > max)
		{
			max = array[i];
		}
	}
	
	return (max - *min) + 1;
}
 
static void Swap(int *val1, int *val2)
{
   int tmp = *val1;
   
   assert( NULL != val1 && NULL != val2);
   
   *val1 = *val2;
   *val2 = tmp;
} 
