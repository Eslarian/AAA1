/*
 * bpGraphAdjList_BL.c
 *
 * Double Linked list implementation of an adjacency list representation.
 *
 *  Created on: 01/07/2015
 *      Author: Jeffrey Chan
 */


#include <stdio.h>
#include <stdlib.h>
#include "commonDefs.h"
#include "bipartiteGraph.h"
#include "list.h"
#include "memoryUtil.h"
#include "binaryTree.h"


#include <stddef.h>
#include "bipartiteGraph.h"
#define INVALID_COMP 3

struct implBipartGraph_t
{
	/* TODO: Implement me! */
	binTreeNode_t * vertsP1root;
	binTreeNode_t * vertsP2root;
};

struct edgeData
{
	int tarVertId;
	int srcVertId;
}; 


/* ************************************************************************* */
/* Function implementations */
void printEdges(binTreeNode_t * pTree)
{
	struct node * searchnode = NULL;
	struct list * castList = NULL;
	struct edgeData * castEdge = NULL;

	if (pTree != NULL) 
	{	
		castList = pTree->value;
		searchnode = castList->head;
		while(searchnode)
		{	
			castEdge = searchnode->data;
			printf("%d %d\n",castEdge->srcVertId,castEdge->tarVertId);
			searchnode = searchnode->next;
		} 
		printEdges(pTree->left);
		printEdges(pTree->right);
	}
}

int edgeComp(struct node * edgeNode,void * val)
{
	struct edgeData * eData;
	int * num;

	num = val;
	eData = edgeNode->data;
	if(eData->tarVertId > *num)
	{	
		return 1;
	} 
	if(eData->tarVertId < *num)
	{
		return -1;
	} 
	if(eData->tarVertId == *num) 
	{
		return 0;
	}
	
	return INVALID_COMP;

} 

bpGraph_t* bipartGraphCreate(int part1VertNum, int part2VertNum)
{
	/* TODO: Implement me! */
	int i;
	struct list * edgeList = NULL;
	binTreeNode_t * newNode = NULL;
	bpGraph_t * graph = safeMalloc(sizeof(bpGraph_t));

	graph->vertsP1root =  NULL;
	graph->vertsP2root =  NULL;


	for(i = 0; i < part1VertNum;i++)
	{
			edgeList = init_list();
			newNode = createTreeNode(i,edgeList);
			insertTreeNode(graph->vertsP1root,newNode);
	} 
			
	for(i = 0;i < part2VertNum;i++)
	{
		edgeList = init_list();
		newNode = createTreeNode(i,edgeList);
		insertTreeNode(graph->vertsP2root,newNode);
	} 

	return graph;
} /* end of bipartGraphCreate() */


void bipartGraphDestroy(bpGraph_t* pGraph)
{
	destroyTree(pGraph->vertsP1root);
	destroyTree(pGraph->vertsP2root);

} /* end of bipartGraphDestroy() */


int bipartGraphInsertVertex(bpGraph_t* pGraph, int vertId, int partite)
{
	/* TODO: Implement me! */
	binTreeNode_t * newNode = NULL;
	struct list * newList = NULL;

	if(partite == 1)
	{
		if(searchTree(pGraph->vertsP1root,vertId) != NULL)
		{
				return EXISTING_VERTEX;
		}
		else if(pGraph->vertsP1root == NULL)
		{	
			newList = init_list();
			newNode = createTreeNode(vertId,newList);
			pGraph->vertsP1root = newNode;
			return NEW_VERTEX;
		} 
		else
		{
			newList = init_list();
			newNode = createTreeNode(vertId,newList);
			insertTreeNode(pGraph->vertsP1root,newNode);
			return NEW_VERTEX;
		} 
	} 
	else if(partite == 2)
	{	
		if(searchTree(pGraph->vertsP2root,vertId) != NULL)
		{
			return EXISTING_VERTEX;
		} 
		else if (pGraph->vertsP2root == NULL)
		{
			newList = init_list();
			newNode = createTreeNode(vertId,newList);
			pGraph->vertsP2root = newNode;
			return NEW_VERTEX;
		} 
		else
		{
			newList = init_list();
			newNode = createTreeNode(vertId,newList);
			insertTreeNode(pGraph->vertsP2root,newNode);
			return NEW_VERTEX;
		} 
	} 

	return ERROR_VALUE;

} /* end of bipartGraphInsertVertex() */


int bipartGraphInsertEdge(bpGraph_t* pGraph, int srcVertId, int tarVertId, int srcPartite)
{
	binTreeNode_t * srcNode = NULL;
	struct list * castList = NULL;
	struct edgeData * newEdge = NULL;

	if(srcPartite == 1)
	{
		srcNode = searchTree(pGraph->vertsP1root,srcVertId);
		if(srcNode)
		{
			castList = srcNode->value;
			if(search(castList,&tarVertId,edgeComp) == 0)
				return EXISTING_EDGE;

			if(srcNode->key == srcVertId)
			{
				newEdge = safeMalloc(sizeof(struct edgeData));
				newEdge->tarVertId = tarVertId;
				newEdge->srcVertId =  srcVertId;
				add_node(castList,newEdge);
				return NEW_EDGE;
			} 

		}
	
	} 
	else if(srcPartite == 2)
	{
		srcNode = searchTree(pGraph->vertsP2root,srcVertId);
		if(srcNode)
		{
			castList = srcNode->value;
			if(search(castList,&tarVertId,edgeComp) == 0)
				return EXISTING_EDGE;

			if(srcNode->key == srcVertId)
			{
				newEdge = safeMalloc(sizeof(struct edgeData));
				newEdge->tarVertId = tarVertId;
				newEdge->srcVertId =  srcVertId;
				add_node(castList,newEdge);
				return NEW_EDGE;
			} 

		}
	} 

	return ERROR_VALUE;
	
} /* end of bipartGraphInsertEdge() */


int bipartGraphDeleteVertex(bpGraph_t* graph, int vertId, int partite)
{
	binTreeNode_t * delNode = NULL;
	binTreeNode_t * parentNode = NULL;
	int leftChild;

	if(partite == 1)
	{
		delNode = searchDeleteNode(graph->vertsP1root,vertId,&parentNode,&leftChild);
		if(!delNode)
			return NOT_FOUND;
		deleteTreeNode(&graph->vertsP1root,delNode,parentNode,leftChild);
		return SUCCESS;
	} 
	else if(partite == 2)
	{
		delNode = searchDeleteNode(graph->vertsP2root,vertId,&parentNode,&leftChild);
		if(!delNode)
			return NOT_FOUND;
		deleteTreeNode(&graph->vertsP2root,delNode,parentNode,leftChild);
		return SUCCESS;
	} 

	return ERROR_VALUE;
} /* end of bipartGraphDeleteVertex() */


int bipartGraphDeleteEdge(bpGraph_t* pGraph,  int srcVertId, int tarVertId, int srcPartite)
{
	binTreeNode_t * searchnode = NULL;
	struct node * searchedge = NULL;
	struct node * delnode = NULL;
	struct node * prevnode = NULL;
	struct list * castList = NULL;
	int i;

	if(srcPartite == 1)
	{
		searchnode = searchTree(pGraph->vertsP1root,srcVertId);
		if(!searchnode)
			return NOT_FOUND;
		castList = searchnode->value;
		delnode = find(castList,&tarVertId,edgeComp);
		if(delnode == NULL)
		{
			return NOT_FOUND;
		}
		else if(delnode == castList->head)
		{
			castList->head = delnode->next;
			prevnode = NULL;
			remove_node(prevnode,delnode,castList,free);
			return SUCCESS;
		} 
		
		searchedge = castList->head;
		for(i = 0; i < castList->count;i++)
		{
			prevnode = searchedge;
			searchedge = prevnode->next;
			if(searchedge == delnode)
			{
				remove_node(prevnode,searchedge,castList,free);
				return SUCCESS;

			} 
		}
	}
	else if(srcPartite == 2)
	{
		searchnode = searchTree(pGraph->vertsP2root,srcVertId);
		if(!searchnode)
			return NOT_FOUND;
		castList = searchnode->value;
		delnode = find(castList,&tarVertId,edgeComp);
		if(delnode == NULL)
		{
			return NOT_FOUND;
		}
		else if(delnode == castList->head)
		{
			castList->head = delnode->next;
			prevnode = NULL;
			remove_node(prevnode,delnode,castList,free);
			return SUCCESS;
		} 
		
		searchedge = castList->head;
		for(i = 0; i < castList->count;i++)
		{
			prevnode = searchedge;
			searchedge = prevnode->next;
			if(searchedge == delnode)
			{
				remove_node(prevnode,searchedge,castList,free);
				return SUCCESS;

			}
		}
	} 

	return ERROR_VALUE;
} /** end of bipartGraphDeleteEdge() */


int bipartGraphFindVertex(bpGraph_t *pGraph, int vertId, int partite)
{
	if(partite == 1)
	{
		if(searchTree(pGraph->vertsP1root,vertId) != NULL)
			return FOUND;

		return NOT_FOUND;
	}
	else if(partite == 2)
	{
		if(searchTree(pGraph->vertsP2root,vertId) != NULL)
			return FOUND;

		return NOT_FOUND;
	} 

	return ERROR_VALUE;
} /* end of bipartGraphFindVertex() */


int bipartGraphFindEdge(bpGraph_t* graph, int srcVertId, int tarVertId, int srcPartite)
{
	/** TODO: Implement me! */
	binTreeNode_t * vertex;


	if(srcPartite == 1)
	{
		vertex = searchTree(graph->vertsP1root,srcVertId);
		if(vertex == NULL)
			return NOT_FOUND;

		if(search(vertex->value,&tarVertId,edgeComp) == 0)
			return FOUND;

		return NOT_FOUND;
	} 
	else if(srcPartite == 2)
	{
		vertex = searchTree(graph->vertsP2root,srcVertId);
		if(vertex == NULL)
			return NOT_FOUND;

		if(search(vertex->value,&tarVertId,edgeComp) == 0)
			return FOUND;

		return NOT_FOUND;
	} 

	return ERROR_VALUE;
} /* end of bipartGraphFindEdge() */


void bipartGraphPrint(bpGraph_t *pGraph)
{
	/* TODO: Implement me! */
	printf("Vertices:\n");
	printf("Part 1\n"); 
	printTree(pGraph->vertsP1root);
	printf("\nPart 2\n");
	printTree(pGraph->vertsP2root);
	printf("\n");

	printf("Edges:\n");	
	printf("Part 1 to 2\n");
	printEdges(pGraph->vertsP1root);
	printf("Part 2 to 1\n");
	printEdges(pGraph->vertsP2root);

} /* end of bipartGraphPrint() */
