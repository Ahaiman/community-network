/*
 * algo_2.c
 *
 *  Created on: 11 баев„ 2020
 *      Author: Avital
 */

#include "./structures/BHatMatrix.h"

void divisionGraphToTwo(graph *group){

	BHatMatrix *B_g_shifted;
	List division;
	double eigenValue;
	double *eigenVector;
	int *s;

	B_g_shifted = createMatrixBHat();
	/*(1) degrees - needs to be built by nodes list in the graph
	 * (2) F
	 */

	/*Calculate B matrix */
	/* B -> A === group -> related_matrix */
	/* B -> degrees === (1)
	/* B -> F === (2)
	/* Matrix norm

	/*Compute leading eigenpair u1 and 1 of the modularity matrix b B[g] */
	/*TODO: findEigen needs to return both vector and value */

	/*B-g need to be shiftes*/


	/*Avital - REMEMBER THAT THE b_g is not matrix is structure*/
	eigenValue = findEigen(B_g_shifted, eigenVector, B_g_shifted -> size);
//	eigenVector = return_value[0];
//	eigenValue = return_value [1];


	//if (b1 <= 0): The network is indivisible
	if(eigenValue <= 0){
		printf();
		return NULL;
	}

	//compute s
	 s = computeS(eigenValue, B_g -> size);


	//if (sT b B[g]s <= 0): The network is indivisible
	 if(computeQ(s, B_g) <= 0){
		 printf();
		 return NULL;
	 }

	// return a division into two groups according to s
	 division = getDivisionByS(s);
	 return division;


}
