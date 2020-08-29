
/* Stack.h - Header File
 *
 * A linked list implementation of a stack.
 *
 * Each element in the stack is a linked-list of graph nodes.
 * The stack contains two fields:
 * 		count - representing the number of element in the stack
 * 		top - a pointer to to the top element in the stack
 *
  */


#ifndef STRUCTURES_STACK_H
#define STRUCTURES_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define   EMPTY      0
#define   FULL       5000000 // five million


typedef   enum {false, true}   boolean;

typedef struct elem {                   /* an element on the stack */
	graph          *group;
    struct elem   *next;
} elem;

//typedef   struct elem   elem;

typedef struct stack{
   int    cnt;                  /* a count of the elements */
   elem   *top;                 /* ptr to the top element */
   void            (*initialize)(struct stack *stk);
   void            (*push)(graph *group, struct stack *stk);
   graph*     	    (*pop)(struct stack *stk);
   boolean         (*empty)(const struct stack *stk);
} stack;


//typedef   struct stack   stack;


#endif
