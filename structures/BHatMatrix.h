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
#include "graph.h"
#ifndef STRUCTURES_BHATMATRIX_H_
#define STRUCTURES_BHATMATRIX_H_


typedef struct _BHatMatrix{

	graph *G;
	double *f_vector;
	int matrixNorm;

	void (*freeBHat)(struct __BHatMatrix *B);
	void (*BHatMult)(BHatMatrix *B, double* vector ,double *result);

} BHatMatrix;

BHatMatrix* createMatrixBHat (spmat *A_g, int *degrees, double *f_vector, double matrixNorm, int size, int *nodesIndices);

#endif /* STRUCTURES_BHATMATRIX_H_ */
