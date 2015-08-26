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
#define INVALID_COMP 3

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
	
	/*FIXME this needs refactoring so that it actually frees properly*/
	
	free_list(pGraph->vertsP1);
	free_list(pGraph->vertsP2);
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
			return NEW_VERTEX

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
			if(search(castData->edgeList,&tarVertId,numComp) == 0)
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
			if(search(castData->edgeList,&tarVertId,numComp) == 0)
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
		} 
	} 

	return ERROR_VALUE;
} /* end of bipartGraphInsertEdge() */


int bipartGraphDeleteVertex(bpGraph_t* graph, int vertId, int partite)
{
	/* TODO: Implement me! */
	if(partite == 1)
	{
		

	/* TODO: Replace placeholder. */
	return 0;
} /* end of bipartGraphDeleteVertex() */


int bipartGraphDeleteEdge(bpGraph_t* pGraph,  int srcVertId, int tarVertId, int srcPartite)
{
	/* TODO: Implement me! */

	/* TODO: Replace placeholder. */
	return 0;
} /** end of bipartGraphDeleteEdge() */


int bipartGraphFindVertex(bpGraph_t *pGraph, int vertId, int partite)
{
	/* TODO: Implement me! */

	/* TODO: Replace placeholder. */
	return 0;
} /* end of bipartGraphFindVertex() */


int bipartGraphFindEdge(bpGraph_t* graph, int srcVertId, int tarVertId, int srcPartite)
{
	/** TODO: Implement me! */

	/* TODO: Replace placeholder. */
	return 0;
} /* end of bipartGraphFindEdge() */


void bipartGraphPrint(bpGraph_t *pGraph)
{
	/* TODO: Implement me! */
	return;
} /* end of bipartGraphPrint() */

