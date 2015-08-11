/*
 *    Copyright 2015, Jeffrey Chan.
 */

#include <stdio.h>
#include <stdlib.h>
#include "binaryTree.h"
#include "commonDefs.h"
#include "memoryUtil.h"


/* ******************************************************************** */

static 
binTreeNode_t* searchDeleteNode(binTreeNode_t *pTree, int key, binTreeNode_t **pParent, int *pLeftChild);



/* ******************************************************************** */

binTreeNode_t* createTreeNode(int key, void *value)
{
	binTreeNode_t *pNode = NULL;
	
	pNode = (binTreeNode_t*) safeMalloc(sizeof(binTreeNode_t));
	
	pNode->key = key;
	pNode->value = value;
	pNode->left = NULL;
	pNode->right = NULL;
	
	return pNode;
} /* end of createNode() */


/* 
 * Destroy a tree.
 */
void destroyTree(binTreeNode_t *pTree)
{
	binTreeNode_t *pLeftChild = pTree->left, *pRightChild = pTree->right;
	
	if (pLeftChild != NULL) {
		destroyTree(pLeftChild);
	}
	
	if (pRightChild != NULL) {
		destroyTree(pRightChild);
	}
	
	destroyTreeNode(pTree);
	pTree = NULL;
} /* end of destroyTree() */


/* 
 * Destroy a node
 */
void destroyTreeNode(binTreeNode_t *pNode)
{
	freeValueMemory(pNode->value);
	/* Implement me!  Please determine the size of deallocated pNode->value */
	/* safeFree(pNode, sizeof(X)); */
} /* end of destroyNode() */


/*
 * Insert a value.
 * NOTE: For this assignment, we don't want duplicates.
 */
int insertTreeNode(binTreeNode_t *pTree, binTreeNode_t *pNewNode)
{
	/* TODO: Implement me! */
	/* Note you are free to change the interface or add another function to add tree nodes.  But you will need to update deleteKey(). */


	return SUCCESS;
} /* end of insertValue() */





/*
 * Delete the first node found with key.
 */
int deleteKey(binTreeNode_t **ppTree, int key)
{
	binTreeNode_t *pDelNode = NULL, *leftChild, *rightChild, *pParent;
	int bleftChild = 0;
	
	/* find node first */
	pDelNode = searchDeleteNode(*ppTree, key, &pParent, &bleftChild);
	
	if (pDelNode != NULL) {
		/* remove node then update subtrees */
		leftChild = pDelNode->left;
		rightChild = pDelNode->right;
		destroyTreeNode(pDelNode);
		
		/* update */
		if (pParent == NULL) {
			/* root node to be deleted */
			*ppTree = leftChild;
			insertTreeNode(*ppTree, rightChild);
		}
		else {
			/* deleted node is left child, so need to replace it */
			if (bleftChild) {
				if (leftChild != NULL) {
					pParent->left = leftChild;
					/* insert the right subtree into the new subtree rooted by leftchild */
					insertTreeNode(leftChild, rightChild);
				}
				else {
					pParent->left = rightChild;
				}
			}
			else {
				if (rightChild != NULL) {
					pParent->right = rightChild;
					/* insert the left subtree into the new subtree rooted by rightchild */
					insertTreeNode(rightChild, leftChild);
				}
				else {
					pParent->right = leftChild;
				}
			}
		}
		
		/* found */
		return SUCCESS;
	}
	
	/* key not found */
	return FAILED;
} /* end of deleteValue() */






/* ******************************************************************** */


binTreeNode_t* searchDeleteNode(binTreeNode_t *pTree, int key, binTreeNode_t **pParentNode, int *pLeftChild)
{
	binTreeNode_t *pCurrNode = pTree;
	
	while (pCurrNode != NULL) {
		if (key == pCurrNode->key) {
			return pCurrNode;
		}
		/* see if traverse down left subtree */
		if (key < pCurrNode->key) {
			*pParentNode = pCurrNode;
			*pLeftChild = 1;
			pCurrNode = pCurrNode->left;
		}
		/* try right */
		else {
			*pParentNode = pCurrNode;
			*pLeftChild = 0;
			pCurrNode = pCurrNode->right;
		}
	}
	
	/* not found */
	return NULL;
} /* end of searchDeleteNode() */



/* ******************************************************************** */



/* TODO: Please implement and move these functions to most appropriate file. */
void freeValueMemory(void *value)
{
	/* TODO: Implement me! */
}


