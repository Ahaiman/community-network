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
	void allocate_graph(graph *, int, int *);
	void free_graph(graph *);

/*
 * --------Functions Implementation---------
 */

/*constructor for graph*/

void allocate_graph(graph *myGraph, int n, int *graph_nodes){
//	graph* myGraph;
//	myGraph	= (graph *) malloc (sizeof(myGraph));

    if(myGraph == NULL)
    {
    	printf("Graph allocation failed");
    	exit(0);
    }

    myGraph -> n = n;
    /*myGraph -> m = m;*/
    myGraph -> divisionNumber = 0;
//    myGraph -> relate_matrix = relate_matrix;
    myGraph -> graph_nodes = graph_nodes;
//    myGraph -> degrees = NULL;

    myGraph -> free_graph = free_graph;

//    return myGraph;
}

void free_graph(graph *G)
{

	/*(1) free relate matrix*/
//	G -> relate_matrix -> spmat_free(G -> relate_matrix, doFreeLists);

	/*(2) free the list itself */
	free(G -> graph_nodes);
}
