/*
 * main.c
 *
 *  AA This Main FIle us ..........
 
 
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "./structures/graph.h"
#include "./functions/functions.h"
#include "./algorithm/algorithm.h"


int main(int argc, char* argv[]){

	/*Variables deceleration*/
	graph *input_graph;
	clock_t start, end;
	FILE	*input_file;
	spmat *matrix;
	int *degrees;
	char *output_file;

	/*Time measurement */
	srand(time(NULL));
	start = clock();
	(void)argc;


	/*File Reading into variable, and asserting the process was successful.
	 * if not - exiting the program.*/
	input_file =  fopen(argv[1], "rb");
	if(input_file == NULL){
		printf("The file is not valid2");
		exit(EXIT_FAILURE);
	}

	/*Create Graph */
	matrix = (spmat *)malloc(sizeof(spmat));
	input_graph = (graph *)malloc(sizeof(graph));

	degrees = createGraph(input_file,input_graph, matrix);

	output_file = argv[2];

	/*Send to Algorithm 3 */
	findCommunities(input_graph, matrix, degrees, output_file);

	end = clock();
	printf("Prog  took: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
	return 0;
}
