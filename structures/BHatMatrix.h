/*
 * its shifted in the calculation
 */

#ifndef STRUCTURES_BHATMATRIX_H_
#define STRUCTURES_BHATMATRIX_H_


typedef struct _BHatMatrix
{
	graph *G;
	double constM;
	int originalSize;
	double matrixNorm;

	void (*freeBHat)(struct __BHatMatrix *B);
	void (*multBHat)(struct __BHatMatrix *B, double* vector ,double *result);

} BHatMatrix;

BHatMatrix* createMatrixBHat (graph *G);

#endif /* STRUCTURES_BHATMATRIX_H_ */
