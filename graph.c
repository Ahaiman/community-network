
/*
 * graph.c - Source File
 * Implementation of the functions declared in the header file
 */

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "errorHandler.h"

/* --------Functions Deceleration--------- */

void			allocate_graph(graph*, int, int* );
void			free_graph(graph* );

/* --------Functions Implementation---------*/

void allocate_graph(graph *myGraph, int n, int *graph_nodes)
{
	if(myGraph == NULL) returnErrorByType(1);

	myGraph -> n = n;
	myGraph -> graph_nodes = graph_nodes;
	myGraph -> free_graph = free_graph;
}

void free_graph(graph *G)
{
	free(G -> graph_nodes);
	free(G);
}
