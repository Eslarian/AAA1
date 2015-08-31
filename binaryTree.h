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
void destroyTree(binTreeNode_t * root);


/* 
 * Destroy a node
 */
void destroyTreeNode(binTreeNode_t *pNode);


/*
 * Insert a value.
 * NOTE: Duplicates are allowed.
 */
int insertTreeNode(binTreeNode_t *pTree, binTreeNode_t *pNewNode);


/*
 * Delete the first node found with value.
 */
void deleteTreeNode(binTreeNode_t **ppTree, binTreeNode_t *pDelNode, binTreeNode_t *pDelParent, int bleftChild);


/*
 * Find node with key, and also return by reference that node's parent and whether it is a left or right child of the parent node.
 */
binTreeNode_t* searchDeleteNode(binTreeNode_t *pTree, int key, binTreeNode_t **pParent, int *pLeftChild);

/*Find node with key*/
binTreeNode_t * searchTree(binTreeNode_t * root,int key);
/*
 * Display the tree using preorder traversal.
 */
void printTree(binTreeNode_t *ppTree);






/* TODO: Please implement if using the above tree structure and code. */

#endif
