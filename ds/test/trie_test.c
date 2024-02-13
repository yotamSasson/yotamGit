#include <stdio.h> /*printf*/
#include <assert.h> /*assert*/

#include "trie.h"

static void DrawSuccess(void);
static void DrawFailure(void);
static void TestTrieCreate(void);
static void TestTrieInsert(void);
static void TestTrieFree(void);
static void TestTrieCount(void);

int main (void)
{
    TestTrieCreate();
    TestTrieInsert();
    TestTrieFree();
    TestTrieCount();
    return 0;
}

/************************ Test Functions ************************/
static void TestTrieCreate(void)
{
    trie_t *trie = TrieCreate();
	
	printf("TrieCreate :\n");
	(NULL != trie) ? DrawSuccess() : DrawFailure();
	assert(NULL != trie);

	TrieDestroy(trie);
}

static void TestTrieInsert(void)
{
    trie_t *trie = TrieCreate();
	int status = 0;
    int status2 = 0;
    int status3 = 0;
    int status4 = 0;
    int status5 = 0;
    int requested = 0;
    int requested2 = 0;
    int requested3 = 1;
    int requested4 = 2;
    int requested5 = 2;
    unsigned int result = 0;
    unsigned int result2 = 0;
    unsigned int result3 = 0;
    unsigned int result4 = 0;
    unsigned int result5 = 0;

	printf("TrieInsert :\n");

    status = TrieSearchAndInsert(trie, requested, &result, 8);
    printf("The result is: %d\n", result);
	(0 == status) ? DrawSuccess() : DrawFailure();
	assert(0 == status);

    status2 = TrieSearchAndInsert(trie, requested2, &result2, 8);
    printf("The result2 is : %d \n", result2);
	(0 == status2) ? DrawSuccess() : DrawFailure();
	assert(0 == status2);
    
   /* printf("serch for result2\n");
    (Search(trie, result2))? DrawSuccess() : DrawFailure();*/

    status3 = TrieSearchAndInsert(trie, requested3, &result3, 8);
    printf("The result3 is : %d \n", result3);
	(0 == status3) ? DrawSuccess() : DrawFailure();
	assert(0 == status3);

    status4 = TrieSearchAndInsert(trie, requested4, &result4, 8);
    printf("The result4 is : %d \n", result4);
	(0 == status4) ? DrawSuccess() : DrawFailure();
	assert(0 == status4);

    status5 = TrieSearchAndInsert(trie, requested5, &result5, 8);
    printf("The result5 is : %d \n", result5);
	(0 == status5) ? DrawSuccess() : DrawFailure();
	assert(0 == status5);
    
	TrieDestroy(trie);
}

static void TestTrieFree(void)
{
    int status = 0;
    trie_t *trie = TrieCreate();
    int requested = 0;
    int requested2 = 1;
    int requested3 = 1;
    unsigned int result = 0;
    unsigned int result2 = 0;
    unsigned int result3 = 0;
    

    TrieSearchAndInsert(trie, requested, &result, 8);
    TrieSearchAndInsert(trie, requested2, &result2, 8);

    status = TrieFree(trie, requested2, 8);

    TrieSearchAndInsert(trie, requested3, &result3, 8);

    printf("TrieTRIEFree :\n");
    (0 == status) ? DrawSuccess() : DrawFailure();
    printf("The result3 is : %d \n", result3);
    assert(0 == status);

    TrieDestroy(trie);
}

static void TestTrieCount(void)
{
    size_t count = 0;
    trie_t *trie = TrieCreate();
    int requested = 0;
    int requested2 = 1;
    int requested3 = 2;
    int requested4 = 255;
    unsigned int result = 0;
    unsigned int result2 = 0;
    unsigned int result3 = 0;
    unsigned int result4 = 0;

    TrieSearchAndInsert(trie, requested, &result, 8);
    TrieSearchAndInsert(trie, requested2, &result2, 8);
    TrieSearchAndInsert(trie, requested3, &result3, 8);
    TrieSearchAndInsert(trie, requested4, &result4, 8);

    printf("TrieCount :\n");

    count = TrieCount(trie);
    (4 == count) ? DrawSuccess() : DrawFailure();
    assert(4 == count);
    
    TrieFree(trie, requested2, 8);
    TrieFree(trie, requested3, 8);

    count = TrieCount(trie);
    (2 == count) ? DrawSuccess() : DrawFailure();
    assert(2 == count);

    TrieDestroy(trie);
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

