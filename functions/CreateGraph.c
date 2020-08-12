/*
 * CreateGraph.c
 *
 *  Created on: 11 баев„ 2020
 *      Author: Avital
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../structures/graph.h"
#include "../structures/node.h"
#include "../structures/spmat.h"

graph *createGraph(char *name_of_input_file){

	/*Variables deceleration*/
	FILE	*input_file;
	graph *input_graph;
	node *curr_node;
	node **nodes_list, **neighbors;
	int *curr_neighbors;
	int **relate_matrix;
	int n, m = 0, degree, j, neighboor_index;
	int succ;

	input_file =  fopen(name_of_input_file, "rb");
	if(input_file == NULL){
		exit("The file is not valid");
	}

	succ = fread(&n, sizeof(int), 1, input_file);
	if(succ != 1){
		exit("The file is empty");
	}

	/*list of pointers to node in size n representing the nodes of the graph*/
	nodes_list = (node*) malloc(sizeof(node) * (n));
	relate_matrix = (int**) malloc(sizeof(int*) * (n));

	/*Initialize Nodes list*/
	for(j= 0; j < n; j++ ){
		/*allocate returns node*/
		*nodes_list = allocate_node(j);
		nodes_list++;
	}
	nodes_list -= n;

	/*Reading File*/
	 while( !feof(input_file) ) {
		 curr_node =  *nodes_list;
		 succ = fread(&degree, sizeof(int), 1, input_file);
		 if(succ != 1){
		 		exit("Failed File Read");
		 	}

		 curr_node -> set_degree(degree);
		 neighbors = allocate_neighbors(degree);
		 curr_neighbors = (int*) calloc(sizeof(int),n);

		 for(j = 0; j < degree; j++){
			 succ = fread(&neighboor_index, sizeof(int), 1, input_file);
			 if(succ != 1) {
			 		exit("Failed File Reading");
			 	}

			 /*adding to neighbors list the corresponding neighbor*/
			 *neighbors = nodes_list[neighboor_index];
			 neighbors++;
			 curr_neighbors[neighboor_index] = 1;

		 }
		 m += degree;
		 curr_node -> set_neighbors(neighbors);
		 *relate_matrix = curr_neighbors;

		 nodes_list++;
		 relate_matrix++;

	 }
	fclose(input_file);
	relate_matrix -= n;
	nodes_list -= n;


	/*Graph building*/
	input_graph = allocate_graph(n, m, nodes_list, relate_matrix);
	return input_graph;


}
