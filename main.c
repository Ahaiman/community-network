/*
 * main.c
 *
 *  This Main FIle us ..........
 
 
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

	/*Time measurement */
	srand(time(NULL));
	start = clock();
	(void)argc;

	/*Create Graph */
	input_graph = createGraph(argv[1]);

	/*Send to Algorithm 3 */
	findCommunities(input_graph, argv[2]);

	end = clock();
	printf("Prog  took: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
	return 0;
}








