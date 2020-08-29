/*
 * its shifted in the calculation
 */

#ifndef STRUCTURES_BHATMATRIX_H_
#define STRUCTURES_BHATMATRIX_H_

#include "./graph.h"

typedef struct _BHatMatrix
{
	graph *G;
	double constM;
	int originalSize;
	double matrixNorm;

	void (*freeBHat)(struct _BHatMatrix *B);
	void (*multBHat)(struct _BHatMatrix *B, double* vector ,double *result, int doShift);

} BHatMatrix;

BHatMatrix* createMatrixBHat (graph *G);

#endif /* STRUCTURES_BHATMATRIX_H_ */
