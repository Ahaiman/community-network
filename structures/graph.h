/*
 * graph.h
 *
 * TO ADD LATER - EXPLAINATIONS0
 *
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "spmat.h"
#include "graph_node.h"

typedef struct _graph {
	/* Number of vertices in the graph : |V| = n */
	int		n;

	/* Number of edges in the graph : |E| = m */
	int     m;

	/* Matrix that represent the relationship between nodes in the graph */
	spmat    *relate_matrix;

	graph_node **graph_nodes;

	/* Frees all resources used by G */
	void (*free_graph)(struct _graph *G);

} graph;

/* Allocates a new linked-lists sparse matrix of size n */

graph* allocate_graph(int n, int m, graph_node **graph_node, spmat *relate_matrix);
#endif






//	/* Returns the size of the graph i.e the number of vertices */
//	int	(*get_size)(struct _graph *G);
//
//	/* Returns the number of edges in the graph */
//	int	(*get_num_edges)(struct _graph *G);
//
//	/* Returns the number of edges in the graph */
//	int	(*get_relate_matrix)(struct _graph *G);
//
//	/* Sets the size of the graph i.e the number of vertices */
//	void(*set_size)(int size);
//
//	/*  Sets the number of edges in the graph */
//	void (*set_num_edges)(int m);
//
//	/*  Sets the number of edges in the graph */
//	void (*set_relate_matrix)(spmat *matrix);
//
//	/*  Sets the number of edges in the graph */
//	void (*set_nodes)(graph_node **graph_node);
