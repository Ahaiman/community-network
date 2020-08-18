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
#include "../structures/graph_node.h"
#include "../structures/spmat.h"

graph *createGraph(char *name_of_input_file){

	/*Variables deceleration*/
	FILE	*input_file;
	graph *input_graph;
	graph_node *curr_node;
	graph_node **nodes_list, **neighbors;
	int *curr_neighbors, *matrix_row, *degrees;
	spmat *relate_matrix;
	int n, m = 0, degree, j, neighboor_index, i = 0;
	int succ;

	/*File Reading into variable, and asserting the process was successful.
	 * if not - exiting the program.
	 */
	input_file =  fopen(name_of_input_file, "rb");
	if(input_file == NULL){
		exit("The file is not valid");
	}

	/*Reading number of nodes in the graph*/
	succ = fread(&n, sizeof(int), 1, input_file);
	if(succ != 1){
		exit("The file is empty");
	}

	/*Initializing list size n, of pointers to the nodes of the graph*/
	nodes_list = (graph_node*) malloc(sizeof(graph_node) * (n));

	/*Initialize Nodes list*/
	for(j = 0; j < n; j++ ){
		/*allocate returns node*/
		*nodes_list = allocate_node(j);
		nodes_list++;
	}
	nodes_list -= n;

	/*Allocating space to sparse matrix represeinting .... */
	relate_matrix = spmat_allocate_list(n);

	degrees = (int *) malloc(sizeof(int) * (n));

	/*Reading File
	 * Reading the input matrix (one row at a time).
	 * For each row, adding it to the sparse matrix
	 */

	 while( !feof(input_file) ) {
		 curr_node =  *nodes_list;
		 /*Read file row : k1 and the indices */
		 succ = fread(&degree, sizeof(int), 1, input_file);
		 if(succ != 1){
		 		exit("Failed File Read");
		 	}

		 curr_node -> set_degree(degree);
		 *degrees = degree;
		 degree++;

		 /*ASK TAL : how to hold the neighbors?
		  * as list of nodes? or as list of int?
				  */
		 neighbors = allocate_neighbors(degree);


		 /*read the neighbors into row*/
		 matrix_row =  (int*) malloc(sizeof(int)*(degree));
		 succ =  fread(matrix_row, sizeof(int), degree, input_file);

		 /*assert*/

		 /*ASK TAL : how to hold the sparse matrix as the relativ matrix?
		  * CHANGE IN SPMAT.C the function add row
		  */
		 relate_matrix -> add_row(relate_matrix, matrix_row, degree, i);

		// curr_neighbors = (int*) calloc(sizeof(int),degree);



		for(j = 0; j < degree; j++){
			 /*adding to neighbors list the corresponding neighbor*/
			*neighbors = nodes_list[*matrix_row];
			neighbors++;
			matrix_row++;
		}

		 m += degree /*updating number of edges*/
				 /* m/2 ????*/
		 curr_node -> set_neighbors(neighbors);

		 nodes_list++;
		 free(matrix_row);
		 i++;

	 }

	 m = m/2;

	fclose(input_file);
	nodes_list -= n;


	/*Graph building*/
	input_graph = allocate_graph(n, m, nodes_list, relate_matrix);
	return input_graph;


}
