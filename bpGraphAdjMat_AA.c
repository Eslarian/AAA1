/*
 * bipartGraphAdjMat.c
 *
 *  Created on: 01/07/2015
 *      Author: jkct440
 */


#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commonDefs.h"
#include "bipartiteGraph.h"
#include "memoryUtil.h"


struct implBipartGraph_t
{
	/* TODO: Implement me! */
	int p1Verts, p2Verts;
	char *vVertExistP1;
	char *vVertExistP2;
	char ** matrix;
};



/* ************************************************************************* */
/* Function implementations */


bpGraph_t* bipartGraphCreate(int part1VertNum, int part2VertNum)
{
	int i;
	bpGraph_t * pGraph  = safeMalloc(sizeof(bpGraph_t));
	
	
	pGraph->p1Verts = part1VertNum;
	pGraph->p2Verts = part2VertNum;

	/*Creating vertex existence array for Partite 1*/
	pGraph->vVertExistP1 = (char *) safeMalloc(part1VertNum * sizeof(char));
	for (i = 0; i < pGraph->p1Verts; ++i) 
	{
		pGraph->vVertExistP1[i] = 1;
	}

	/*Creating vertex existence array for Partite 2*/
	pGraph->vVertExistP2 = (char *) safeMalloc(part2VertNum * sizeof(char));
	for (i = 0; i < pGraph->p2Verts; ++i) 
	{
		pGraph->vVertExistP2[i] = 1;
	}

	/*Allocating space for the 2D array of edges for Partite 1*/
	pGraph->matrix = safeMalloc(part1VertNum * sizeof(char*));
	for(i = 0; i < part1VertNum; i++)
	{
		pGraph->matrix[i] = safeMalloc(part2VertNum * sizeof(char));
	} 
	 
	
	return pGraph;
} /* end of bipartGraphDestroy() */

void resizeMatrix(bpGraph_t * pGraph,int newSize,int partite)
{
	if(partite == 1) 
	{
		pGraph->matrix = safeMalloc(part1VertNum * sizeof(char*));
		for(i = 0; i < part1VertNum; i++)
		{
			pGraph->matrix[i] = safeMalloc(part2VertNum * sizeof(char));
		} 
	} 



void bipartGraphDestroy(bpGraph_t* pGraph)
{
	safeFree(pGraph->p1matrix,sizeof(char **)*pGraph->p1Verts);
	safeFree(pGraph->p2matrix,sizeof(char **)*pGraph->p2Verts);
	safeFree(pGraph->vVertExistP1,sizeof(char) * pGraph->p1Verts);
	safeFree(pGraph->vVertExistP2,sizeof(char) * pGraph->p2Verts);
	safeFree(pGraph,sizeof(bpGraph_t));

} /* end of bipartGraphDestroy() */


int bipartGraphInsertVertex(bpGraph_t* pGraph, int vertId, int partite)
{
	
	if(partite == 1)
	{
		if(vertId > pGraph->p1Verts)
		{
			pGraph->vVertExistP1 = safeRealloc(pGraph->vVertExistP1,sizeof(char) * vertId+1,sizeof(char) * (vertId - pGraph->p1Verts+1));
			pGraph->vVertExistP1[vertId] = 1;
			pGraph->p1Verts = vertId;
			pGraph->p1matrix = safeRealloc(pGraph->p1

			return SUCCESS;
		} 


		if(pGraph->vVertExistP1[vertId] == 1) 
		{
			return EXISTING_EDGE;
		} 
		
		pGraph->vVertExistP1[vertId] = 1;
		return SUCCESS;
	} 
	if(partite == 2)
	{
		if(vertId > pGraph->p2Verts)
		{
			
			pGraph->vVertExistP2 = safeRealloc(pGraph->vVertExistP2,sizeof(char) * vertId+1,sizeof(char) * (vertId - pGraph->p2Verts+1));
			pGraph->vVertExistP2[vertId] = 1;
			pGraph->p2Verts = vertId;
			return SUCCESS;
		} 


		if(pGraph->vVertExistP2[vertId] == 1) 
		{
			return EXISTING_EDGE;
		} 
		
		pGraph->vVertExistP2[vertId] = 1;
		return SUCCESS;
	} 


	return ERROR_VALUE;
} 
		
/* end of bipartGraphInsertVertex() */


int bipartGraphInsertEdge(bpGraph_t* pGraph, int srcVertId, int tarVertId, int srcPartite)
{
	/* TODO: Implement me! */
	
	
	/* TODO: Replace placeholder. */
	return 0;
} /* end of bipartGraphInsertEdge() */


int bipartGraphDeleteVertex(bpGraph_t* graph, int vertId, int partite)
{
	/* TODO: Implement me! */

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
} /* end of bipartGraphPrint() */

