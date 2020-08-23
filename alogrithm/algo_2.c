/*
 * algo_2.c
 *
 *  Created on: 11 ����� 2020
 *      Author: Avital
 */

#include "./structures/BHatMatrix.h"
#include "./structures/stack.h"
#include "./functions/functions/h"

stack *divisionGraphToTwo(graph *group, stack *division, int *s){

	BHatMatrix *B_g_shifted;
	/*size : 2 */

	double eigenValue, dQ;
	double *eigenVector;

	B_g_shifted = createMatrixBHat(group);

	/*Compute leading eigenpair u1 and b1 of the modularity matrix b B[g] */
	eigenVector = (double *) malloc (sizeof(double) * (group -> n));
	eigenValue = findEigen(B_g_shifted, eigenVector);

	//if (b1 <= 0): The network is indivisible
	if(eigenValue <= 0){
		printf("not possible");
		return NULL;
	}

	//compute s
	 s = computeS(eigenVector,group -> n);

	 dQ = computeDQ(s, B_g_shifted);

	 //if (s^T b B[g]s <= 0): The network is indivisible
	 if( dQ <= 0){
		 printf("not possible");
		 return NULL;
	 }

	 return dQ;


}
