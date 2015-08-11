/*
 *    Copyright 2015, Jeffrey Chan.
 */

#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_



#include <stdlib.h>
#include <string.h>


struct binTreeNode;
typedef struct binTreeNode binTreeNode_t;

/*
 * Binary tree node data type.
 */
struct binTreeNode {
	int key;
	/* pointer to the value that the node holds */
	void *value;
	/* Left and right children subtrees */
	binTreeNode_t *left, *right;
};





/* 
 * Create a tree.
 */
binTreeNode_t* createTreeNode(int key, void *value);


/* 
 * Destroy a tree.
 */
void destroyTree(binTreeNode_t *tree);


/* 
 * Destroy a node
 */
void destroyTreeNode(binTreeNode_t *node);


/*
 * Insert a value.
 * NOTE: Duplicates are allowed.
 */
int insertTreeNode(binTreeNode_t *pTree, binTreeNode_t *pNewNode);


/*
 * Delete the first node found with value.
 */
int deleteKey(binTreeNode_t **ppTree, int key);







/* TODO: Please implement. */
void* allocateValueMemory();

/* TODO: Please implement. */
void freeValueMemory(void *value);




#endif


