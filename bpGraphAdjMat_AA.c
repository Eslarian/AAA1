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
	char ** p1matrix;
	char ** p2matrix;
};



/* ************************************************************************* */
/* Function implementations */


bpGraph_t* bipartGraphCreate(int part1VertNum, int part2VertNum)
{
	/* TODO: Implement me! */
	int i;
	bpGraph_t * graph  = safeMalloc(sizeof(bpGraph_t));
	
	if(part1VertNum == 0)
		graph->p1Verts = part1VertNum-1;
	else
		graph->p1Verts = part1VertNum;
	if(part2VertNum == 0)
		graph->p2Verts = part2VertNum-1;
	else
		graph->p2Verts = part2VertNum;

	if(part1VertNum != 0)
	{
		graph->p1matrix = safeMalloc(part1VertNum * sizeof(char*));
		for(i = 0; i < part1VertNum; i++)
		{
			graph->p1matrix[i] = safeMalloc(part2VertNum * sizeof(char));
		} 
	} 

	if(part2VertNum != 0)
	{

		graph->p2matrix = safeMalloc(part2VertNum * sizeof(char*));
		for(i = 0; i < part1VertNum; i++)
		{
			graph->p2matrix[i] = safeMalloc(part1VertNum * sizeof(char));
		} 
	} 

	for(i = 0; i < part1VertNum; i++)
	{
		graph->p1matrix[i][0] = '1';
	}	
	for(i = 0; i < part2VertNum; i++)
	{
		graph->p2matrix[i][0] = '1';
	} 
	

	return graph;
} /* end of bipartGraphDestroy() */


void bipartGraphDestroy(bpGraph_t* pGraph)
{
	/* TODO: Implement me! */
	safeFree(pGraph->p1matrix,sizeof(char **)*pGraph->p1Verts);
	safeFree(pGraph->p2matrix,sizeof(char **)*pGraph->p2Verts);
	safeFree(pGraph,sizeof(bpGraph_t));

} /* end of bipartGraphDestroy() */


int bipartGraphInsertVertex(bpGraph_t* pGraph, int vertId, int partite)
{
	/* TODO: Implement me!*/ 
	int i;

	if(partite == 1)
	{	
		if(vertId > pGraph->p1Verts)
		{
			if(vertId == 0)
			{
				pGraph->p1matrix = realloc(pGraph->p1matrix,sizeof(char*));
				for(i = 0; i < 1; i++)
				{
					pGraph->p1matrix[i] = realloc(pGraph->p1matrix[i],sizeof(char) * pGraph->p2Verts);
				} 

				pGraph->p1matrix[0][0] = 1;
				pGraph->p1Verts = vertId;
				return SUCCESS;
			}

			pGraph->p1matrix = realloc(pGraph->p1matrix,sizeof(char*) * vertId);
			for(i = 0; i < vertId; i++)	
			{
				pGraph->p1matrix[i] = realloc(pGraph->p1matrix[i],sizeof(char) * pGraph->p2Verts);
			}
			pGraph->p1Verts = vertId;
			pGraph->p1matrix[vertId+1][0] = '1';
			return SUCCESS;
		} 
		if(pGraph->p1matrix[vertId+1][0] == '1')
			return EXISTING_VERTEX;
	
		
		pGraph->p1matrix[vertId][0] = '1';
		return SUCCESS;
	} 
	else if(partite == 2)
	{
		if(vertId > pGraph->p2Verts)
		{
			if(vertId == 0)
			{
				pGraph->p2matrix = realloc(pGraph->p2matrix,sizeof(char*));
				for(i = 0; i < 1; i++)
				{
					pGraph->p2matrix[i] = realloc(pGraph->p2matrix[i],sizeof(char) * pGraph->p2Verts);
				}	
				pGraph->p2matrix[0][0] = 1;
				pGraph->p2Verts = vertId;
				return SUCCESS;
			} 

			pGraph->p2matrix = realloc(pGraph->p2matrix,sizeof(char*) * vertId);
			for(i = 0; i < vertId; i++)	
			{
				pGraph->p2matrix[i] = realloc(pGraph->p2matrix[i],sizeof(char) * pGraph->p2Verts);
			}
			pGraph->p1Verts = vertId;
			pGraph->p2matrix[vertId+1][0] = '1';
			return SUCCESS;
		} 
		if(pGraph->p2matrix[vertId+1][0] == '1')
			return EXISTING_VERTEX;
	
		
		pGraph->p2matrix[vertId][0] = '1';
		return SUCCESS;	
		
	} 

	 
	return ERROR_VALUE;
} /* end of bipartGraphInsertVertex() */


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

