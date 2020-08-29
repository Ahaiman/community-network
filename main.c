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
	FILE	*input_file;

	/*Time measurement */
	srand(time(NULL));
	start = clock();
	(void)argc;

	/*Create Graph */
	input_file =  fopen(argv[1], 'rb');
	if(input_file == NULL){
		printf("The file is not valid");
		exit(EXIT_FAILURE);
	}

	input_graph = createGraph(input_file);

	/*Send to Algorithm 3 */
	findCommunities(input_graph, argv[2]);

	end = clock();
	printf("Prog  took: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
	return 0;
}








