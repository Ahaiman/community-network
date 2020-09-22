
/* graph.h - Header File
 *
 * Implementation of a graph structure.
 *
 * The graph contains two fields:
 * 		     "n"      - representing the number of nodes in the graph
 * 		"graph_nodes" - a list of the nodes values in the graph
 *
 * allocate_graph - Creates a new graph
 * free_graph     - Frees all the memory resources used by the graph
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "spmat.h"

typedef struct _graph {

	/*Number of vertices in the graph: |V| = n*/
	int 	n;

	/*List of the nodes in the graph, according to their initial value*/
	int		*graph_nodes;

	void	(*free_graph)(struct _graph* );

} graph;

/**
 * Setting values to the inner fields of the pre-initialized graph structure (using dynamic allocation).
 *  If graph == NULL, throws an error and exits the program.
 *
 * @param graph              - pointer to an pre- initialized graph.
 * @param integer            - the size of the graph (number of nodes).
 * @param vector of integers - the graph's nodes list
 */
void           allocate_graph(graph* , int , int* );

#endif
