/*
 * algo_2.c
 *
 *  Created on: 11 баев„ 2020
 *      Author: Avital
 */

#include "./structures/BHatMatrix.h"
#include "./structures/stack.h"

stack *divisionGraphToTwo(graph *group, stack *division, int *s){

	BHatMatrix *B_g_shifted;
	/*size : 2 */

	double eigenValue, Dq;
	double *eigenVector;

	B_g_shifted = createMatrixBHat(group);

	/*Compute leading eigenpair u1 and b1 of the modularity matrix b B[g] */
	eigenVector = (double *) malloc (sizeof(double) * (B_g_shifted -> size));
	eigenValue = findEigen(B_g_shifted, eigenVector);

	//if (b1 <= 0): The network is indivisible
	if(eigenValue <= 0){
		printf("not possible");
		return NULL;
	}

	//compute s
	 s = computeS(eigenVector, B_g_shifted -> size);

	 Dq = computeDQ(s, B_g_shifted);
	//TODO OR: implement DQ in function "compueDQ"
	 //if (s^T b B[g]s <= 0): The network is indivisible
	 if( Dq <= 0){
		 printf("not possible");
		 return NULL;
	 }

	// return a division into two groups according to s
	 //returns 1 , cnt = 2,  stack wich holds 2 graphs : the division


	 /*Avital */
//	 division = getDivisionByS(s, group);
	 return Dq;


}
