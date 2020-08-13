 /* BHatMatrix.c
 *
 *  Created on: 12 áàåâ× 2020
 *      Author: Avital
 */

#include "BHatMatrix.h"
#include "spmat.h"

BHatMatrix *createMatrixBHat (spmat *A_g, double *degrees, double *f_vector, double matrixNorm, int size, int *nodesIndices)
{
	BHatMatrix *B;
    	B = (BHatMatrix *) malloc (sizeof(BHatMatrix));
    	if(B == NULL)
    	{
    		printf("B Allocation Failed");
    		exit(0);
    	}
	B -> A_g=A_g;
	B -> degrees=degrees;
	B -> f_vector=f_vector;
	B -> matrixNorm=matrixNorm;
	B -> size=size;
	B -> nodesIndices=nodesIndices;
	B -> calcBHatMatrixEigenVector=calcBHatMatrixEigenVector;
	B -> freeBHat=freeBHat;
	return B;
}


//double* createMatrixBHat(double *degrees, spmat *A, double *f, double *b_k){
	/*implenet*/
//}


void *freeBHat(struct __BHatMatrix *B){
	spmat_free(B - > A_g);
	free(B - > degrees);
	free(B - >  f_vector);
	free(B -> nodesIndices);
}
