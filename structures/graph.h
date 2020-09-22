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

	int *graph_nodes;




	/* Matrix that represent the relationship between nodes in the graph */
//	 struct _spmat    *relate_matrix;

//	graph_node **graph_nodes;





	/*Vector representing the degrees of the nodes */
//	int *degrees;

	/* Frees all resources used by G , freeNode - represents whether nodes should be free to*/
	void (*free_graph)(struct _graph *G);

} graph;

/* Allocates a new linked-lists sparse matrix of size n */

void allocate_graph(graph *, int n, int *graph_node);

#endif
