/*
 * algo_3.c
 *
 *  Created on: 11 баев„ 2020
 *      Author: Avital
 */

#include "./structures/BHatMatrix.h"
#include "./structures/stack.h"
#include "./structures/linkedList.h"
#include "./structures/graph.h"
#include "./structures/graph_node.h"
#include "./function/doDivisionByS.c"


void findCommunities(graph *G){
	stack *P, *O, *divisionToTwo;
	graph *group, *group1, *group2;
	int *s;
	double dQ;


	initialize(O);
	initialize(P);
	initialize(divisionToTwo);
	s = (int *) malloc (sizeof(int) * (G -> n));

	//	1.Start with a trivial division into one group: the all nodes in the graph
	P -> push(G, P);

	while(!empty(P)){
		group = P -> pop(P);

		/* 1) Divide g into g1; g2 with Algorithm 2 */
		dQ  = algorithm2(group, s);


		/*2) Together :
		 * Implenet optimiztiom - */
		 algorithm4(s, dQ);

		 /*Creating the division*/
		 doDivisionByS(group, s, divisionToTwo);

		 group1 = divisionToTwo -> pop(divisionToTwo);
		 group2 = divisionToTwo -> pop(divisionToTwo);

		/* 3) if either g1 or g2 is of size 0: Add g to O*/
		if(group1  == NULL || group2 == NULL ){
			O.push(group);
		}

		/*4) Add to O: any group (g1 and/or g2) of size 1*/
		if(group1 -> n == 1){
			O.push(group1);
		}
		else{
			P.push(group1);
		}

		if(group2 -> n == 1){
			O.push(group2);
		}
		else{
			P.push(group2);
		}
	}

/*O consists of several graphs, we need to make it as the input file requires*/


	/*writing the output file */
//
//	fclose(inputMatrix);
//	/*writing the eigen vector to the file*/
//	outputFile =  fopen(argv[place + 2], "wb");
//	assert(outputFile != NULL);
//
//	place = 1;
//	fwrite(&place, sizeof(int), 1, outputFile);
//	fwrite(&matrixSize, sizeof(int), 1, outputFile);
//	n = fwrite(initialVec, sizeof(double), matrixSize, outputFile);
//	assert(n == matrixSize);
//
//	fclose(outputFile);
//	free(result);
//	free(initialVec);
//	sparseMatrix -> free(sparseMatrix);
//	end = clock();
//	printf("Prog  took: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);


}
