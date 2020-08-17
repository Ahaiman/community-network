 /* BHatMatrix.c
 *
 *  Created on: 12 áàåâ× 2020
 *      Author: Avital
 */

#include "BHatMatrix.h"
#include "graph.h"
#include "spmat.h"
#include "./functions/findEigen.c"

	double (**calcBHatMatrixEigenVector)(struct __BHatMatrix);
	void (*freeBHat)(struct __BHatMatrix);
	void (*BHatMult)(BHatMatrix, double*, double*);

BHatMatrix *createMatrixBHat (graph *G, int *degrees, double *f_vector, double matrixNorm)
{
	BHatMatrix *B;
    	B = (BHatMatrix *) malloc (sizeof(BHatMatrix));
    	if(B == NULL)
    	{
    		printf("B Allocation Failed");
    		exit(0);
    	}
	B -> G=G;
	B -> degrees=degrees;
	B -> f_vector=f_vector;
	B -> matrixNorm=matrixNorm;
	B -> calcBHatMatrixEigenVector=calcBHatMatrixEigenVector;
	B -> freeBHat=freeBHat;
	B->BHatMult=BHatMult;
	return B;
}

void BHatMult(BHatMatrix *B, double* eigenVector ,double* result)
{
	//pointers???

	double *A_g_eigenVector, *Bnorm_eigenVector, *degVec, *fbVec;
	double dotProduct;

	//calculating A_g*bk
	((B->G)->relate_matrix)->mult((B->G)->relate_matrix, eigenVector, A_g_eigenVector);

	//calculating (degreesTranspose*bk)*degrees/M:
		//calculating (degreesTranspose*bk)
		dotProduct=calcDotProduct(*(B->degrees),*eigenVector, (B->G)->size);
		//calculating dotProduct*(degrees/M):
		degVec=(double*) malloc(sizeof(double)*((B->G)->size));
		multNumVec((B->G)->size, dotProduct/(((B->G)->n)*2),*(B->degrees),*degVec);

	//calculating fVector*bk
	fbVec=(double*) malloc(sizeof(double)*((B->G)->size));
	multTwoVecs((B->G)->size, (B->f_vector),eigenVector, fbVec);

	//calculating ||N||*bk
	Bnorm_eigenVector=(double*) malloc(sizeof(double)*(B->size));
	multNumVec((B->G)->size, B->matrixNorm, *eigenVector, *Bnorm_eigenVector);

	findEigen_MultResult((B->G)->size, A_g_eigenVector, degVec, fbVec, Bnorm_eigenVector, result);
	free(degVec);
	free(fbVec);
}

void freeBHat(struct __BHatMatrix *B)
{
	free_graph(B - > G);
	free(B - > degrees);
	free(B - >  f_vector);
}
