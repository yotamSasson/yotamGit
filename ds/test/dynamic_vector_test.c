#include <stdio.h> /*printf*/
#include "dynamic_vector.h"

static void TestVector(void);
static void DrawSuccess(void);
static void DrawFailure(void);

int main(void)
{
    TestVector();
    return 0;
}

static void TestVector(void)
{
    int element1 = 1;
    int element2 = 2;
    int element3 = 3;
    int element4 = 4;
    size_t capacity1 = 1;
    size_t index1 = 0;
    size_t index2 = 2;
    size_t element_size1 = sizeof(element1);
    size_t count_push = 0;
    vector_t *vector1 = VectorCreate(capacity1, element_size1);
    vector_t *vector2 = VectorCreate(capacity1, element_size1);
    
    printf("VectorCreate :\n");
    if (capacity1 == VectorCapacity(vector1))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    printf("VectorSize :\n");
    if (count_push == VectorSize(vector1))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    printf("VectorIsEmpty :\n");
    if (VectorIsEmpty(vector1))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    printf("VectorPushBack :\n");
    VectorPushBack(vector1, &element1);
    ++count_push;
    if (count_push == VectorSize(vector1))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    printf("VectorGetAccessToElement :\n");
    if (element1 == *((int*)VectorGetAccessToElement(vector1 ,index1)))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    printf("VectorShrinkToSize :\n");
    VectorShrinkToSize(vector1);
    if ((VectorSize(vector1) + 1) == VectorCapacity(vector1))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    printf("VectorPopBack :\n");
    VectorPopBack(vector1);
    --count_push;
    if (VectorSize(vector1)  == count_push)
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    VectorPushBack(vector2, &element1);
    printf("VectorSize  after push one is: %ld \n", VectorSize(vector2));
    printf("VectorCapacity is: %ld\n", VectorCapacity(vector2));
    VectorPushBack(vector2, &element2);
    printf("VectorSize after push one more is: %ld \n", VectorSize(vector2));
    printf("VectorCapacity is: %ld\n", VectorCapacity(vector2));
    VectorPopBack(vector2);
    printf("VectorSize  after pop one is: %ld \n", VectorSize(vector2));
    printf("VectorCapacity is: %ld\n", VectorCapacity(vector2));
    VectorPushBack(vector2, &element2);
    VectorPushBack(vector2, &element3);
    VectorPushBack(vector2, &element4);
    printf("VectorCapacity after push three is: %ld\n", VectorCapacity(vector2));
    printf("VectorSize is: %ld \n", VectorSize(vector2));
    printf("VectorGetAccessToElement: %ld is: %d\n",index2 ,*((int*)VectorGetAccessToElement(vector2 ,index2)));
    VectorShrinkToSize(vector2);
    printf("VectorCapacity is: %ld\n", VectorCapacity(vector2));
    
    VectorDestroy(vector1);
    VectorDestroy(vector2);
}

static void DrawSuccess(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;42mSUCCESS\033[0m\n\n");
}

static void DrawFailure(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;41mFailed, You should be ashamed of yourself!\033[0m\n\n");
}

