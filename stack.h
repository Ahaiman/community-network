
/* stack.h - Header File
 *
 * A linked list implementation of a stack, according to LIFO.
 *
 * Each element in the stack consists of a graph structure and a pointer to the next element.
 * The stack contains two fields:
 * 		"cnt" - representing the current number of elements in the stack
 * 		"top" - a pointer to the top element in the stack
 *
 * 	initialize   - Initializes a new stack
 * 	push 		 - Pushes a new element into the stack (to the top)
 *	pop          - Removes the top element in the stack and returns it
 *	empty        - Checks if the stack is empty
 *	full 		 - Checks if the stack is full
 */

#ifndef STACK_H_
#define STACK_H_

#define   EMPTY      0
#define   FULL       5000000

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

typedef struct _elem {

	/*An element in the stack */
	graph*        	  group;

	/*A pointer to the next element in the stack */
	struct _elem*     next;

} elem;

typedef struct _stack{

	int		cnt;
	elem*	top;

} stack;

/**
 * Allocates a new stack using dynamic allocation.
 * Sets the stack's size to 0 (represented by the field "cnt"),
 * and the top element to NULL.
 *
 * @return
 * If allocation succeeded, returns a pointer to the new stack.
 * Otherwise, throws an error and exits the program.
 */

stack*          initialize();

/**
 * Creates a new element of the input graph.
 * Pushes the element into the stack, updates the top value and increases the stack's size.
 * Throws an error if the given stack is not initialized.
 *
 * @param graph - the input graph structure
 * @param stack - a pointer to the current stack
 */

void            push(graph*, stack*);

/**
 * Removes the top element in the given stack, and returns it.
 * Updated the new top value and decreases the stack's size.
 *
 * @param stack - a pointer to the current stack
 *
 * @return the graph at the top of the stack.
 * If the stack is empty, the function returns NULL.
 * If the stack is NULL, the function throws an error.
 */

graph*			pop(stack*);

/**
 * Checks if the stack is empty.
 *
 * @param const stack - pointer to the current stack, when stack != NULL
 *
 * @return stack size == EMPTY( = 0).
 */

bool            empty(const stack*);

/**
 * Checks if the stack is full.
 *
 * @param const stack - pointer to the current stack, when stack != NULL
 *
 * @return stack size == FULL ( = 5000000).
 */

bool            full(const stack*);

#endif
