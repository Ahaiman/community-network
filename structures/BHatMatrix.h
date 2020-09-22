/*
 * its shifted in the calculation
 */

#ifndef STRUCTURES_BHATMATRIX_H_
#define STRUCTURES_BHATMATRIX_H_

#include "./graph.h"

typedef struct _BHatMatrix
{
//	graph *G;

	/* Matrix that represent the relationship between nodes in the graph */
	graph *originalGraph;
	//int *graph_nodes;
	spmat    *relate_matrix;
	int *degrees;

	double constM;
	int originalSize; // originalGraph - > n
	double matrixNorm;
	double *f_vector;

	void (*freeBHat)(struct _BHatMatrix *B);
	void (*multBHat)(struct _BHatMatrix *B,graph *group, double* vector ,double *result, int doShift);

} BHatMatrix;

BHatMatrix* createMatrixBHat (graph *G, spmat *relate_matrix, int *degrees);
void initializeFVector(BHatMatrix *B);
int sumRowsA(spmat *relate_matrix, graph *group , int m);
double sumRowsD(graph *, BHatMatrix *, int);
double sumRowB (BHatMatrix *, int);
void multNumVec(graph * ,double, int*, double*);
void substractTwoVecs(graph *, double*, double*, double*);
double  calcMatrixNorm(BHatMatrix *);
double calcM(BHatMatrix *);



#endif /* STRUCTURES_BHATMATRIX_H_ */
