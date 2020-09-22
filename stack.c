
/*
 * stack.c - Source File
 * Implementation of the functions declared in the header file
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"
#include "graph.h"
#include "errorHandler.h"

/* --------Functions Deceleration--------- */

void			push(graph* , stack* );
graph*     	    pop(stack* );
bool            empty(const stack* );
stack*          initialize();

/* --------Functions Implementation---------*/

stack* initialize()
{
	stack *stk = (stack *)malloc(sizeof(stack));
	if(stk == NULL) returnErrorByType(10);

	stk -> cnt = 0;
	stk -> top = NULL;

	return stk;
}

void push(graph* group, stack* stk)
{ 
	elem   *newGraphElem;

	newGraphElem = (elem *)malloc(sizeof(elem));
	if(stk == NULL) returnErrorByType(11);

	newGraphElem -> group = group;
	newGraphElem -> next = stk -> top;
	stk -> top = newGraphElem;
	stk -> cnt++;
}

graph* pop(stack* stk)
{ 
	graph   *group;
	elem   *newGraphElem;

	if(stk == NULL) returnErrorByType(11);
	if(empty(stk))  return NULL;

	group = (stk -> top) -> group;
	newGraphElem = stk -> top;
	stk -> top = (stk -> top) -> next;
	stk -> cnt--;
	free(newGraphElem);

	return group;
}

bool empty(const stack* stk)
{ 
	return stk -> cnt == EMPTY;
}

bool full(const stack *stk)
{
	return stk -> cnt == FULL;
}
