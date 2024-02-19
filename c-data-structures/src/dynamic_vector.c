#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */
#include "dynamic_vector.h"

struct dynamic_vector
{
	void *data;
	size_t size;
	size_t capacity;
    size_t element_size;
};

#define GROWTH_FACTOR ((size_t) 2)
#define SHRINKING_FACTOR ((size_t) 4)

vector_t *VectorCreate(size_t capacity, size_t element_size)
{
	vector_t *vector = NULL;
	
	assert(0 != capacity);
	
	vector = (vector_t *)malloc(sizeof(vector_t));
	if (NULL == vector)
	{
		printf("vector allocation failed!\n");
		return NULL;
	}

	vector->data = malloc(capacity * sizeof(void *));
	if (NULL == vector->data)
	{
		printf("vector's data allocation failed!\n");
		free(vector);
		return NULL;
	}
	
	vector->size = 0;
	vector->capacity = capacity;
    vector->element_size = element_size;
	
	return vector;
}

void VectorDestroy(vector_t *vector)
{
	assert(NULL != vector);
	
	free(vector->data);
	free(vector);
}

status_t VectorPushBack(vector_t *vector, const void *element)
{
	int realloc_fail_flag = 0;
		
	assert(NULL != vector);
	assert(NULL != element);
	 	
	if (vector->size == vector->capacity - 1)
	{
		realloc_fail_flag = VectorReserve(vector, (vector->capacity * GROWTH_FACTOR));
	}
	
	memcpy((char *)vector->data + (vector->size * vector->element_size), element, vector->element_size);
	
	++vector->size;
		
	return realloc_fail_flag;
}

void VectorPopBack(vector_t *vector)
{
	void *tmp = NULL;
	
	assert(NULL != vector);
	
	--(vector->size);
	
	if (vector->size <= (vector->capacity / SHRINKING_FACTOR))
	{
		tmp = realloc(vector->data, (vector->capacity / GROWTH_FACTOR) * sizeof(void *));
		if (NULL != tmp)
		{
			vector->data = tmp;
			vector->capacity /= GROWTH_FACTOR;
		}
	}
}

void *VectorGetAccessToElement(const vector_t *vector, size_t index)
{
	assert(NULL != vector);
	
	return ((char *)vector->data + (index * vector->element_size));
}

status_t VectorReserve(vector_t *vector, size_t reserve_size)
{
	void *tmp = NULL;
	
	assert(NULL != vector);
	
	if (vector->capacity >= reserve_size)
	{
		return SUCCESS;
	}
	
	tmp = realloc(vector->data, reserve_size * vector->element_size);
	if (NULL == tmp)
	{
		perror("\n\033[1;29mSystem:\033[0m Allocating adittional data failed!\n");
		return FAILURE;
	}
	
	vector->data = tmp;
	vector->capacity = reserve_size;
	
	return SUCCESS;
}

status_t VectorShrinkToSize(vector_t *vector)
{
	void *tmp = NULL;
	
	assert(NULL != vector);
	
	tmp = realloc(vector->data, (vector->size + 1) * sizeof(void *));	
	if (NULL == vector->data)
	{
		printf("\n\033[1;29mSystem:\033[0m Allocating adittional data failed!\n");
		return FAILURE;
	}
	
	vector->data = tmp;
	vector->capacity = vector->size + 1;
	
	return SUCCESS;
}

int VectorIsEmpty(const vector_t *vector)
{
	assert(NULL != vector);
	
	return (0 == vector->size);
}

size_t VectorCapacity(const vector_t *vector)
{
	assert(NULL != vector);
	
	return vector->capacity;
}

size_t VectorSize(const vector_t *vector)
{
	assert(NULL != vector);
	
	return vector->size;
}
