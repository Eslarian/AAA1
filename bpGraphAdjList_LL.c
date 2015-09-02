/*
 * bpGraphAdjMat_AA.c
 *
 *  Created on: 01/07/2015
 *      Author: Jeffrey Chan
 */

#include <stddef.h>
#include "bipartiteGraph.h"
#include "memoryUtil.h"
#include "list.h"
#include "commonDefs.h"
#include <stdlib.h>
#include <stdio.h>
#define INVALID_COMP 3

/*Data structures*/
struct implBipartGraph_t
{
	int vertNumP1;
	int vertNumP2;

	struct list * vertsP1;
	struct list * vertsP2;	
	
};

struct vertData
{
	int vertId;
	struct list * edgeList;
}; 

struct edgeData
{
	int tarVertId;
	int srcVertId;
}; 

/*Function implementations for generics use*/

/*Comparison function used for searching and finding*/
int numComp(struct node * vertNode, void * val)
{
	struct vertData * vData;
	int * num;
	
	num = val;
	vData  = vertNode->data;
	if(vData->vertId > *num)
	{	
		return 1;
	} 
	if(vData->vertId < *num)
	{
		return -1;
	} 
	if(vData->vertId == *num) 
	{
		return 0;
	}
	
	return INVALID_COMP;

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
	
	
/*Free function for freeing the data in the vertices list*/
void free_vertData(void * data)
{
	struct vertData * castData = data;

	free_list(castData->edgeList,free);
	free(castData);
} 
/* ************************************************************************* */
/* Function implementations */


bpGraph_t* bipartGraphCreate(int part1VertNum, int part2VertNum)
{
	int i;

	/*Allocating space for the bipartGraph, assigning values and initializing vertices lists*/
	bpGraph_t * pGraph = safeMalloc(sizeof(bpGraph_t));
	pGraph->vertNumP1 = part1VertNum;
	pGraph->vertNumP2 = part2VertNum;
	pGraph->vertsP1 = init_list();
	pGraph->vertsP2 = init_list();

	/*Creating vertices nodes up until the VertNum values*/
	for(i = 0; i < part1VertNum;i++)
	{
		bipartGraphInsertVertex(pGraph, i, 1);
	} 
	
	for(i = 0; i < part2VertNum;i++)
	{
		bipartGraphInsertVertex(pGraph, i, 2);
	} 


	
	return pGraph;
} /* end of bipartGraphCreate() */


void bipartGraphDestroy(bpGraph_t* pGraph)
{
	
	free_list(pGraph->vertsP1, free_vertData);
	free_list(pGraph->vertsP2, free_vertData);
	safeFree(pGraph, sizeof(bpGraph_t));
	

} /* end of bipartGraphDestroy() */


int bipartGraphInsertVertex(bpGraph_t* pGraph, int vertId, int partite)
{
	struct vertData * newData = NULL;

	if(partite == 1) 
	{	
		/*Checking if the vertex exists already*/
		if(search(pGraph->vertsP1,&vertId,numComp) == 0) 
		{	
			return EXISTING_VERTEX;
		} 
		else 
		{	
			/*Creating data struct and adding vertex node*/
			newData = safeMalloc(sizeof(struct vertData)); 
			newData->vertId = vertId;
			newData->edgeList = init_list(); 
			add_node(pGraph->vertsP1,newData);
			return NEW_VERTEX;

		} 
	} 
	else if(partite == 2) 
	{
		/*Checking if the vertex exists already*/
		if(search(pGraph->vertsP2,&vertId,numComp) == 0) 
		{ 
			return EXISTING_VERTEX;
		} 
		else
		{
			/*Creating data struct and adding vertex node*/
			newData = safeMalloc(sizeof(struct vertData)); 
			newData->vertId = vertId;
			newData->edgeList = init_list(); 
			add_node(pGraph->vertsP2,newData);
			return NEW_VERTEX;
		} 
	} 
		
 	return ERROR_VALUE;
	
} /* end of bipartGraphInsertVertex() */


int bipartGraphInsertEdge(bpGraph_t* pGraph, int srcVertId, int tarVertId, int srcPartite)
{

	struct node * searchnode = NULL;
	struct vertData * castData = NULL;
	struct edgeData * newData = NULL;

	if(srcPartite == 1)
	{
		searchnode = pGraph->vertsP1->head;
		/*Searching through the vertex list to find where to insert the edge node, or if the edge exists already*/
		while(searchnode)
		{
			castData = searchnode->data;
			/*Checking if the edge exists already*/
			if(search(castData->edgeList,&tarVertId,edgeComp) == 0)
			return EXISTING_EDGE; 		
			
			if(castData->vertId == srcVertId) 
			{
				/*Inserting new edge node*/
				newData = safeMalloc(sizeof(struct edgeData));
				newData->tarVertId = tarVertId;
				newData->srcVertId = srcVertId; 
				add_node(castData->edgeList,newData);
				return NEW_EDGE;
			} 
			searchnode = searchnode->next;
		}
	} 
	else if(srcPartite == 2) 
	{
		searchnode = pGraph->vertsP2->head;
		/*Searching through the vertex list to find where to insert the edge node, or if the edge exists already*/
		while(searchnode)
		{
			castData = searchnode->data;
			/*Checking if the edge exists already*/
			if(search(castData->edgeList,&tarVertId,edgeComp) == 0)
			return EXISTING_EDGE;

			if(castData->vertId == srcVertId)
			{
				/*Inserting new edge node*/
				newData = safeMalloc(sizeof(struct edgeData));
				newData->tarVertId = tarVertId;
				newData->srcVertId = srcVertId; 
				add_node(castData->edgeList,newData);
				return NEW_EDGE;
			} 
			searchnode = searchnode->next;
		} 
	} 

	return ERROR_VALUE;
} /* end of bipartGraphInsertEdge() */


int bipartGraphDeleteVertex(bpGraph_t* graph, int vertId, int partite)
{
	struct node * delNode = NULL;
	struct node * prevNode = NULL;
	struct node * searchnode = NULL;
	int i;

	if(partite == 1)
	{	
		delNode = find(graph->vertsP1,&vertId,numComp);
		
		if(delNode == NULL)
			return NOT_FOUND;
		
		if(delNode == graph->vertsP1->head)
		{
			graph->vertsP1->head = delNode->next;
			prevNode = NULL;
			remove_node(prevNode,delNode,graph->vertsP1,free_vertData);
			return SUCCESS;
		} 
			
		searchnode = graph->vertsP1->head;
		for(i = 0; i < graph->vertsP1->count;i++)
		{
			prevNode = searchnode;
			searchnode = prevNode->next;
			if(searchnode == delNode)
			{
				remove_node(prevNode,searchnode,graph->vertsP1,free_vertData);
				return SUCCESS;
			} 
		}
			
				
	}
	else if(partite == 2)
	{
		delNode = find(graph->vertsP2,&vertId,numComp);
		
		if(delNode == NULL)
			return NOT_FOUND;

		if(delNode == graph->vertsP2->head)
		{
			graph->vertsP1->head = delNode->next;
			prevNode = NULL;
			remove_node(prevNode,delNode,graph->vertsP1,free_vertData);
			return SUCCESS;
		} 
			
		searchnode = graph->vertsP2->head;
		for(i = 0; i < graph->vertsP2->count;i++)
		{
			prevNode = searchnode;
			searchnode = prevNode->next;
			if(searchnode == delNode)
			{
				remove_node(prevNode,searchnode,graph->vertsP2,free_vertData);
				return SUCCESS;

			} 
		}

	} 

	
	return ERROR_VALUE;
} /* end of bipartGraphDeleteVertex() */


int bipartGraphDeleteEdge(bpGraph_t* pGraph,  int srcVertId, int tarVertId, int srcPartite)
{
	struct node * searchnode = NULL;
	struct node * searchedge = NULL;
	struct node * delNode = NULL;
	struct node * prevNode = NULL;
	struct vertData * castData;
	int i;

	if(srcPartite == 1)
	{	
		searchnode = pGraph->vertsP1->head;
		while(searchnode)
		{
			castData = searchnode->data;
			if((delNode = find(castData->edgeList,&tarVertId,edgeComp)) != NULL)
				break;
			searchnode = searchnode->next;
		} 			
		
		if(delNode == NULL)
		{
			return NOT_FOUND;
		}
		else if(delNode == castData->edgeList->head)
		{
			castData->edgeList->head = delNode->next;
			prevNode = NULL;
			remove_node(prevNode,delNode,castData->edgeList,free);
			return SUCCESS;
		} 
		
		searchedge = castData->edgeList->head;
		for(i = 0; i < castData->edgeList->count;i++)
		{
			prevNode = searchedge;
			searchedge = prevNode->next;
			if(searchedge == delNode)
			{
				remove_node(prevNode,searchedge,castData->edgeList,free);
				return SUCCESS;

			} 
		}

	} 
	else if(srcPartite == 2)
	{
		searchnode = pGraph->vertsP2->head;
		while(searchnode)
		{
			castData = searchnode->data;
			if((delNode = find(castData->edgeList,&tarVertId,edgeComp)) != NULL)
				break;
			searchnode = searchnode->next;
		} 			
		
		if(delNode == NULL)
		{
			return NOT_FOUND;
		}
		else if(delNode == castData->edgeList->head)
		{
			castData->edgeList->head = delNode->next;
			prevNode = NULL;
			remove_node(prevNode,delNode,castData->edgeList,free);
			return SUCCESS;
		} 
		
		searchedge = castData->edgeList->head;
		for(i = 0; i < castData->edgeList->count;i++)
		{
			prevNode = searchedge;
			searchedge = prevNode->next;
			if(searchedge == delNode)
			{
				remove_node(prevNode,searchedge,castData->edgeList,free);
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
		if(search(pGraph->vertsP1,&vertId,numComp) == -1)
			return FOUND;
		
		return NOT_FOUND;
	}
	else if(partite == 2)
	{
		if(search(pGraph->vertsP2,&vertId,numComp) == 0)
			return FOUND;
	
		return NOT_FOUND;
	} 
	
	return NOT_FOUND;

} /* end of bipartGraphFindVertex() */


int bipartGraphFindEdge(bpGraph_t* graph, int srcVertId, int tarVertId, int srcPartite)
{
	
	struct node * searchnode = NULL;
	struct vertData * castData = NULL;

	if(srcPartite == 1)
	{
		while(searchnode)
		{
			castData = searchnode->data;
			
			if(search(castData->edgeList,&tarVertId,edgeComp) == 0)
			return FOUND;
		}

		return NOT_FOUND;
	} 
	else if(srcPartite == 2)
	{
		while(searchnode)
		{
			castData = searchnode->data;

			if(search(castData->edgeList,&tarVertId,edgeComp) == 0)
			return FOUND;
		}
		
		return NOT_FOUND;
	} 

	return NOT_FOUND;

} /* end of bipartGraphFindEdge() */


void bipartGraphPrint(bpGraph_t *pGraph)
{
	struct node * searchnode = NULL;
	struct node * searchedge = NULL;
	struct vertData * castData = NULL;
	struct edgeData * castEdge = NULL;
	
	printf("Vertices:\n");
	printf("Part 1\n"); 	
	
	searchnode = pGraph->vertsP1->head;
	while(searchnode)
	{
		castData = searchnode->data;
		printf("%d ",castData->vertId);	
		searchnode = searchnode->next;
	} 	
	printf("\n");

	printf("Part 2\n");
	searchnode = pGraph->vertsP2->head;
	while(searchnode)
	{
		castData = searchnode->data;
		printf("%d ",castData->vertId);	
		searchnode = searchnode->next;
	} 
	printf("\n");
	
	printf("Edges:\n");
	printf("Part 1 to 2\n");
	
	searchnode = pGraph->vertsP1->head;
	while(searchnode)
	{	
		castData = searchnode->data;
		searchedge = castData->edgeList->head;
		while(searchedge)
		{
			castEdge = searchedge->data;
			printf("%d %d\n",castEdge->srcVertId,castEdge->tarVertId);
			searchedge = searchedge->next;
		} 
		searchnode = searchnode->next;
	} 

	printf("Part 2 to 1\n");
	searchnode = pGraph->vertsP2->head;
	while(searchnode)
	{	
		castData = searchnode->data;
		searchedge = castData->edgeList->head;
		while(searchedge)
		{
			castEdge = searchedge->data;
			printf("%d %d\n",castEdge->srcVertId,castEdge->tarVertId);
			searchedge = searchedge->next;
		} 
		searchnode = searchnode->next;
	} 
	
} /* end of bipartGraphPrint() */

