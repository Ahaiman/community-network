/*
 * node.c
 *
 *  Created on: 11 баев„ 2020
 *      Author: Avital
 */

#include "node.h"
#include <stdio.h>
#include <stdlib.h>



/*
 * --------Functions Definition---------
 */
	int	get_index (node *);
	int get_degree(node *);
	node** get_neighbors(node *);
	int get_group(node *);
	int did_move(node *);
	void set_degree(node *, int);
	void set_neighbors(node *, node *);
	void allocate_neighbors(node *, int);
	void set_group(node *, int);
	void move(node *, int);
	void free_node(node *);
	node *allocate_node(int);

	/*
	 * --------Functions Implementation---------
	 */

/*constructor for node*/

node *allocate_node(int i) {
	node *newNode;
    newNode	= (node *) malloc (sizeof(node));
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
    newNode -> free_node = free_node;
    return newNode;
}



int	get_index (struct _node *N){
	return N -> index;
}

int get_degree(struct _node *N){
	return N -> degree;
}

node** get_neighbors(struct _node *N){
	return N -> neighbors;

}
int get_group(struct _node *N){
	return N -> group;
}

int did_move(struct _node *N){
	return N -> has_moved;
}

void set_degree(struct _node *N, int degree){
	N -> degree = degree;
}
void set_neighbors(struct _node *N, struct _node **neighbors){
	N -> neighbors = neighbors;
}
struct _node** allocate_neighbors(int degree){
	struct _node** neighbors = (node **) malloc(sizeof(node*) * degree);
	return neighbors;

}
void set_group(struct _node *N, int group){
	N -> group = group;
}

void move(struct _node *N, int move){
	N -> move = move;
}

void free_node(struct _node *N){
	free(N -> neighbors);
	free(N);
}

