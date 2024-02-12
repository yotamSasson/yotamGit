#ifndef MY_PROJECT_DYNAMIC_VECTOR_H__
#define MY_PROJECT_DYNAMIC_VECTOR_H__

#include <stddef.h> /*size_t*/

typedef struct dynamic_vector vector_t;

typedef enum status {SUCCESS, FAILURE} status_t;



/*
* Create Description:
*	creates new Dynamic Vector data structure.
*	the function allocates memory according to capacity * element_size for storing the data
*	plus additional memory for new struct that manages the vector functionality
*
* @Params:
*	capacity - number of possible elements in the vector.
*	element_size - size of one element in bytes.
*
* @Returns:
*	pointer to a vector that can be used to access vector functions.
*
* @Complexity
*	Time: Amortized O(1)
*/
vector_t *VectorCreate(size_t capacity, size_t element_size);

/*
* Description:
*	realeases allocated memory for vector and all it's data.
*
* @Params:
*	vector - pointer to a vector to destroy.
*
* @Returns:
*	void
*
* @Complexity
*	Time: Amortized O(1)
*/
void VectorDestroy(vector_t *vector);

/* 
* VectorCapacity Description:
* Checks the vector current maximum capacity.
*
* @param:
*	vector - The vector to chaeck its capacity 
*
* @Return
*	size_t variable represents the maximum number of elements the vector can currently store.
*
* @Complexity
*	Time: O(1)
*/
size_t VectorCapacity(const vector_t *vector);

/* 
* VectorSize Description:
* Checks the vector current number of elements in the vector.
*
* @param:
*	vector - The vector to chaeck its size(number of elements) 
*
* @Return
*	size_t variable represents the current number of elements.
*
* @Complexity
*	Time: O(1)
*/
size_t VectorSize(const vector_t *vector);

/* 
* VectorIsEmpty Description:
* Checks if the Vector is empty and return a feedback to the user.
*
* @param:
*	vector - The vector to check if is empty. 
*
* @Return
*	0 for success, 1 for failiur.
*
* @Complexity
*	Time: O(1)
*/
int VectorIsEmpty(const vector_t *vector);

/* 
* PushBack Description:
*	push an element to the end of the vector
*	if pushing to last avaiable space, capacity will be doubled.
*
* @param:
*	vector - pointer to a vector to add an element to.
*	element - pointer to an element to push back.
*
* @Return
*	returns 0 if the push was successful.
*	returns 1 if failed to increase size.
*
* @Complexity
*	Time: Amortized O(1)
*/
status_t VectorPushBack(vector_t *vector, const void *element);

/* 
* PopBack Description
*	pops an element from the end of the vector
*	the capacity might be reduced by an internal growth factor.
*	popping an element from an empty vector causes undefiend behaviour.
*
* @param:
*	vector - pointer to the vector.	 
*			
*
* @Return
*	None.
*
* @Complexity
*	Time: Amortized O(n) if reallocation is required / Amortized O(1) if not
*/
void VectorPopBack(vector_t *vector);

/*
* VectorGetAccessToElement Description:
* 	Returns a pointer to the element by a given index.
*	The pointer returned by the function might be invalidated by any Pop,
*	and by Push that reallocates.
*
* @param:
*	vector - pointer to the vector to read the element from. 
*       index - Index to the element in vector to read.
*			
* @Return
*	A pointer to the element stored in a given index. 
*
* @Complexity
*	Time: O(1)
*/
void *VectorGetAccessToElement(const vector_t *vector, size_t index);

/* 
* Reserve Description
*	Increasing the capacity of the vector to the given 'new_capacity'.
*	Increasing to a capacity less then the current capacity will not work .
*
* @param:
*	vector - pointer to a vector to allocate more space to.
*	new_capacity - the new capacity to set the vector to.
*
* @Return
*	returns 0 if the allocation was successful, 
*	returns 1 if failed to increase size.
*
* @Complexity
*	Time: O(n)
*/
status_t VectorReserve(vector_t *vector, size_t new_capacity);

/* 
* ShrinkToSize Description
*	Shrinks the capacity of a vector to the current number of elements + 1.
*
* @param:
*	vector - pointer to a vector to shrink to size.
*
* @Return
*	returns 0 if the allocation was successful, 
*	returns -1 if failed to shrink to size.
*
* @Complexity
*	Time: O(n)
*/
status_t VectorShrinkToSize(vector_t *vector);

#endif

