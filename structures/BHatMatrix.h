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

	//spmat *F;
	//int **K_Matrix;
	/*
	 calculating a b-hat-matrix eigen vector (b_k will be calculated inside this method) 
	*/
	double (**calcBHatMatrixEigenVector)(BHatMatrix *B);
	BHatMatrix (**createMatrixBHat) (spmat *A_g, double *degrees, double *F, double matrixNorm);
	void (*free)(struct __BHatMatrix *B);


} BHatMatrix;

#endif /* STRUCTURES_BHATMATRIX_H_ */
