/*
 * main.c
 *
 * The main program is based mainly on algorithm 3 (the numbers of the algorithms are according to the instructions file),
 * which calls the other relevant algorithms.
 *
 * This function creates the main original graph (using "createGraph" function),
 * and initializes the main structures needed for future use in the function "findCommunities" in algorithm 3.
 *
 * The errors that may occur during the entire program, are considered to be "thrown",
 * but actually an error message is printed to the screen, and the running of the program ends (using "exit" function).
 * As written in the documentation of the "errorHandler.h" file, the memory allocated during the program,
 * is not freed when the exit happens.
 *
 * The whole program flow begins with "findCommunities" function (in algorithm 3).
 * After a division is found and written on the output file, the main program prints the running time of the program.
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "graph.h"
#include "algorithm3.h"
#include "errorHandler.h"

int main(int argc, char* argv[]){

	/*Variables deceleration*/
	graph*		input_graph;
	clock_t 	start, end;
	FILE*		input_file;
	spmat*		adjacency_matrix;
	int*		graph_degrees;
	char*		output_file;

	/*Time measurement */
	srand(time(NULL));
	start = clock();
	(void)argc;

	 /*Reading the file into a variable*/
	input_file =  fopen(argv[1], "rb");
	if(input_file == NULL) returnErrorByType(0);

	/*Creating an instance of the original graph from the input file*/
	input_graph = (graph *)malloc(sizeof(graph));
	if(input_graph == NULL) returnErrorByType(3);

	/*Creating an instance of the adjacency matrix of the graph*/
	adjacency_matrix = (spmat *)malloc(sizeof(spmat));
	if(adjacency_matrix == NULL) returnErrorByType(1);

	/*Setting the graph, and reading the degrees into the corresponding vector*/
	graph_degrees = createGraph(input_file,input_graph, adjacency_matrix);

	output_file = argv[2];

	/*Performing algorithm 3 on the input graph */
	findCommunities(input_graph, adjacency_matrix, graph_degrees, output_file);

	end = clock();
	printf("The program took: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

	/*If the program ends successfully, the main function returns 0*/
	return 0;
}
