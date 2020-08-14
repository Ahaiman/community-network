/*
 * algo_2.c
 *
 *  Created on: 11 баев„ 2020
 *      Author: Avital
 */

#include "./structures/BHatMatrix.h"
#include "./structures/stack.h"

stack *divisionGraphToTwo(graph *group){

	BHatMatrix *B_g_shifted;
	stack *division;
	double eigenValue;
	double *eigenVector;
	int *s;

	B_g_shifted = createMatrixBHat(group);

	/*Compute leading eigenpair u1 and b1 of the modularity matrix b B[g] */
	eigenVector = (double *) malloc (sizeof(double) * (B_g_shifted -> size));
	eigenValue = findEigen(B_g_shifted, eigenVector);

	//if (b1 <= 0): The network is indivisible
	if(eigenValue <= 0){
		printf();
		return NULL;
	}

	//compute s
	 s = computeS(eigenVector, B_g_shifted -> size);


	//TODO OR: implement Q
	 //if (sT b B[g]s <= 0): The network is indivisible
	 if(computeQ(s, B_g_shifted) <= 0){
		 printf();
		 return NULL;
	 }

	// return a division into two groups according to s
	 //returns 1 , cnt = 2,  stack wich holds 2 graphs : the division
	 initialize(division);

	 division = getDivisionByS(s, group);

	 return division;


}
