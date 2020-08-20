 /* BHatMatrix.c
 *
 *  Created on: 12 áàåâ× 2020
 *      Author: Avital
 */

#include "BHatMatrix.h"
#include "graph.h"
#include "spmat.h"
#include "./functions/findEigen.c"

	void (freeBHat)(struct __BHatMatrix);
	void (BHatMult)(BHatMatrix, double*, double*);
	double* (calculate_fVector)(graph*);
	double (calc_MatrixNorm)(graph*);

	/*OR: needs to receive only G.
	 * build function to calculate other based on the G
	 */
BHatMatrix *createMatrixBHat (graph *G)
{
	BHatMatrix *B;
    	B = (BHatMatrix *) malloc (sizeof(BHatMatrix));
    	if(B == NULL)
    	{
    		printf("B Allocation Failed");
    		exit(0);
    	}
	B -> G=G;

	B -> degrees= G-> degrees;
	B -> f_vector=calculate_fVector(G);
	B -> matrixNorm=calc_MatrixNorm(G);
	B -> freeBHat=freeBHat;
	B->BHatMult=BHatMult;
	return B;
}
/*we need to provid M!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
int calcM(graph *G)
{
	int i, M=0;
	for(i=0;i<G->n;i++)
	{
		M+=*(G->degrees);
		(G->degrees)++;
	}
	return M;
}
double* (calculate_fVector)(graph *G)
{
	int size, i, j;
	double *fVec;
	double sub;
	fVec=(double*)malloc(sizeof(double)*size);
	size=G->n;
	for(j=0;j<size;j++)
	{
		*fVec=0;
		for(i=0;i<size;i++)
		{
			sub=((G->graph_nodes)[i]->degree)*((G->graph_nodes)[j]->degree)/M;
			*fVec+=((G->relate_matrix)[i,j]-sub);
		}
		fVec++;
	}
	return fVec;
}
/*returns the sum of the largest column*/
int (calc_MatrixNorm)(graph *G)
{
	int sum, max=0, i, j;
	for(j=0;j<G->n;j++)
	{
		sum=0;
		for(i=0;i<G->n;i++)
		{
			sum+=(G->relate_matrix)[i,j];
		}
		if (sum>max)
			max=sum;
	}
	return max;
}
void BHatMult(BHatMatrix *B, double *eigenVector ,double *result)
{
	double *A_g_eigenVector, *Bnorm_eigenVector, *degVec, *fbVec;
	double dotProduct;

	//calculating A_g*bk
	((B->G)->relate_matrix)->spmat_mult((B->G)->relate_matrix, eigenVector, A_g_eigenVector);

	//calculating (degreesTranspose*bk)*degrees/M:
		//calculating (degreesTranspose*bk)
		dotProduct=calcDotProduct(B->degrees,eigenVector, (B->G)->n);
		//calculating dotProduct*(degrees/M):
		degVec=(double*) malloc(sizeof(double)*((B->G)->n));
		multNumVec((B->G)->n, dotProduct/(((B->G)->n)*2), B->degrees, degVec);

	//calculating fVector*bk
	fbVec=(double*) malloc(sizeof(double)*((B->G)->n));
	multTwoVecs((B->G)->n, B->f_vector, eigenVector, fbVec);

	//calculating ||N||*bk
	Bnorm_eigenVector=(double*) malloc(sizeof(double)*((B->G)->n));
	multNumVec((B->G)->n, B->matrixNorm, eigenVector, Bnorm_eigenVector);

	findEigen_MultResult((B->G)->n, A_g_eigenVector, degVec, fbVec, Bnorm_eigenVector, result);
	free(degVec);
	free(fbVec);
}

void freeBHat(struct __BHatMatrix *B)
{
	free_graph(B->G);
	free(B->degrees);
	free(B->f_vector);
}
