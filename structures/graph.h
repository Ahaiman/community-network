/*
 * graph.h
 *
 * TO ADD LATER - EXPLAINATIONS0
 *
 */

#ifndef GRAPH_H_
#define GRAPH_H_

typedef struct _graph {
	/* Number of vertices in the graph : |V| = n */
	int		n;

	/* Number of edges in the graph : |E| = m */
	int     m;

	/* Matrix that represent the relationship between nodes in the graph */
	int    **relate_matrix;

	struct _node **graph_nodes;

	/* Returns the size of the graph i.e the number of vertices */
	int	(*get_size)(struct _graph *G);

	/* Returns the number of edges in the graph */
	int	(*get_num_edges)(struct _graph *G);

	/* Returns the number of edges in the graph */
	int	(*get_relate_matrix)(struct _graph *G);

	/* Sets the size of the graph i.e the number of vertices */
	void(*set_size)(int size);

	/*  Sets the number of edges in the graph */
	void (*set_num_edges)(int m);

	/*  Sets the number of edges in the graph */
	void (*set_relate_matrix)(int **matrix);

	/*  Sets the number of edges in the graph */
	void (*set_nodes)(struct _node **graph_node);


	/* Frees all resources used by G */
	void (*free_graph)(struct _graph *G);

} graph;

/* Allocates a new linked-lists sparse matrix of size n */

graph* allocate_graph(int n, int m, struct _node **graph_node, int **relate_matrix);
#endif

