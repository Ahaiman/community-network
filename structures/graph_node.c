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
	int	get_index (graph_node *);
	int get_degree(graph_node *);
	graph_node** get_neighbors(graph_node *);
	int get_group(graph_node *);
	int did_move(graph_node *);
	void set_degree(graph_node *, int);
	void set_neighbors(graph_node *, graph_node *);
	void allocate_neighbors(graph_node *, int);
	void set_group(graph_node *, int);
	void move(graph_node *, int);
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
    newNode -> group = 0;
    newNode -> degree = -1;
    newNode -> has_moved = 0;
    newNode -> get_index = get_index;
    newNode -> get_degree = get_degree;
    newNode -> get_neighbors = get_neighbors;
    newNode -> get_group = get_group;
    newNode -> did_move = did_move;
    newNode -> set_degree = set_degree;
    newNode -> set_neighbors = set_neighbors;
    newNode -> allocate_neighbors = allocate_neighbors;
    newNode -> set_group = set_group;
    newNode -> move = move;
    newNode -> free_graph_node = free_graph_node;
    return newNode;
}



int	get_index (graph_node *N){
	return N -> index;
}

int get_degree(graph_node *N){
	return N -> degree;
}

graph_node** get_neighbors(graph_node *N){
	return N -> neighbors;

}
int get_group(graph_node *N){
	return N -> group;
}

int did_move(graph_node *N){
	return N -> has_moved;
}

void set_degree(graph_node *N, int degree){
	N -> degree = degree;
}
void set_neighbors(graph_node *N, graph_node **neighbors){
	N -> neighbors = neighbors;
}
struct graph_node** allocate_neighbors(int degree){
	struct _node** neighbors = (graph_node **) malloc(sizeof(graph_node*) * degree);
	return neighbors;

}
void set_group(struct graph_node *N, int group){
	N -> group = group;
}

void move(struct graph_node *N, int move){
	N -> move = move;
}

void free_node(struct graph_node *N){
	free(N -> neighbors);
	free(N);
}

