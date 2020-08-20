 /* BHatMatrix.c
 *
 *  Created on: 12 áàåâ× 2020
 *      Author: Avital
 */

#include "BHatMatrix.h"
#include "graph.h"
#include "spmat.h"
#include "./functions/findEigen.c" /*necessary for calcDorProduct in BHatMult*/

void freeBHat(struct __BHatMatrix);
void BHatMult(BHatMatrix, double*, double*);
double* calculate_fVector(graph*);
int  calc_MatrixNorm(graph*);
void multNumVec(int, double, double*, double*);
void multTwoVecs(int, double*, double*, double*);
void MultBMatAndVector(int, double*, double*, double*, double*);
void findEigen_MultResult(int, double*, double*, double*, double*, double*);
void SubtractTwoVectors(int, double*, double*);
void AddTwoVectors(int, double*, double*);

BHatMatrix *createMatrixBHat (graph *G)
{
	BHatMatrix *B;
    	B = (BHatMatrix *) malloc (sizeof(BHatMatrix));
    	if(B == 0)
    	{
    		printf("B Allocation Failed");
    		exit(0);
    	}

	B -> G=G;
	B -> f_vector=calculate_fVector(G);
	B -> matrixNorm=calc_MatrixNorm(G);
	B -> freeBHat=freeBHat;
	B -> BHatMult=BHatMult;
	return B;
}
void multNumVec(int size, double num, double *vec, double *res)
{
	int i;
	for(i=0;i<size;i++)
	{
		*res=(*vec)*num;
		res++;
		vec++;
	}
}

void multTwoVecs(int size, double *fVector, double *eigenVector, double *res)
{
	int i;
	for(i=0;i<size;i++)
	{
		*res=(*fVector)*(*eigenVector);
		res++;
		fVector++;
		eigenVector++;
	}
}
void MultBMatAndVector(int size, double *A_g_eigenVector, double *degVec, double *fbVec, double *result)
{
	double *sub1;
	*sub1=(double*) malloc(sizeof(double)*(size));
	SubtractTwoVectors(size, A_g_eigenVector, degVec, sub1);
	SubtractTwoVectors(size, sub1, fbVec, result);
	free(sub1);
}

void findEigen_MultResult(int size, double *A_g_eigenVector, double *degVec, double *fbVec, double *Bnorm_eigenVector, double *result)
{
	double* sub=(double*) malloc(sizeof(double)*(size));
	MultBMatAndVector(size, A_g_eigenVector, degVec, fbVec, sub);
	AddTwoVectors(size, sub, Bnorm_eigenVector, result);
	free(sub);
}
void SubtractTwoVectors(int size, double *vec1, double *vec2, double *result)
{
	int i;
	for (i=0;i<size;i++)
	{
		*result=*vec1-*vec2;
		result++;
		vec1++;
		vec2++;
	}
}
void AddTwoVectors(int size, double *vec1, double *vec2, double *result)
{
	int i;
	for (i=0;i<size;i++)
	{
		*result=*vec1+*vec2;
		result++;
		vec1++;
		vec2++;
	}
}
//we need to provide M!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//calculates a local M
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
//the i number in the fVector is the sum of the i row in the B[g] matrix (B[g]=Ag_ij-k_i*k_j/M)
double* calculate_fVector(graph *G)
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
			//we need to provide M!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			sub=((G->graph_nodes)[i]->degree)*((G->graph_nodes)[j]->degree)/M;
			*fVec+=((G->relate_matrix)[i][j]-sub);
		}
		fVec++;
	}
	return fVec;
}
/*returns the sum of the largest column*/
int calc_MatrixNorm(graph *G)
{
	int sum, max=0, i, j;
	for(j=0;j<G->n;j++)
	{
		sum=0;
		for(i=0;i<G->n;i++)
		{
			sum+=(G->relate_matrix)[i][j];
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

	//calculating (degrees^T*bk)*degrees/M:
		//calculating (degrees^T*bk)
		dotProduct=calcDotProduct((B->G)->degrees,eigenVector, (B->G)->n);
		//calculating dotProduct*(degrees/M):
		//here I used a local M and not the entire graph's M!!!!!!!!!!!!!!!!!!!!!!!!
		degVec=(double*) malloc(sizeof(double)*((B->G)->n));
		//here I used a local M and not the entire graph's M!!!!!!!!!!!!!!!!!!!!!!!!
		multNumVec((B->G)->n, dotProduct/(((B->G)->n)*2), (B->G)->degrees, degVec);

	//calculating fVector*bk
	fbVec=(double*) malloc(sizeof(double)*((B->G)->n));
	multTwoVecs((B->G)->n, B->f_vector, eigenVector, fbVec);

	//calculating ||N||*bk
	Bnorm_eigenVector=(double*) malloc(sizeof(double)*((B->G)->n));
	multNumVec((B->G)->n, B->matrixNorm, eigenVector, Bnorm_eigenVector);

	findEigen_MultResult((B->G)->n, A_g_eigenVector, degVec, fbVec, Bnorm_eigenVector, result);
	free(degVec);
	free(fbVec);
	free(Bnorm_eigenVector);
}

void freeBHat(struct __BHatMatrix *B)
{
	/*other inputs?????????????????????????*/
	free_graph(B->G);
	/*free(B->degrees);*/
	free(B->f_vector);
}
