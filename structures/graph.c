/*
 * node.c
 *
 *  Created on: 11 баев„ 2020
 *      Author: Avital
 */

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include "graph_node.h"



/*
 * --------Functions Definition---------
 */

	int	get_size(graph *);
	int	get_num_edges(graph *);
	spmat *get_relate_matrix(graph *);
	void set_size(graph *, int);
	void set_num_edges(graph *, int);
	void set_relate_matrix(graph *, spmat *);
	void set_nodes(graph *, graph_node **);
	void free_graph(graph *, int freeNode, int freeLists);
	graph* allocate_graph(int, int, graph_node **, spmat *);


/*
 * --------Functions Implementation---------
 */

/*constructor for graph*/

graph* allocate_graph(int n, int m, graph_node **graph_nodes, spmat *relate_matrix){
	graph* myGraph;
	myGraph	= (graph *) malloc (sizeof(myGraph));

    if(myGraph == NULL){
    	printf("Allocation Failed");
    	exit(0);
    }

    myGraph -> n = n;
    /*myGraph -> m = m;*/
    myGraph -> relate_matrix = relate_matrix;
    myGraph -> graph_nodes = graph_nodes;
    myGraph -> free_graph = free_graph;
    return myGraph;
}


void free_graph(graph *G, int freeNode, int freeLists){
	int i = 0;
	int *curr_arr;
	graph_node *curr_node;

	/*free matrix*/
	spmat_free(G -> relate_matrix, freeLists);

	/*free nodes list - if needed*/
	if(freeNode == 1){
		for(i = 0; i < G -> n; i++){
			curr_node = *(G -> graph_nodes);
			free_node(curr_node);
			(G -> graph_nodes)++;
		}
	G -> graph_nodes = (G -> graph_nodes) - (G -> n);
	}

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
