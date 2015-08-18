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



struct implBipartGraph_t
{
	int vertNumP1;
	int vertNump2;

	linkedList_t * vertsP1;
	linkedList_t * vertsP2;	
	
		
};




/* ************************************************************************* */
/* Function implementations */


bpGraph_t* bipartGraphCreate(int part1VertNum, int part2VertNum)
{
	
	bpGraph_t * pGraph = safemalloc(sizeof(bpGraph_t));
	pGraph->vertNumP1 = part1VertNum;
	pGraph->vertNumP2 = part2VertNum;
	init_list(pGraph->vertNumP1);
	init_list(pGraph->vertNumP2);

	
	return pGraph;
} /* end of bipartGraphCreate() */


void bipartGraphDestroy(bpGraph_t* pGraph)
{
	/* TODO: Implement me! */
	int i;
	linkedList_t * curr;
	
	free_list(pGraph->vertsP1);
	free_list(pGraph->vertsP2);
	safeFree(pGraph, sizeof(bpGraph_t));
	

} /* end of bipartGraphDestroy() */


int bipartGraphInsertVertex(bpGraph_t* pGraph, int vertId, int partite)
{
	/* TODO: Implement me! */

	/* TODO: Replace placeholder. */
	return 0;
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

