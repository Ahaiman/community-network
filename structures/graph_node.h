/*
 * node.h
 *
 *  Created on: 11 баев„ 2020
 *      Author: Avital
 */

#ifndef STRUCTURES_GRAPH_NODE_H_
#define STRUCTURES_GRAPH_NODE_H_

typedef struct _graph_node{

	/* Number of vertices in the graph : |V| = n */
	int		index;

	/* Number of edges in the graph : |E| = m */
	int    degree;

	/*0(initial), 1 , -1 */
	int		group;

	/*0 or 1*/
	int		has_moved;


	struct _graph_node		*neighbors;


	/* Returns the index of the node */
	int	(*get_index)(struct _graph_node *N);

	/* Sets the degree of the node */
	int(*get_degree)(struct _graph_node *N);

	/* Returns the array of the node's neighbors */
	struct _graph_node** (*get_neighbors)(struct _graph_node *N);

	/* Sets the degree of the node */
	int(*get_group)(struct _graph_node *N);

	int (*did_move)(struct _graph_node *N);

//	/* Sets the size of the graph i.e the number of vertices */
//	void	(*set_index)(struct _node *N);

	/*  Sets the degree of the node */
	void (*set_degree)(struct _graph_node *N, int degree);

	/* Sets the array representing the node's neighbors */
	void (*set_neighbors)(struct _graph_node *N, struct _graph_node **neighbors);

	/* Sets the array representing the node's neighbors */
	void (*allocate_neighbors)(struct _graph_node *N, int degree);

	void (*set_group)(struct _graph_node *N, int group);

	void  (*move)(struct _graph_node *N, int move);

	/* Frees all resources used by Node */
	void	(*free_graph_node)(struct _graph_node *N);

}  graph_node;

/* Allocates a new Node with index i */
graph_node* allocate_node(int i);

#endif


