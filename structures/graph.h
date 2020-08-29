/*
 * graph.h
 *
 * TO ADD LATER - EXPLAINATIONS0
 *
 */

//updated 18.8

#ifndef GRAPH_H_
#define GRAPH_H_

#include "./spmat.h"


typedef struct _graph {
	/* Number of vertices in the graph : |V| = n */
	int		n;

	/* The number of the group in S vector*/
	int divisionNumber;

	/* Matrix that represent the relationship between nodes in the graph */
	spmat    *relate_matrix;

//	graph_node **graph_nodes;

	int *graph_nodes;

	/*Vector representing the degrees of the nodes */
	int *degrees;

	/* Frees all resources used by G , freeNode - represents whether nodes should be free to*/
	void (*free_graph)(struct _graph *G, int freeLists);

} graph;

/* Allocates a new linked-lists sparse matrix of size n */

graph* allocate_graph(int n, int *graph_node, spmat *relate_matrix);

#endif
