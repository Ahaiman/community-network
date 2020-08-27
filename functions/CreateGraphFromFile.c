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
#include "functions.h"


graph *createGraph(char *name_of_input_file){

	/*Variables deceleration*/
	FILE	*input_file;
	graph *input_graph;
	graph_node *curr_node;
	int *nodes_list;
	int *curr_neighbors, *matrix_row, *degrees;
	spmat *relate_matrix;
	int n, m = 0, degree, j, neighboor_index, i = 0;
	int succ;

	/*File Reading into variable, and asserting the process was successful.
	 * if not - exiting the program.*/
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
	nodes_list = (int *) malloc(sizeof(int) * (n));

	/*Assert allocation*/
	if(nodes_list == NULL){
			exit("Allocation of nodes list failed");
	}

	/*Initialize Nodes list*/
	for(j = 0; j < n; j++ ){
		/*Allocate returns node*/
		*nodes_list = j;
		nodes_list++;
	}
	nodes_list -= n;

	/*Allocating space to sparse matrix */
	relate_matrix = spmat_allocate_list(n);

	degrees = (int *) malloc(sizeof(int) * (n));
	if(degrees == NULL){
		exit("Allocation of degrees vector failed");
	}

	/*Reading File:
	 *      Reading the input matrix (one row at a time).
	 *      For each row, adding it to the sparse matrix
	 */

	 while( !feof(input_file) ) {

		 /*Read file row : k1 and the indices */
		 succ = fread(&degree, sizeof(int), 1, input_file);
		 if(succ != 1){
		 	exit("Failed degree reading");
		 }
		 *degrees = degree;
		 degrees++;

		 /*Read the neighbors indices into row*/
		 matrix_row =  (int*) malloc(sizeof(int)*(degree));
		 if(matrix_row == NULL){
		 		exit("Allocation failed");
		 }

		 succ =  fread(matrix_row, sizeof(int), degree, input_file);
		 if(succ != degree){
			exit("Failed file read");
		}

		 relate_matrix -> add_row(relate_matrix, matrix_row, degree, i);
		 free(matrix_row);
		 i++;


	 }


	fclose(input_file);


	/*Graph building*/
	input_graph = allocate_graph(n, nodes_list, relate_matrix);
	input_graph -> degrees = degrees;

	return input_graph;

}
