
/* spmat.h - Header File
 *
 * A linked list implementation of a sparse matrix.
 *
 * Sparse matrix represents the adjacency matrix of a graph.
 * Each linked list in the matrix, represents the neighbors of the nodes in the graph.
 * If two nodes aren't neighbors, they will not be included in the linked list of each other in the sparse matrix.
 * An instance of a sparse matrix, is created only once during the program, and represents the adjacency matrix of the input graph.
 *
 * In order to distinguish between linked lists, according to the definition of linked list structure:
 * 			Each linked list contains an index ("node_index") that belongs to the relevant node.
		    By this value, we can distinguish who the list of neighbors belongs to.

 * The sparse matrix is based on an array of linked list.
 * The "spmat" structure contains the following fields:
 * 		   "n"    - represents the matrix size (n * n)
 * 		"private" - an inner implementation (linked list in our case)
 *
 * spmat_allocate_list  - Creating a new sparse matrix instance
 * add_row 		     	- Reading a matrix into the sparse, row by row
 * spmat_free           - Frees all resources used by the "spmat" structure
 */

#ifndef SPMAT_H
#define SPMAT_H

#include "graph.h"

typedef struct _spmat
{
	int		n;

	void	*private;

	/*
	 * The function initializes the sparse matrix, creating the linked lists of the sparse matrix,
	 * by receiving the i'th row of the original matrix (n x n).
	 * Each row is adjusted to a corresponding linked list in the i'th place of the "spmat" structure.
	 *
	 * This function is being called when the input graph is created,
	 * exactly n times in order (i = 0 to n-1)
	 */

	void	(*add_row)(struct _spmat *A, const int *row, int i, int j);

	/*
	 * Frees the linked list implementation of the sparse matrix (using built in free function for linked list)
	 */
	void	(*spmat_free)(struct _spmat *A);

} spmat;

/**
 * Initializing a new linked-lists sparse matrix of size n.
 * Sets the sparse matrix field to the corresponding values.
 *
 * @param  - a pre- allocated sparse matrix and an integer value representing the size n x n.
 * If the input matrix is NULL, the function throws an error and exits the program.
 */
void 		spmat_allocate_list(spmat *, int);

#endif
