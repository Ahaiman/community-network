/*
 * main.c
 *
 *  This Main FIle us ..........
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>
//#include "./structures/graph.h"
#include "./functions/CreateGraph.c"
#include <string.h>



/*SELF NOTE - do not use assert, for any error use "return" something rather then 0*/

int main(int argc, char* argv[]){

	/*Variables deceleration*/
	graph *input_graph;
	clock_t start, end;
	double epsilon = 0.00001;
	int i = 0;
//	double *initialVec, *matrixRow, *result, *tmp;

	/*Time measurement */
	srand(time(NULL));
	start = clock();
	(void)argc;

	//input_graph = createGraph(NAME OF FILE);


	end = clock();
	printf("Prog  took: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
	return 0;
}








