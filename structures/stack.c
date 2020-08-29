
/* Stack.c
 *
 * Implementation of the functions declared in the Header file.
  */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void            initialize(stack *stk);
void            push(graph *group, stack *stk);
graph*     	    pop(stack *stk);
boolean         empty(const stack *stk);

void initialize(stack *stk)
{
   stk -> cnt = 0;
   stk -> top = NULL;
   stk -> push = push;
   stk -> pop = pop;
   stk -> empty = empty;
}

void push(graph *group, stack *stk)
{ 
   elem   *p;

   p = malloc(sizeof(elem));
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

