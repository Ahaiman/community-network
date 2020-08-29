/*
 * node.c
 *
 *  Created on: 11 баев„ 2020
 *      Author: Avital
 */


#include <stdio.h>
#include <stdlib.h>
#include "./graph.h"
#include "./spmat.h"

/*
 * --------Functions Definition---------
 */

	void free_graph(graph *, int);
	graph* allocate_graph(int, int *,spmat *);


/*
 * --------Functions Implementation---------
 */

/*constructor for graph*/

graph* allocate_graph(int n, int *graph_nodes, spmat *relate_matrix){
	graph* myGraph;
	myGraph	= (graph *) malloc (sizeof(myGraph));

    if(myGraph == NULL)
    {
    	printf("Graph allocation failed");
    	exit(0);
    }

    myGraph -> n = n;
    /*myGraph -> m = m;*/
    myGraph -> divisionNumber = 0;
    myGraph -> relate_matrix = relate_matrix;
    myGraph -> graph_nodes = graph_nodes;
    myGraph -> degrees = NULL;
    myGraph -> free_graph = free_graph;

    return myGraph;
}


void free_graph(graph *G, int doFreeLists)
{

	/*(1) free relate matrix*/
	G -> relate_matrix -> spmat_free(G -> relate_matrix, doFreeLists);

	/*(2) free the list itself */
	free(G -> graph_nodes);
}
