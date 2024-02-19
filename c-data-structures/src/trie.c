#include <stdlib.h> /* malloc */
#include <assert.h> /*assert*/

#include "trie.h"

#define FULL (1)
#define EMPTY (0)
#define NOT_FOUND (0)
#define DOUBLE_FREE (2)
#define FAIL (1)
#define SUCCESS (0)

typedef enum child_pos
{
	LEFT = 0,
	RIGHT = 1,
	NUM_OF_CHILDREN = 2
}child_pos_t;

struct trie_node
{
	trie_node_t *children[NUM_OF_CHILDREN];
    int is_full;
};

struct trie_tree
{
	trie_node_t *root;
};

/************************ Static Functions ************************/
static trie_node_t *CreateNode(void);
static void TrieFreeNode(trie_node_t *node);
static trie_node_t *TrieLeftChild(const trie_node_t *node);
static trie_node_t *TrieRightChild(const trie_node_t *node);
static int TrieInsertRec(trie_node_t *node, unsigned int requested_num, unsigned int *result, size_t n, size_t index);
static int TrieFreeRec(trie_node_t *node, unsigned int num_to_free, size_t n);
static size_t TrieCountRec(trie_node_t *node);
static int IsLeaf(trie_node_t *node);
/************************ Functions ************************/
trie_t *TrieCreate(void)
{
	trie_t *trie = (trie_t *)malloc(sizeof(trie_t));
	
	if (NULL == trie)
    {
        return NULL;
    }
    
    trie->root = CreateNode();
    if (NULL == trie->root)
    {
        free(trie);
        trie = NULL;
    }
    return trie;
}

void TrieDestroy(trie_t *trie)
{
    assert(NULL != trie);

    TrieFreeNode((trie->root));
    free(trie);
}

int Search(const trie_t *trie, unsigned int requested_num, size_t n)
{
    trie_node_t *current = NULL;
    int bit = 0;
    int i = 0;

    assert (NULL != trie);

    current = trie->root;

    for (i = n - 1; i >= 0 && FULL != current->is_full; --i)
    {   
        bit = ((requested_num >> i) & 1);
        if (NULL == current->children[bit])
        {
            return NOT_FOUND;
        }
        else
        {
            current = current->children[bit];
        }
    }
    return current->is_full;
}

int TrieSearchAndInsert(const trie_t *trie, unsigned int requested_num, unsigned int *result, size_t n)
{
    int num = requested_num;

    assert (NULL != trie);
    assert (NULL != result);

    while (Search(trie, num, n))
    {
        ++num;
    }
    return TrieInsert(trie, num, result, n);
}

int TrieInsert(const trie_t *trie, unsigned int requested_num, unsigned int *result, size_t n)
{
    assert (NULL != trie);
    assert (NULL != result);

    return TrieInsertRec(trie->root, requested_num, result, n, 0);
}

int TrieIsEmpty(const trie_t *trie)
{
	assert(NULL != trie);
    return (NULL == trie->root->children[LEFT] && NULL == trie->root->children[RIGHT]);
}

int TrieIsFULL(const trie_t *trie)
{
    return trie->root->is_full;
}

int TrieFree(const trie_t *trie, unsigned int num_to_free, size_t n)
{
    assert (NULL != trie);
    return TrieFreeRec(trie->root, num_to_free, n);
}

size_t TrieCount(const trie_t *trie)
{
    assert (NULL != trie);
    return TrieCountRec(trie->root);
}

static size_t TrieCountRec(trie_node_t *node)
{
    size_t count = 0;

    if (node == NULL)
    {
        return count;
    }
    if (IsLeaf(node) && node->is_full)
    {
        return count + 1;
    }
    count += TrieCountRec(node->children[LEFT]);
    count += TrieCountRec(node->children[RIGHT]);
    return count;
}
/************************ Static Functions ************************/
static trie_node_t *CreateNode(void)
{
    trie_node_t *new_node = (trie_node_t *)malloc(sizeof(trie_node_t));
    
    if (NULL == new_node)
    {
        return NULL;
    }
    new_node->children[LEFT] = NULL;
    new_node->children[RIGHT] = NULL;
    new_node->is_full = 0;

    return new_node;
}

static int IsLeaf(trie_node_t *node)
{
    return (NULL == node->children[LEFT] && NULL == node->children[RIGHT]);
}

static trie_node_t *TrieLeftChild(const trie_node_t *node)
{
    assert(NULL != node);

    return node->children[LEFT];
}

static trie_node_t *TrieRightChild(const trie_node_t *node)
{
    assert(NULL != node);

    return node->children[RIGHT];
}

static void TrieFreeNode(trie_node_t *node)
{
    if (node != NULL)
    {
        TrieFreeNode(TrieLeftChild(node));
        TrieFreeNode(TrieRightChild(node));
        free(node);
    }
}

static int TrieInsertRec(trie_node_t *node, unsigned int requested_num, unsigned int *result, size_t n, size_t index)
{
    int status = SUCCESS;
    int bit = ((requested_num >> (n - 1)) & 1);

    if (0 == n)
    {
        node->is_full = FULL;
        return status;
    }

    *result |= bit << (n -1);
    
    if (NULL == node->children[bit])
    {
        node->children[bit] = CreateNode();
        if (NULL == node->children[bit])
        {
            return FAIL;
        }
    }

    status = TrieInsertRec(node->children[bit], requested_num, result, n - 1, index + 1);
    if (SUCCESS == status && node->children[bit]->is_full)
    {
        if (NULL != node->children[!bit] && node->children[!bit]->is_full)
        {
            node->is_full = FULL;
        }
    }

    return status;
}

static int TrieFreeRec(trie_node_t *node, unsigned int num_to_free, size_t n)
{
    int status = SUCCESS;
    int bit = ((num_to_free >> (n - 1)) & 1);

    if (0 == n)
    {
        if (EMPTY == node->is_full)
        {
            return DOUBLE_FREE;
        }
        else
        {
            node->is_full = EMPTY;
            return status;
        } 
    }
    
    if (NULL != node->children[bit])
    {
        status = TrieFreeRec(node->children[bit], num_to_free, n - 1);
        node->is_full = EMPTY;
    }
    
    return status;
}

