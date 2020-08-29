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

	void free_graph(graph *, int , int);
	graph* allocate_graph(int, int, int *, spmat *);


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
	spmat_free(G -> relate_matrix, doFreeLists);

	/*(2) free the list itself */
	free(G -> graph_nodes);
}

//
//myGraph -> get_size = get_size;
//   myGraph -> get_num_edges = get_num_edges;
//   myGraph -> get_relate_matrix = get_relate_matrix;
//   myGraph -> set_size = set_size;
//   myGraph -> set_num_edges = set_num_edges;
//   myGraph -> set_relate_matrix = set_relate_matrix;
//   myGraph -> set_nodes = set_nodes;

//
//int	get_size(graph *G){
//	return G -> n;
//}
//
//int	get_num_edges(graph *G){
//	return G -> m;
//}
//
//spmat *get_relate_matrix(graph *G){
//	return G -> relate_matrix;
//}
//int	get_edges(graph *G){
//	return G -> m;
//}
//void set_size(graph *G, int n){
//	G -> n = n;
//}
//void set_num_edges(graph *G, int m){
//	G -> m = m;
//}
//void set_relate_matrix(graph *G, spmat *matrix){
//	G -> relate_matrix = matrix;
//
//}
//void set_nodes(graph *G, graph_node **nodes_list){
//	G -> graph_nodes = nodes_list;
