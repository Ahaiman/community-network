
/* Stack.c
 *
 * Implementation of the functions declared in the Header file.
  */

#include <stdio.h>
#include <stdlib.h>
#include "./stack.h"
#include "./graph.h"

void            push(graph *group, stack *stk);
graph*     	    pop(stack *stk);
boolean         empty(const stack *stk);
stack            *initialize();

stack *initialize()
{
   stack *stk = (stack *)malloc(sizeof(stack));
   stk -> cnt = 0;
   stk -> top = NULL;
   return stk;
}

void push(graph *group, stack *stk)
{ 
   elem   *p;

   p = (elem *)malloc(sizeof(elem));
   p -> group = group;
   p -> next = stk -> top;
   stk -> top = p;
   stk -> cnt++;
}

graph* pop(stack *stk)
{ 
   graph*   group;
   elem   *p;

   group = (stk -> top) -> group;
   p = stk -> top;
   stk -> top = (stk -> top) -> next;
   stk -> cnt--;
   free(p);
   return group;
}

boolean empty(const stack *stk)
{ 
   return ((boolean) (stk -> cnt == EMPTY));
}

