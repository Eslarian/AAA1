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
	int i;

	if(partite == 1) 
	{
		pGraph->matrix = safeRealloc(pGraph->matrix,newSize * sizeof(char*),sizeof(char*) * (newSize - pGraph->p1Verts));
		for(i = pGraph->p1Verts; i < newSize; i++)
		{
			pGraph->matrix[i] = safeMalloc(pGraph->p2Verts* sizeof(char));
		} 
		pGraph->p1Verts = newSize;
	} 

	if(partite == 2)
	{
		for(i = 0; i < pGraph->p1Verts; i++)
		{
			pGraph->matrix[i] = safeRealloc(pGraph->matrix[i],newSize * sizeof(char),(newSize - pGraph->p2Verts));
		}
		pGraph->p2Verts = newSize;
	} 

} 

void bipartGraphDestroy(bpGraph_t* pGraph)
{
	safeFree(pGraph->matrix,sizeof(char **)*pGraph->p2Verts);
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
			resizeMatrix(pGraph,vertId+1,1);	
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
			resizeMatrix(pGraph,vertId+1,2);
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
	if(srcPartite == 1)
	{
		if(srcVertId < pGraph->p1Verts && tarVertId < pGraph->p2Verts)
		{
			if(pGraph->vVertExistP1[srcVertId] == 1)
			{
				if(pGraph->matrix[srcVertId][tarVertId] == 0) 
				{
					pGraph->matrix[srcVertId][tarVertId] = 1;
					return SUCCESS;
				} 
				if(pGraph->matrix[srcVertId][tarVertId] == 2)
				{
					pGraph->matrix[srcVertId][tarVertId] = 3;
					return SUCCESS;
				} 	

				return EXISTING_VERTEX;
			}
		} 
	} 
	if(srcPartite == 2)
	{
		if(srcVertId < pGraph->p2Verts && tarVertId < pGraph->p1Verts)
		{
			if(pGraph->vVertExistP2[srcVertId] == 1)
			{
				if(pGraph->matrix[tarVertId][srcVertId] == 0) 
				{
					pGraph->matrix[tarVertId][srcVertId] = 2;
					return SUCCESS;
				} 
				if(pGraph->matrix[tarVertId][srcVertId] == 2)
				{
					pGraph->matrix[tarVertId][srcVertId] = 3;
					return SUCCESS;
				} 

				return EXISTING_VERTEX;
			}
		} 
	
	} 

	
	return ERROR_VALUE;
} /* end of bipartGraphInsertEdge() */


int bipartGraphDeleteVertex(bpGraph_t* graph, int vertId, int partite)
{
	/* TODO: Implement me! */
	int i;

	if(partite == 1)
	{
		if(vertId < graph->p1Verts)
		{
			for(i = 0; i < graph->p2Verts;i++)
			{
				bipartGraphDeleteEdge(graph,vertId,i,1);
			}
			graph->vVertExistP1[vertId] = 0;	
			return SUCCESS;
		}
		return NOT_FOUND;
	} 
	if(partite == 2)
	{
		if(vertId < graph->p2Verts)
		{
			for(i = 0; i < graph->p1Verts;i++)
			{
				bipartGraphDeleteEdge(graph,vertId,i,2);
			}
			graph->vVertExistP2[vertId] = 0;
			return SUCCESS;
		}
		return NOT_FOUND;
	} 

	return ERROR_VALUE;
} /* end of bipartGraphDeleteVertex() */


int bipartGraphDeleteEdge(bpGraph_t* pGraph,  int srcVertId, int tarVertId, int srcPartite)
{
	/* TODO: Implement me! */
	if(srcPartite == 1)
	{
		if(srcVertId < pGraph->p1Verts)
		{
			if(pGraph->vVertExistP1[srcVertId] == 1) 
			{
				if(pGraph->matrix[srcVertId][tarVertId] == 0 || pGraph->matrix[srcVertId][tarVertId] == 2) 
					return NOT_FOUND;	

				pGraph->matrix[srcVertId][tarVertId] -= 1;
				return SUCCESS; 
			} 
		} 
	} 
	if(srcPartite == 2)
	{	
		if(srcVertId < pGraph->p2Verts)
		{
			if(pGraph->vVertExistP2[srcVertId] == 1)
			{
				if(pGraph->matrix[tarVertId][srcVertId] == 0 || pGraph->matrix[tarVertId][srcVertId] == 1) 
					return NOT_FOUND;
				pGraph->matrix[tarVertId][srcVertId] -= 2;
				return SUCCESS;
			}
		} 
	} 
	
	return ERROR_VALUE;
} /** end of bipartGraphDeleteEdge() */


int bipartGraphFindVertex(bpGraph_t *pGraph, int vertId, int partite)
{
	/* TODO: Implement me! */
	if(partite == 1)
	{
		if(vertId < pGraph->p1Verts)
		{
			if(pGraph->vVertExistP1[vertId] == 1)
				return FOUND;
			return NOT_FOUND;
		} 
	} 
	if(partite == 2)
	{
		if(vertId < pGraph->p2Verts)
		{
			if(pGraph->vVertExistP2[vertId] == 1)
				return FOUND;
			return NOT_FOUND;
		} 
	} 

	return ERROR_VALUE;
} /* end of bipartGraphFindVertex() */


int bipartGraphFindEdge(bpGraph_t* graph, int srcVertId, int tarVertId, int srcPartite)
{
	/** TODO: Implement me! */
	if(srcPartite == 1)
	{
		if(srcVertId < graph->p1Verts)
		{
			if(graph->vVertExistP1[srcVertId] == 1)
			{
				if(graph->matrix[srcVertId][tarVertId] == 1 || graph->matrix[srcVertId][tarVertId] == 3)
				{
					return FOUND;
				} 
			} 
			return NOT_FOUND;
		} 
	} 
	if(srcPartite == 2)
	{
		if(srcVertId < graph->p2Verts)
		{
			if(graph->vVertExistP2[srcVertId] == 1)
			{
				if(graph->matrix[tarVertId][srcVertId] == 2 || graph->matrix[tarVertId][srcVertId] == 3)
				{
					return FOUND;
				} 
			}
			return NOT_FOUND;
		} 
	}

	return ERROR_VALUE;
} /* end of bipartGraphFindEdge() */

void bipartGraphPrint(bpGraph_t *pGraph)
{
	/* TODO: Implement me!*/ 
	int i,j;

	printf("Vertices:\n");
	printf("Part 1:\n"); 

	for(i = 0; i < pGraph->p1Verts; i++)
	{	
		if(pGraph->vVertExistP1[i] == 1)
			printf("%d ",i);
	} 
	
	printf("\nPart 2:\n");
	for(i = 0; i < pGraph->p2Verts; i++)
	{
		if(pGraph->vVertExistP2[i] == 1)
			printf("%d ",i);
	} 
	printf("\nEdges:\n");
	printf("Part 1 to 2:\n");
	for(i = 0; i < pGraph->p1Verts; i++)
	{
		for(j = 0; j < pGraph->p2Verts; j++)
		{
			if(pGraph->matrix[i][j] == 1 || pGraph->matrix[i][j] == 3)
			{
				printf("%d %d\n",i,j);
			} 
		} 
	}
	printf("Part 2 to 1:\n");
	for(i = 0; i < pGraph->p1Verts; i++)
	{
		for(j = 0; j < pGraph->p2Verts; j++)
		{
			if(pGraph->matrix[i][j] == 2 || pGraph->matrix[i][j] == 3)
			{
				printf("%d %d\n",j,i);
			} 
		} 
	}
	
	
} /* end of bipartGraphPrint() */

