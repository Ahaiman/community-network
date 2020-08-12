#include "spmat.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * --------Structer---------
 */


typedef struct node {
    double value;
    int index;
    struct node *next;
} node;

typedef struct linkedList {
    node *head;
} linkedList;


/*
 * --------Functions Definition---------
 */

void add_row_to_list(spmat *A, const double *row, int i);
void freeRow_list(node *rowHead);
void free_list(struct _spmat *A);
void mult_list(const struct _spmat *A, const double *v, double *result);
node *createNode(double value, int index);
linkedList *createLinkedList();


/*constructor for node*/
node *createNode(double value, int index) {
    node *newNode = (node *)malloc(sizeof(node));
    assert(newNode!=NULL);
    newNode->value = value;
    newNode->index = index;
    newNode->next = NULL;
    return newNode;
}

/* constructor for linkedList*/
linkedList *createLinkedList() {
    linkedList *list = (linkedList *)malloc(sizeof(linkedList));
    assert(list!=NULL);
    list->head = NULL;
    return list;
}


/*
 * --------Linked List---------
 */


spmat *spmat_allocate_list(int n) {
    spmat *matrix;
    linkedList **rows;
    matrix = (spmat *)malloc(sizeof(spmat));
    assert(matrix != NULL);
    rows = (linkedList **)malloc(n*sizeof(linkedList *));
    assert(rows != NULL);

    matrix->private = rows;
    matrix->n = n;
    matrix->add_row = add_row_to_list;
    matrix->free = free_list;
    matrix->mult = mult_list;
    return matrix;
}



/*
 * adds a the i'th row in the linkedList implementation
 */
void add_row_to_list(struct _spmat *A, const double *row, int i) {
    int col;
    node *curr, *tmp;
    bool headUpdated = 0;
    linkedList *currRow = createLinkedList(); /* currRow->size = 0, currRow->head = NULL; */
    for (col = 0; col < A->n; col++) {
        if (*row != 0) {
            tmp = createNode(*row, col);   /*tmp->value = *row, tmp->index = col*/
            if (headUpdated == 0) {
                currRow->head = tmp;
                curr = tmp;
                headUpdated = 1;
            }
            else {
                curr->next = tmp;
                curr = curr->next;
            }
        }
        row++;
    }
    ((linkedList **) A->private)[i] = currRow;
}



/*
 * frees the linkedList implementation of the sparsMatrix
 */
void free_list(struct _spmat *A) {
    linkedList **rows =  ((linkedList **) A->private), **rowsStart = rows, *currRow;
    int row;
    for (row = 0; row < A->n; row++) {
        currRow = *rows;
        freeRow_list((currRow)->head);
        free(currRow);
        rows++;
    }
    free(rowsStart);
    free(A);
}

/*
 * frees every row in the linkedList implementation using recursion
 */
void freeRow_list(node *rowHead) {
    if (rowHead != NULL) {
        freeRow_list(rowHead->next);
        free(rowHead);
    }
}


void mult_list(const struct _spmat *A, const double *v, double *result) {
    int row;
    register double sum;
    node* currNode;
    linkedList *currRow, **rows = A->private;
    assert(result!=NULL);

    for (row = 0; row < A->n; row++) {
        currRow = *rows;    /*  currRow = rows[row]; */
        currNode = currRow->head;
        sum = 0;
        while (currNode != NULL) {
            sum += (currNode->value)*(v[currNode->index]);
            currNode = currNode->next;
        }
        rows++;
        *result = sum;
        result++;
    }
}

