#ifndef _SPMAT_H
#define _SPMAT_H

#include "./graph.h"

typedef struct _spmat
{
	/* Matrix size (n*n) */
	int		n;

	/* Adds row i the matrix. Called before any other call,
	 * exactly n times in order (i = 0 to n-1) */
	void	(*add_row)(struct _spmat *A, const int *row, int i, int j);

	/* Frees all resources used by A */
	void	(*spmat_free)(struct _spmat *A, int freeInnerLists);

	/* Private field for inner implementation.
	 * Should not be read or modified externally */
	void	*private;
} spmat;

/* Allocates a new linked-lists sparse matrix of size n */
void spmat_allocate_list(spmat *matrix, int n);



#endif
