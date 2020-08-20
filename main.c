/*
 * main.c
 *
 *  This Main FIle us ..........


 *Avital


 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./structures/graph.h"
#include "./functions/CreateGraphFromFile.c"
#include "./algorithm/algo_3.c"
#include <string.h>


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
	findCommunities(input_graph);

	end = clock();
	//printf("Prog  took: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
	return 0;
}








