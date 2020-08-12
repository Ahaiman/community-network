/*
 * BHatMatrix.h
 *
 *  Created on: 12 баев„ 2020
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
	double *degrees;

	int size;

	spmat *A;

	spmat *F;

//	int **K_Matrix;

	double matrixNorm;

	double (**createMatrixBHat)(double *degrees, spmat *A, spmat *F, double *b_k);
	void (*free)(struct __BHatMatrix *B);


};

#endif /* STRUCTURES_BHATMATRIX_H_ */
