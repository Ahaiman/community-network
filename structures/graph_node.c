/*
 * node.c
 *
 *  Created on: 11 баев„ 2020
 *      Author: Avital
 */

#include "graph_node.h"
#include <stdio.h>
#include <stdlib.h>



/*
 * --------Functions Definition---------
 */

	void allocate_neighbors(graph_node *, int);s
	void free_graph_node(graph_node *);
	graph_node *allocate_node(int);

/*
 * --------Functions Implementation---------
 */

/*constructor for node*/

graph_node *allocate_node(int i) {
	graph_node *newNode;
    newNode	= (graph_node *) malloc (sizeof(graph_node));

    if(newNode == NULL){
    	printf("Allocation Failed");
    	exit(0);
    }

    newNode -> index = i;
//    newNode -> group = 0;
    newNode -> degree = 0;
    newNode -> set_neighbors = set_neighbors;
    newNode -> allocate_neighbors = allocate_neighbors;
    newNode -> free_graph_node = free_graph_node;
    return newNode;
}


graph_node** allocate_neighbors(int degree){
	graph_node **neighbors = (graph_node **) malloc(sizeof(graph_node *) * degree);
	return neighbors;

}
void free_graph_node(graph_node *N){
	free(N -> neighbors);
	free(N);
}

