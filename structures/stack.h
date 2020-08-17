
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

///aaaaa55556a555Avital is working now through git
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define   EMPTY      0
#define   FULL       5000000 // five million

typedef   enum {false, true}   boolean;

struct elem {                   /* an element on the stack */
	graph          group;
    struct elem   *next;
};

typedef   struct elem   elem;

struct stack {
   int    cnt;                  /* a count of the elements */
   elem   *top;                 /* ptr to the top element */
};

typedef   struct stack   stack;

void            initialize(stack *stk);
void            push(graph *group, stack *stk);
graph*     	    pop(stack *stk);
boolean         empty(const stack *stk);

//graph*          top(const stack *stk);
