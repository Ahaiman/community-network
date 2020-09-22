
/*
 * spmat.c - Source File
 * Implementation of the functions declared in the header file
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "spmat.h"
#include "graph.h"
#include "linkedList.h"
#include "errorHandler.h"

/* --------Functions Deceleration--------- */

void			spmat_allocate_list(spmat * ,int);
void     	    add_row_to_list(spmat * , const int *, int, int);
void            spmat_free(spmat *);

/* --------Functions Implementation---------*/

void spmat_allocate_list(spmat *matrix, int n)
{
	linkedList **spmatRows;

	if(matrix == NULL) returnErrorByType(3);

	spmatRows = (linkedList **)malloc(n * sizeof(linkedList *));
	if(spmatRows == NULL) returnErrorByType(8);

	matrix -> n = n;
	matrix -> private = spmatRows;
	matrix -> add_row = add_row_to_list;
	matrix-> spmat_free = spmat_free;
}

void add_row_to_list(struct _spmat *A, const int *matrixRow, int row_size, int i)
{
	/*Creating a new linked list for each row*/
	linkedList *currRow = createLinkedList();

	linkedList_node *curr, *tmpNode;
	int currNodeValue;
	bool headUpdated = 0;
	int col;

	for (col = 0; col < row_size; col++)
	{
		/*Creating a new node for each value in the input matrix row*/
		currNodeValue = *matrixRow;
		tmpNode = createNode(currNodeValue);

		/*Initializing a new linked list*/
		if (headUpdated == 0)
		{
			currRow -> head = tmpNode;
			curr = tmpNode;
			headUpdated = 1;
		}
		else
		{
			curr -> next = tmpNode;
			curr = curr-> next;
			curr -> next = NULL;
		}
		matrixRow++;
	}

	/*Each linked list represents the neighbors of a specific node in the graph*/
	currRow -> node_index = i;
	currRow -> size = row_size;
	*((linkedList**)(A -> private) + i) = currRow;
}

void spmat_free(spmat *matrix)
{
	linkedList **spmatRows =  ((linkedList **) matrix -> private), *currRow;
	int row;

	for (row = 0; row < matrix -> n; row++)
	{
		/*Frees each linked list*/
		currRow = *spmatRows;
		currRow -> free_linkedList(currRow);
		spmatRows++;
	}

	/*Frees the array of lists*/
	free(matrix -> private);

	/*Frees the sparse structure*/
	free(matrix);
}
