/*
 * BHatMatrix.h
 *
 *  Created on: 12 áàåâ× 2020
 *      Author: Avital
 */

/*
 * its shifted in the calculation
 */
#include "spmat.h"

#ifndef STRUCTURES_BHATMATRIX_H_
#define STRUCTURES_BHATMATRIX_H_


typedef struct _BHatMatrix{
	/*Keeping the degrees of the current nodes in the group
	 * in degrees vector
	 */
	spmat *A_g;
	double *degrees;
	double *f_vector;
	double matrixNorm;
	int size;
	int *nodesIndices;
	/*
	 calculating a b-hat-matrix eigen vector (b_k will be calculated inside this method) 
	*/
	double (**calcBHatMatrixEigenVector)(__BHatMatrix *B);
	void (*free)(struct __BHatMatrix *B);
} BHatMatrix;

BHatMatrix* createMatrixBHat (spmat *A_g, double *degrees, double *f_vector, double matrixNorm, int size, int *nodesIndices);

#endif /* STRUCTURES_BHATMATRIX_H_ */
