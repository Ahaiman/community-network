
//19/8

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./spmat.h"
#include "./linkedList.h"

/*
 * --------Functions Definition---------
 */

spmat *spmat_allocate_list(int);
void add_row_to_list(spmat *, const double *, int);
void freeRow_list(linkedList_node*);
void free_list(struct _spmat *, int);

/*
 * --------Implementation With Linked List---------
 */


spmat *spmat_allocate_list(int n)
{
    spmat *matrix;
    linkedList **rows_indices;
    matrix = (spmat *)malloc(sizeof(spmat));
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

    matrix-> private = rows_indices;
    matrix-> n = n;
    matrix-> add_row = add_row_to_list;
    matrix -> spmat_mult = mult_list;
    matrix->spmat_free = free_list;
    return matrix;
}



/*
 * adds a the i'th row in the linkedList implementation
 */
void add_row_to_list(struct _spmat *A, const double *row, int row_size, int i)
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
    A->private[i] = currRow;
}


/*
 * frees the linkedList implementation of the sparsMatrix
 */
void free_list(struct _spmat *A, freeInnerLists)
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


void mult_list(spmat *A, const double *v, double *result)
{
    linkedList_node *currNode;
    linkedList *currList, **rows_indices = A->private;
    int row, n = A -> n;
    double sum;

    if(result == NULL)
    {
		printf("result is not allocated");
		exit(0);
    }

    for (row = 0; row < n; row++)
    {
    	currList = *rows_indices;
        currNode = currList -> head;
        sum = 0;
        while (currNode != NULL)
        {
            sum += *(v + (currNode -> value));
            currNode = currNode->next;
        }
        rows_indices++;
        *result = sum;
        result++;
    }
}
