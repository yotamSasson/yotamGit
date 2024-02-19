#include <stdlib.h> /* malloc */
#include <assert.h> /*assert*/

#include "bst.h"

#define DUMMY_LEFT_CHILD(bst) ((bst)->dummy_root.children[LEFT])
#define MAX2(a, b) (((a) > (b)) ? (a) : (b))

typedef enum child_pos
{
	LEFT = 0,
	RIGHT = 1,
	NUM_OF_CHILDREN = 2
}child_pos_t;

struct bst_node
{
	bst_node_t *parent;
	bst_node_t *children[NUM_OF_CHILDREN];
	void *data;
};

struct binary_search_tree
{
	bst_node_t dummy_root;
	int (*cmp_func)(const void *, const void *);
};

static bst_iter_t BSTInValidIter(void);
static int BSTIsIterValid(bst_iter_t iter);
static bst_node_t *BSTIterToNode(bst_iter_t iter);
static bst_iter_t BSTNodeToIter(bst_node_t *node);
static bst_node_t *CreateNode(void *data);
static child_pos_t BSTGetChildPos(bst_node_t *node);
static int BSTIsLeaf(const bst_node_t *node);
static int BSTIsOneChild(const bst_node_t *node);
static bst_node_t *BSTGetSingleChild(const bst_node_t *node);
static void BSTReplaceNode(bst_node_t *node_to_remove);
static bst_node_t *BSTLeftChild(const bst_node_t *node);
static bst_node_t *BSTRightChild(const bst_node_t *node);
static bst_node_t *BSTNodeBySide(const bst_node_t *node, const child_pos_t side);
static size_t BSTHeightRec(bst_node_t *node);
static bst_iter_t BSTFindExtreme(bst_node_t *iter, const child_pos_t side);

/************************ Functions ************************/


bst_t *BSTCreate(int (*cmp_func)(const void *, const void *))
{
	bst_t *bst = (bst_t *)malloc(sizeof(bst_t));
	bst_node_t dummy_root = {0};

	assert(NULL != cmp_func);
	
	if (NULL == bst)
    {
        return NULL;
    }
    
    bst->cmp_func = cmp_func;
    bst->dummy_root = dummy_root;
    
    return bst;
}

void BSTDestroy(bst_t *bst)
{
    assert(NULL != bst);

    while (!BSTIsEmpty(bst))
    {
        BSTRemove(BSTBeginIter(bst));
    }

    free(bst);
}

bst_iter_t BSTInsert(bst_t *bst, void *data)
{
    bst_node_t *new_node = NULL;
    bst_node_t *curr_node = NULL;
    bst_node_t *parent_node = NULL;
    child_pos_t child_pos = LEFT;
    int cmp_res = 0;
    
    assert(NULL != bst);
    assert(NULL != data);
    
    new_node = CreateNode(data);
    if (NULL == new_node)
    {
        return BSTEndIter(bst);
    }
    
    curr_node = DUMMY_LEFT_CHILD(bst);
    parent_node = BSTIterToNode(BSTEndIter(bst));
    
    while (NULL != curr_node)
    {
        cmp_res = bst->cmp_func(data, curr_node->data);
    
        assert(0 != cmp_res);
        
        parent_node = curr_node;
        child_pos = 0 > cmp_res ? LEFT : RIGHT;
        curr_node = BSTNodeBySide(curr_node, child_pos);
    }
    
    new_node->parent = parent_node;
    parent_node->children[child_pos] = new_node;
    
    return BSTNodeToIter(new_node);
}

void BSTRemove(bst_iter_t iter)
{
	bst_node_t *node_to_remove = NULL;
	bst_node_t *child = NULL;
	bst_node_t *parent = NULL; 
	child_pos_t child_pos = LEFT;
	
    node_to_remove = BSTIterToNode(iter);
	child_pos = BSTGetChildPos(node_to_remove);
	parent = node_to_remove->parent;
	
    if (BSTIsLeaf(node_to_remove))
    {
    	parent->children[child_pos] = NULL;
    }
    else if (BSTIsOneChild(node_to_remove))
    {
        child = BSTGetSingleChild(node_to_remove);
        parent->children[child_pos] = child;
        child->parent = parent;
    }
    else
    {
    	BSTReplaceNode(node_to_remove);
    }

    free(node_to_remove);
}

int BSTIsEmpty(const bst_t *bst)
{
	assert(NULL != bst);
    return (NULL == bst->dummy_root.children[LEFT]);
}

bst_iter_t BSTEndIter(const bst_t *bst)
{
	assert(NULL != bst);

	return (bst_iter_t)(&(bst->dummy_root));
}

bst_iter_t BSTBeginIter(const bst_t *bst)
{
    bst_node_t *curr_node = NULL;

    assert(NULL != bst);

    curr_node = (bst_node_t *)&bst->dummy_root;
  
    while (NULL != BSTLeftChild(curr_node))
    {
        curr_node = BSTLeftChild(curr_node);
    }

    return BSTNodeToIter(curr_node);
}

int BSTIsSameIter(const bst_iter_t iter1, const bst_iter_t iter2)
{
	assert(BSTIsIterValid(iter1));
	assert(BSTIsIterValid(iter2));
	
    return iter1 == iter2;
}

void *BSTGetData(bst_iter_t iter)
{
	return BSTIterToNode(iter)->data;
}

bst_iter_t BSTNextIter(const bst_iter_t iter)
{
	return BSTFindExtreme(BSTIterToNode(iter), RIGHT);
}

bst_iter_t BSTPrevIter(const bst_iter_t iter)
{
	return BSTFindExtreme(BSTIterToNode(iter), LEFT);
}

size_t BSTHeight(const bst_t *bst)
{
    assert(NULL != bst);

    return BSTHeightRec(DUMMY_LEFT_CHILD(bst));
}

size_t BSTSize(const bst_t *bst)
{
	bst_iter_t curr_iter = BSTInValidIter();
	size_t count = 0;
	
	assert(NULL != bst);
	
	for (curr_iter = BSTBeginIter(bst); !BSTIsSameIter(curr_iter, BSTEndIter(bst)); curr_iter = BSTNextIter(curr_iter))
	{
		++count;
	}
	
	return count;
}

bst_iter_t BSTFind(const bst_t *bst, const void *key) 	
{
	 bst_iter_t curr_iter = BSTInValidIter();
	 int cmp_res = 1;
	 
	assert(NULL != bst);
	assert(NULL != key);
		
	for (curr_iter = BSTBeginIter(bst); !BSTIsSameIter(curr_iter, BSTEndIter(bst)) && 0 != cmp_res; curr_iter = BSTNextIter(curr_iter))
	{
		cmp_res = bst->cmp_func(key, BSTGetData(curr_iter));
	}
	
	return ((0 != cmp_res) ? BSTEndIter(bst) : BSTPrevIter(curr_iter));
}

int BSTForEach(bst_iter_t from, const bst_iter_t to, int (*action_func)(void *, void *), void *param)
{
	int flag = 0;
	
	assert(BSTIsIterValid(from));
	assert(BSTIsIterValid(to));
	assert(NULL != action_func);
	
	while (!BSTIsSameIter(from, to) && 0 == flag)
	{
		flag = action_func(BSTGetData(from), param);
		from = BSTNextIter(from);
	}
	return flag;
}

/************************ Static Functions ************************/
static int BSTIsIterValid(bst_iter_t iter)
{
	return BSTInValidIter() != iter;
}

static bst_iter_t BSTInValidIter(void)
{
	return NULL;
}

static bst_node_t *BSTIterToNode(bst_iter_t iter)
{
	assert(BSTIsIterValid(iter));
    return (bst_node_t *)iter;
}

static bst_iter_t BSTNodeToIter(bst_node_t *node)
{
    return (bst_iter_t)node;
}

static bst_node_t *CreateNode(void *data)
{
    bst_node_t *new_node = (bst_node_t *)malloc(sizeof(bst_node_t));
    
    if (NULL == new_node)
    {
        return NULL;
    }
    new_node->parent = NULL;
    new_node->children[LEFT] = NULL;
    new_node->children[RIGHT] = NULL;
    new_node->data = data;

    return new_node;
}

static child_pos_t BSTGetChildPos(bst_node_t *node)
{
	assert(NULL != node);  
    return node == node->parent->children[LEFT] ? LEFT : RIGHT;
}

static int BSTIsLeaf(const bst_node_t *node)
{
    assert(NULL != node);

    return ((NULL == BSTLeftChild(node)) && (NULL == BSTRightChild(node)));
}

static int BSTIsOneChild(const bst_node_t *node)
{
	assert(NULL != node); 
	return (NULL == BSTLeftChild(node) || NULL == BSTRightChild(node));
}

static bst_node_t *BSTGetSingleChild(const bst_node_t *node)
{
    assert(NULL != node);

    return (NULL == BSTLeftChild(node)) ? BSTRightChild(node) : BSTLeftChild(node);
}

static void BSTReplaceNode(bst_node_t *node_to_remove)
{
	bst_node_t *child = NULL;
	child_pos_t child_pos = LEFT;
	bst_node_t *parent = NULL; 
	bst_node_t *next = NULL;
	
	assert(NULL != node_to_remove);
	
	next = BSTIterToNode(BSTNextIter(BSTNodeToIter(node_to_remove)));
    node_to_remove->data = next->data;
    node_to_remove = next;
    parent = node_to_remove->parent;
    child = BSTRightChild(node_to_remove);
    child->parent = parent;
    child_pos = BSTGetChildPos(node_to_remove);
    parent->children[child_pos] = child;
}

static bst_node_t *BSTLeftChild(const bst_node_t *node)
{
    assert(NULL != node);

    return node->children[LEFT];
}

static bst_node_t *BSTRightChild(const bst_node_t *node)
{
    assert(NULL != node);

    return node->children[RIGHT];
}

static bst_node_t *BSTNodeBySide(const bst_node_t *node, const child_pos_t side)
{
    assert(NULL != node);

    return ((LEFT == side) ? BSTLeftChild(node) : BSTRightChild(node));
}

static size_t BSTHeightRec(bst_node_t *node)
{
	size_t left_height = 0;
	size_t right_height = 0;
	
    if (NULL == node)
    {
        return 0;
    }
    
    left_height = BSTHeightRec(BSTLeftChild(node)) + 1;
    right_height = BSTHeightRec(BSTRightChild(node)) + 1;
    
    return MAX2(left_height, right_height);
}

static bst_iter_t BSTFindExtreme(bst_node_t *node, const child_pos_t side)
{
	/*NEXT -side is RIGHT
	   PREV -side is LEFT*/
	bst_node_t *next_node = NULL;
	bst_node_t *parent_node = NULL;
    bst_node_t *child_node = NULL;
    child_pos_t child_pos = (child_pos_t)(RIGHT - side);
    
	assert(NULL != node);
	
	if (NULL != BSTNodeBySide(node, side))
    {
        next_node = BSTNodeBySide(node, side);
        while (NULL != BSTNodeBySide(next_node, child_pos))
        {
            next_node = BSTNodeBySide(next_node, child_pos);
        }
        return BSTNodeToIter(next_node);
    }
    else
    {
    	parent_node = node->parent;
    	child_node = node;
    	while (NULL != parent_node && BSTNodeBySide(parent_node, side) == child_node)
    	{
    		child_node = parent_node;
    		parent_node = parent_node->parent;
    	}
    	return BSTNodeToIter(parent_node);
    }
}

