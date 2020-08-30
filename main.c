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
//#include "./test/cluster.h"


int main(int argc, char* argv[]){

	/*Variables deceleration*/
	graph *input_graph;
	clock_t start, end;
	FILE	*input_file, *output_file;

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
	input_graph = createGraph(input_file);

	output_file =  fopen(argv[2], "wb");
//	if(output_file == NULL){
//		printf("output file failed");
//		exit(EXIT_FAILURE);
//	}
	/*Send to Algorithm 3 */
	findCommunities(input_graph, output_file);

	end = clock();
	printf("Prog  took: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
	return 0;
}








