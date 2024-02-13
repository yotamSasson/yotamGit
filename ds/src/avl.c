#include <stdlib.h> /* malloc */
#include <assert.h> /*assert*/
#include <stdio.h> /*printf*/

#include "avl.h"

#define DUMMY_LEFT_CHILD(avl) ((avl)->dummy_root.children[LEFT])
#define MAX2(a, b) (((a) > (b)) ? (a) : (b))

typedef struct avl_node avl_node_t;

typedef enum child_pos
{
	LEFT = 0,
	RIGHT = 1,
	NUM_OF_CHILDREN = 2
}child_pos_t;

struct avl_node
{
	avl_node_t *children[NUM_OF_CHILDREN];
	void *data;
	size_t height;
};

struct avl_tree
{
	avl_node_t dummy_root;
	int (*cmp_func)(const void *, const void *);
};

/************************ nodes Functions ************************/
static avl_node_t *CreateNode(void *data);
static void DestroyNode(avl_node_t *node);
static avl_node_t *AVLLeftChild(const avl_node_t *node);
static avl_node_t *AVLRightChild(const avl_node_t *node);
static avl_node_t *AVLNodeBySide(const avl_node_t *node, const child_pos_t side);
static avl_node_t *AVLGetSuccessor(avl_node_t *node);
static avl_node_t *AVLGetSingleChild(const avl_node_t *node);
static int AVLHasTwoChildren(const avl_node_t *node);

/************************ Helper Functions ************************/
/*static size_t AVLHeightRec(const avl_node_t *node);*/
static size_t AVLCountRec(const avl_node_t *node);
static void *AVLFindRec(avl_node_t *node, const void *key, int (*cmp_func)(const void *, const void *));
static void AVLInsertRec(avl_node_t **node_ptr, void *data, avl_node_t *new_node, int (*cmp_func)(const void *, const void *));
static void AVLRemoveRec(avl_node_t **root, const void *key, int (*cmp_func)(const void *, const void *));
static int AVLForEachInOrder(avl_node_t *root, int (*action_func)(void *, void *), void *param);
static int AVLForEachPostOrder(avl_node_t *root, int (*action_func)(void *, void *), void *param);
static int AVLForEachPreOrder(avl_node_t *root, int (*action_func)(void *, void *), void *param);
static void AVLUpdateHeight(avl_node_t *node);
static int AVLGetBalanceFactor(avl_node_t *node);
static void AVLRebalance(avl_node_t **node_ptr);
static void AVLRotateBySide(avl_node_t **node_ptr, child_pos_t side);

/************************ Print Functions ************************/
static void AVLPrintInOrderRec(avl_node_t *root, void (*print_func)(const void *));
void AVLPrintTree(avl_t *avl);
void AVLPrintInOrder(avl_t *avl, void (*print_func)(const void *));
void AVLPrintPostOrder(avl_t *avl, void (*print_func)(const void *));
void AVLPrintPreOrder(avl_t *avl, void (*print_func)(const void *));
static void AVLPrintPreOrderRec(avl_node_t *root, void (*print_func)(const void *));
static void PrintTreeRec(avl_node_t *node, int level);
static void AVLPrintPostOrderRec(avl_node_t *root, void (*print_func)(const void *));

/************************ Functions ************************/

avl_t *AVLCreate(int (*cmp_func)(const void *, const void *))
{
	avl_t *avl = (avl_t *)malloc(sizeof(avl_t));
	avl_node_t dummy_root = {0};

	assert(NULL != cmp_func);
	
	if (NULL == avl)
    {
        return NULL;
    }
    
    avl->cmp_func = cmp_func;
    avl->dummy_root = dummy_root;
    
    return avl;
}

void AVLDestroy(avl_t *avl)
{
	assert(NULL != avl);
	
	DestroyNode(DUMMY_LEFT_CHILD(avl));
    free(avl);
}

int AVLInsert(avl_t *avl, void *data)
{
	avl_node_t *new_node = NULL;
	
	assert(NULL != avl);
	assert(NULL != data);
	
	new_node = CreateNode(data);
	if (NULL == new_node)
    {
        return 1;
    }
    
	AVLInsertRec(&DUMMY_LEFT_CHILD(avl), data, new_node, avl->cmp_func);
	return  0;
}

void AVLRemove(avl_t *avl, const void *key)
{
	assert(NULL != avl);
	assert(NULL != key);
	
	if(!AVLIsEmpty(avl))
	{
		AVLRemoveRec(&DUMMY_LEFT_CHILD(avl), key, avl->cmp_func);
	}
}

int AVLIsEmpty(const avl_t *avl)
{
	assert(NULL != avl);
    return (NULL == DUMMY_LEFT_CHILD(avl));
}

size_t AVLHeight(const avl_t *avl)
{
	assert(NULL != avl);
	if (NULL == DUMMY_LEFT_CHILD(avl))
	{
		return 0;
	}
	
    return DUMMY_LEFT_CHILD(avl)->height;
}

size_t AVLCount(const avl_t *avl)
{
	assert(NULL != avl);

    return AVLCountRec(DUMMY_LEFT_CHILD(avl));
}

void *AVLFind(const avl_t *avl, const void *key)
{
	assert(NULL != avl);
	assert(NULL != key);

    return AVLFindRec(DUMMY_LEFT_CHILD(avl), key, avl->cmp_func);
}

int AVLForEach(avl_t *avl, int (*action_func)(void *, void *), void *param, order_t order)
{
	int status = 0;
	
	assert(NULL != avl);
	assert(NULL != param);
	
	switch (order)
	{
		case IN_ORDER:
				status = AVLForEachInOrder(DUMMY_LEFT_CHILD(avl), action_func, param);
				break;
		case POST_ORDER:
				status = AVLForEachPostOrder(DUMMY_LEFT_CHILD(avl), action_func, param);
				break;
		case PRE_ORDER:
				AVLForEachPreOrder(DUMMY_LEFT_CHILD(avl), action_func, param);
				break;
	}
	return status;
}

/*============================== Recursive functions ==============================*/
static void DestroyNode(avl_node_t *node)
{
    if (NULL != node)
    {
    	DestroyNode(AVLLeftChild(node));
   		DestroyNode(AVLRightChild(node));
    }
    free(node);
}

static void AVLInsertRec(avl_node_t **node_ptr, void *data, avl_node_t *new_node, int (*cmp_func)(const void *, const void *))
{
    int cmp_res = 0;
    child_pos_t child_pos = LEFT;

    if (NULL == *node_ptr)
    {
        *node_ptr = new_node;
    } 
    else 
    {
        cmp_res = cmp_func(data, (*node_ptr)->data);
        child_pos = 0 > cmp_res ? LEFT : RIGHT;
        AVLInsertRec(&(*node_ptr)->children[child_pos], data, new_node, cmp_func);
    }
   AVLUpdateHeight(*node_ptr); 
   AVLRebalance(node_ptr);
}

static void AVLRemoveRec(avl_node_t **root, const void *key, int (*cmp_func)(const void *, const void *))
{
    avl_node_t *remove_node = NULL;
    avl_node_t *successor = NULL;
    child_pos_t child_pos = LEFT;
	int cmp_res =  0;
	
    if (NULL == *root)
    {
        return;
    }
    
	cmp_res = cmp_func(key, (*root)->data);
    if (0 != cmp_res)
    {
		child_pos = 0 > cmp_res ? LEFT : RIGHT;
		AVLRemoveRec(&(*root)->children[child_pos], key, cmp_func);
    } 
    else
    { 
    	remove_node = *root;
    	if (AVLHasTwoChildren(remove_node))
    	{
    		successor = AVLGetSuccessor(remove_node);
    		remove_node->data = successor->data;
    		AVLRemoveRec(&remove_node->children[RIGHT], successor->data, cmp_func);
    	}
    	else
    	{
    		*root = AVLGetSingleChild(remove_node);
    		free(remove_node);
    	} 
    }
    
    AVLUpdateHeight(*root); 
    AVLRebalance(root);    
}    
/*static size_t AVLHeightRec(const avl_node_t *node)
{
	size_t left_height = 0;
	size_t right_height = 0;
	
    if (NULL == node)
    {
        return 0;
    }
    
    left_height = AVLHeightRec(AVLLeftChild(node)) + 1;
    right_height = AVLHeightRec(AVLRightChild(node)) + 1;
    
    return MAX2(left_height, right_height);
}*/

static size_t AVLCountRec(const avl_node_t *node)
{
	if (NULL == node)
    {
        return 0;
    }
    else
    {
    	return 1 + AVLCountRec(AVLLeftChild(node)) + AVLCountRec(AVLRightChild(node));
    }
}

static void *AVLFindRec(avl_node_t *node, const void *key, int (*cmp_func)(const void *, const void *))
{
	int cmp_res = 0;
	child_pos_t child_pos = 0;
	
	if (NULL == node)
    {
        return NULL;
    }
    
    cmp_res = cmp_func(key, node->data);
    
    if (0 == cmp_res)
    {
    	return node->data;
    }
    
    child_pos = 0 > cmp_res ? LEFT : RIGHT;
    
    return AVLFindRec(AVLNodeBySide(node, child_pos), key, cmp_func);
}

static int AVLForEachInOrder(avl_node_t *root, int (*action_func)(void *, void *), void *param)
{
    if (NULL != root)
    {
   		if (AVLForEachInOrder(AVLLeftChild(root), action_func, param) != 0) 
		{
			return -1;
		}
		if (action_func(root->data, param) != 0) 
		{
			return -1;
		}
		if (AVLForEachInOrder(AVLRightChild(root), action_func, param) != 0) 
		{
			return -1;
		}
	}
	return 0;
}

static int AVLForEachPostOrder(avl_node_t *root, int (*action_func)(void *, void *), void *param)
{
     if (NULL != root)
     {
   		if (AVLForEachPostOrder(AVLLeftChild(root), action_func, param) != 0) 
		{
			return -1;
		}
		if (AVLForEachPostOrder(AVLRightChild(root), action_func, param) != 0) 
		{
			return -1;
		}
		if (action_func(root->data, param) != 0) 
		{
			return -1;
		}
	}
	return 0;
}

static int AVLForEachPreOrder(avl_node_t *root, int (*action_func)(void *, void *), void *param)
{
    if (NULL != root)
     {
		if (action_func(root->data, param) != 0) 
		{
			return -1;
		}
   		if (AVLForEachPreOrder(AVLLeftChild(root), action_func, param) != 0) 
		{
			return -1;
		}
		if (AVLForEachPreOrder(AVLRightChild(root), action_func, param) != 0) 
		{
			return -1;
		}
	}
	return 0;
}

/*============================== Helper functions ==============================*/

static avl_node_t *CreateNode(void *data)
{
    avl_node_t *new_node = (avl_node_t *)malloc(sizeof(avl_node_t));
    
    if (NULL == new_node)
    {
        return NULL;
    }
    new_node->height = 1;
    new_node->children[LEFT] = NULL;
    new_node->children[RIGHT] = NULL;
    new_node->data = data;

    return new_node;
}

static void AVLUpdateHeight(avl_node_t *node)
{
	int left_height = 0;
	int right_height = 0;

	if (NULL != node)
	{
		left_height = (AVLLeftChild(node) ? AVLLeftChild(node)->height : 0);
		right_height = (AVLRightChild(node) ? AVLRightChild(node)->height : 0);
		node->height = 1 + MAX2(left_height, right_height);
	}
}

static int AVLGetBalanceFactor(avl_node_t *node)
{
    int left_height = (AVLLeftChild(node) ? AVLLeftChild(node)->height : 0);
    int right_height = (AVLRightChild(node) ? AVLRightChild(node)->height : 0);

    return left_height - right_height;
}

static void AVLRebalance(avl_node_t **node_ptr)
{
    int balance_factor = 0;
	if (NULL != *node_ptr)
	{
		balance_factor = AVLGetBalanceFactor(*node_ptr);
	
  		if (balance_factor > 1)
    	{
        	if (AVLGetBalanceFactor(AVLLeftChild(*node_ptr)) < 0)
        	{
            	AVLRotateBySide(&(*node_ptr)->children[LEFT], RIGHT); /*if tree is left-heavy and subtree is right-heavy rotate first to the left*/
        	}
        	AVLRotateBySide(node_ptr, LEFT); /*rotate to the right*/
    	}
    	else if (balance_factor < -1)
    	{
        	if (AVLGetBalanceFactor(AVLRightChild(*node_ptr)) > 0)
        	{
            	AVLRotateBySide(&(*node_ptr)->children[RIGHT], LEFT); /*if tree is right-heavy and subtree is left-heavy rotate first to the right*/
        	}
         	AVLRotateBySide(node_ptr, RIGHT); /*rotate to the left*/
    	}
    
    }
}

static void AVLRotateBySide(avl_node_t **node_ptr, child_pos_t side)
{
	child_pos_t child_pos = RIGHT - side;
    avl_node_t *new_root =  AVLNodeBySide(*node_ptr, side);
    avl_node_t *child_of_new_root = AVLNodeBySide(new_root, child_pos);

    (*node_ptr)->children[side] = child_of_new_root;
    new_root->children[child_pos] = *node_ptr;

    AVLUpdateHeight(*node_ptr);
    AVLUpdateHeight(new_root);

    *node_ptr = new_root;
}

static avl_node_t *AVLGetSuccessor(avl_node_t *node)
{
	avl_node_t *current = NULL;
	
	assert(NULL != node);
	
	current = AVLRightChild(node);
    while (NULL != current->children[LEFT])
    {
    	current = AVLLeftChild(current);
    }
    return current;
}

static avl_node_t *AVLLeftChild(const avl_node_t *node)
{
    assert(NULL != node);

    return node->children[LEFT];
}

static avl_node_t *AVLRightChild(const avl_node_t *node)
{
    assert(NULL != node);

    return node->children[RIGHT];
}

static avl_node_t *AVLNodeBySide(const avl_node_t *node, const child_pos_t side)
{
    assert(NULL != node);

    return ((LEFT == side) ? AVLLeftChild(node) : AVLRightChild(node));
}

static avl_node_t *AVLGetSingleChild(const avl_node_t *node)
{
    assert(NULL != node);

    return (NULL == AVLLeftChild(node)) ? AVLRightChild(node) : AVLLeftChild(node);
}

static int AVLHasTwoChildren(const avl_node_t *node)
{
	assert(NULL != node); 
	return (NULL != AVLLeftChild(node) &&  NULL != AVLRightChild(node));
}

/*============================== Print functions ==============================*/

void AVLPrintInOrder(avl_t *avl, void (*print_func)(const void *))
{
	assert(NULL != avl);
	assert(NULL != print_func);
	
	AVLPrintInOrderRec(DUMMY_LEFT_CHILD(avl), print_func);
}

static void AVLPrintInOrderRec(avl_node_t *root, void (*print_func)(const void *))
{
	if (NULL != root)
    {
		AVLPrintInOrderRec(AVLLeftChild(root), print_func);
    	print_func(root->data);
    	AVLPrintInOrderRec(AVLRightChild(root), print_func);
    }
}

void AVLPrintPostOrder(avl_t *avl, void (*print_func)(const void *))
{
	assert(NULL != avl);
	assert(NULL != print_func);
	
	AVLPrintPostOrderRec(DUMMY_LEFT_CHILD(avl), print_func);
}

static void AVLPrintPostOrderRec(avl_node_t *root, void (*print_func)(const void *))
{
	if (NULL != root)
    {
		AVLPrintInOrderRec(AVLLeftChild(root), print_func);
    	AVLPrintInOrderRec(AVLRightChild(root), print_func);
    	print_func(root->data);
    }
}

void AVLPrintPreOrder(avl_t *avl, void (*print_func)(const void *))
{
	assert(NULL != avl);
	assert(NULL != print_func);
	
	AVLPrintPreOrderRec(DUMMY_LEFT_CHILD(avl), print_func);
}

static void AVLPrintPreOrderRec(avl_node_t *root, void (*print_func)(const void *))
{
	if (NULL != root)
    {
		print_func(root->data);
    	AVLPrintInOrderRec(AVLLeftChild(root), print_func);
   		AVLPrintInOrderRec(AVLRightChild(root), print_func);
   	}
}

void AVLPrintTree(avl_t *avl)
{
	assert(NULL != avl);
	PrintTreeRec(DUMMY_LEFT_CHILD(avl), 0);
}

static void PrintTreeRec(avl_node_t *node, int level)
{
    int i = 0;
    if (NULL == node) return;

    PrintTreeRec(node->children[RIGHT], level + 1);
    for (i = 0 ; i < level ; ++i)
    {
        printf("        ");
    }
    printf("%d, %ld\n", *(int*)node->data, node->height);
    PrintTreeRec(node->children[LEFT], level + 1);
}



