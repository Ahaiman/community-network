
//19/8

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./spmat.h"
#include "./graph.h"
#include "./linkedList.h"

/*
 * --------Functions Definition---------
 */

void spmat_allocate_list(spmat *,int);
void add_row_to_list(spmat *, const int *, int, int);
void free_list(struct _spmat *, int);
void freeRow_list(linkedList_node*);
//void mult_list(graph *, const double *, double *);
//void mult_spmat_s(spmat *A, const int *s, double *result);

/*
 * --------Implementation With Linked List---------
 */


void spmat_allocate_list(spmat *matrix, int n)
{

    linkedList **rows_indices;

    if(matrix == NULL)
    {
       	printf("Allocation of matrix Failed");
       	exit(0);
    }
    rows_indices = (linkedList **)malloc(n*sizeof(linkedList *));
    if(rows_indices == NULL)
    {
		printf("Allocation of rows Failed");
		exit(0);
    }

    matrix -> private = rows_indices;
    matrix -> n = n;
    matrix -> add_row = add_row_to_list;
//    matrix -> spmat_mult = mult_list;
    matrix-> spmat_free = free_list;
}



/*
 * adds a the i'th row in the linkedList implementation
 */
void add_row_to_list(struct _spmat *A, const int *row, int row_size, int i)
{
    linkedList *currRow = createLinkedList();
    linkedList_node *curr, *tmp;
    bool headUpdated = 0;
    int col;

    for (col = 0; col < row_size; col++)
    {
            tmp = createNode(*row);   /* tmp->index = *row*/
            if (headUpdated == 0)
            {
                currRow -> head = tmp;
                curr = tmp;
                headUpdated = 1;
            }
            else
            {
                curr -> next = tmp;
                curr = curr-> next;
                curr -> next = NULL;
            }
        row++;
    }

    currRow -> node_index = i;
    currRow -> size = row_size;
    *((linkedList**)(A -> private) + i) = currRow;
}


/*
 * frees the linkedList implementation of the sparsMatrix
 */
void free_list(struct _spmat *A, int freeInnerLists)
{
	linkedList **rows =  ((linkedList **) A->private), **rowsStart = rows, *currRow;
	int row;
	if(freeInnerLists)
	{
		for (row = 0; row < A->n; row++)
		{
			currRow = *rows;
			freeRow_list((currRow)->head);
			free(currRow);
			rows++;
		}
    }
    free(rowsStart);
    free(A);
}

/*
 * frees every row in the linkedList implementation using recursion
 */
void freeRow_list(linkedList_node *rowHead)
{
    if (rowHead != NULL)
    {
        freeRow_list(rowHead->next);
        free(rowHead);
    }
}

