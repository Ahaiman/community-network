
/* Stack.c
 *
 * Implementation of the functions declared in the Header file.
  */

#include "stack.h"
#include "graph.h"
#include <stdbool.h>

void initialize(stack *stk)
{
   stk -> cnt = 0;
   stk -> top = NULL;
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

