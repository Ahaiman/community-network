
/* Stack.c
 *
 * Implementation of the functions declared in the Header file.
  */

#include "stack.h"
#include "linkedList.h"

void initialize(stack *stk)
{
   stk -> cnt = 0;
   stk -> top = NULL;
}

void push(linkedList list, stack *stk)
{ 
   elem   *p;

   p = malloc(sizeof(elem));
   p -> list = list;
   p -> next = stk -> top;
   stk -> top = p;
   stk -> cnt++;
}

linkedList pop(stack *stk)
{ 
   linkedList   list;
   elem   *p;

   list = stk -> top -> list;
   p = stk -> top;
   stk -> top = stk -> top -> next;
   stk -> cnt--;
   free(p);
   return list;
}

linkedList top(const stack *stk)
{ 
   return (stk -> top -> list);
}

boolean empty(const stack *stk)
{ 
   return ((boolean) (stk -> cnt == EMPTY));
}

