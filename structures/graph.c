/*
 * node.c
 *
 *  Created on: 11 ����� 2020
 *      Author: Avital
 */

#include "graph.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>



/*
 * --------Functions Definition---------
 */

	int	get_size(graph *);
	int	get_num_edges(graph *);
	int	get_relate_matrix(graph *);
	void set_size(graph *, int);
	void set_num_edges(graph *, int);
	void set_relate_matrix(graph *, int **);
	void set_nodes(graph *, node **);
	void free_graph(graph *);
	graph* allocate_graph(int, int, node **, int **);


	/*
	 * --------Functions Implementation---------
	 */

/*constructor for graph*/

graph* allocate_graph(int n, int m, struct _node **graph_nodes, int **relate_matrix){
	graph* myGraph;
	myGraph	= (graph *) malloc (sizeof(myGraph));

    if(myGraph == NULL){
    	printf("Allocation Failed");
    	exit(0);
    }

    myGraph -> n = n;
    myGraph -> m = m;
    myGraph -> relate_matrix = relate_matrix;
    myGraph -> graph_nodes = graph_nodes;
    myGraph -> get_size = get_size;
    myGraph -> get_num_edges = get_num_edges;
    myGraph -> get_relate_matrix = get_relate_matrix;
    myGraph -> set_size = set_size;
    myGraph -> set_num_edges = set_num_edges;
    myGraph -> set_relate_matrix = set_relate_matrix;
    myGraph -> set_nodes = set_nodes;
    myGraph -> free_graph = free_graph;
    return myGraph;
}


int	get_size(graph *G){
	return G -> n;
}

int	get_num_edges(graph *G){
	return G -> m;
}

int	get_relate_matrix(graph *G){
	return G -> relate_matrix;
}
int	get_edges(graph *G){
	return G -> m;
}
void set_size(graph *G, int n){
	G -> n = n;
}
void set_num_edges(graph *G, int m){
	G -> m = m;
}
void set_relate_matrix(graph *G, int **matrix){
	G -> relate_matrix = matrix;

}
void set_nodes(graph *G, node **nodes_list){
	G -> graph_nodes = nodes_list;
}
void free_graph(graph *G){
	int i = 0;
	int *curr_arr;
	node *curr_node;

	/*free matrix*/
	for(; i < G -> n; i++){
		curr_arr = *(G -> relate_matrix);
		free(curr_arr);
		(G -> relate_matrix)++;
	}
	G -> relate_matrix = G -> relate_matrix - G -> n;
	free(G -> relate_matrix);

	/*free nodes list*/
	for(i = 0; i < G -> n; i++){
		curr_node = *(G -> graph_nodes);
		free_node(curr_node);
		(G -> graph_nodes)++;
	}
	G -> graph_nodes = G -> graph_nodes - G -> n;
	free(G -> graph_nodes);

}

