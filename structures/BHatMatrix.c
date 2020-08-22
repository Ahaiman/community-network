#include "BHatMatrix.h"
#include "graph.h"
#include "spmat.h"
#include "./functions/functions.h" /*necessary for calcDorProduct in multBHat*/

/*
 * --------Functions Definition---------
 */

//no declaration for calcM!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
BHatMatrix* createMatrixBHat (graph*);
void multBHat(BHatMatrix*, double*, double*);
void subtractFirstThreeVecs(int, double*, double*, double*, double*);
void findEigenMultResult(int, double*, double*, double*, double*, double*);
void calcFirstThreeVecs(BHatMatrix*, double* ,double*, double*, double*);
void multNumVec(int, double, double*, double*);
void multTwoVecs(int, double*, double*, double*);
void subtractTwoVecs(int, double*, double*);
void addTwoVecs(int, double*, double*);
double* calcfVec(graph*);
int  calcMatrixNorm(graph*);
void freeBHat(BHatMatrix*);

/*
 * --------Implementation---------
 */

/*
 * Bhat matrix initialization.
 */
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
	B -> f_vector=calcfVec(G);
	B -> matrixNorm=calcMatrixNorm(G);
	B -> freeBHat=freeBHat;
	B -> multBHat=multBHat;
	return B;
}

/*
 * Multiplies a shifted Bhat matrix by a vector.
 * The output is in "result" vector.
 */
void multBHat(BHatMatrix *B, double *eigenVector ,double *result)
{
	double *Ag_eigenVector, *Bnorm_eigenVector, *degVec, *fbVec;

	//calculating the first 3 vectors needed for Bhat multiplication
	Ag_eigenVector=(double*) malloc(sizeof(double)*((B->G)->n));
	degVec=(double*) malloc(sizeof(double)*((B->G)->n));
	fbVec=(double*) malloc(sizeof(double)*((B->G)->n));
	calcFirstThreeVecs(B, eigenVector, Ag_eigenVector, degVec, fbVec);

	//calculating ||N||*bk - the last vector needed for Bhat multiplication
	Bnorm_eigenVector=(double*) malloc(sizeof(double)*((B->G)->n));
	multNumVec((B->G)->n, B->matrixNorm, eigenVector, Bnorm_eigenVector);

	//calculating the final product of the multiplication using all the vectors above
	findEigenMultResult((B->G)->n, Ag_eigenVector, degVec, fbVec, Bnorm_eigenVector, result);

	free(Ag_eigenVector);
	free(degVec);
	free(fbVec);
	free(Bnorm_eigenVector);
}

/*
 * Multiplies Bhat matrix by a vector.
 * The output is in "result" vector.
 */
void subtractFirstThreeVecs(int size, double *A_g_eigenVector, double *degVec, double *fbVec, double *result)
{
	double *sub1;
	*sub1=(double*) malloc(sizeof(double)*(size));
	subtractTwoVecs(size, A_g_eigenVector, degVec, sub1);
	subtractTwoVecs(size, sub1, fbVec, result);
	free(sub1);
}

/*
 * Calculates the final vector of Bhat-shifted matrix multiplication by a vector.
 * The output is in "result" vector.
 */
void findEigenMultResult(int size, double *A_g_eigenVector, double *degVec, double *fbVec, double *Bnorm_eigenVector, double *result)
{
	double* sub=(double*) malloc(sizeof(double)*(size));
	subtractFirstThreeVecs(size, A_g_eigenVector, degVec, fbVec, sub);
	addTwoVecs(size, sub, Bnorm_eigenVector, result);
	free(sub);
}

/*
 * Calculates the first 3 vectors needed for Bhat matrix multiplication by a vector.
 * The output is in "result" vector.
 */
void calcFirstThreeVecs(BHatMatrix *B, double *eigenVector ,double *Ag_eigenVector, double *degVec, double *fbVec)
{
	double dotProduct;

	//calculating A_g*bk
	((B->G)->relate_matrix)->spmat_mult((B->G)->relate_matrix, eigenVector, Ag_eigenVector);

	//calculating (degrees^T*bk)*degrees/M:
		//calculating (degrees^T*bk)
		dotProduct=calcDotProduct((B->G)->degrees,eigenVector, (B->G)->n);
		//calculating dotProduct*(degrees/M):
		//here I used a local M and not the entire graph's M!!!!!!!!!!!!!!!!!!!!!!!!
		multNumVec((B->G)->n, dotProduct/(((B->G)->n)*2), (B->G)->degrees, degVec);

	//calculating fVector*bk
	multTwoVecs((B->G)->n, B->f_vector, eigenVector, fbVec);
}

/*
 * Multiplies a vector by a number.
 * The output is in "result" vector.
 */
void multNumVec(int size, double num, double *vec, double *result)
{
	int i;
	for(i=0;i<size;i++)
	{
		*result=(*vec)*num;
		result++;
		vec++;
	}
}

/*
 * Multiplies two column vectors according to this scheme: result[i]=fVec[i]*eigenVector[i].
 * The output is in "result" vector.
 */
void multTwoVecs(int size, double *fVector, double *eigenVector, double *result)
{
	int i;
	for(i=0;i<size;i++)
	{
		*result=(*fVector)*(*eigenVector);
		result++;
		fVector++;
		eigenVector++;
	}
}

/*
 * Subtracts two column vectors according to this scheme: result[i]=vec1[i]-vec2[i].
 * The output is in "result" vector.
 */
void subtractTwoVecs(int size, double *vec1, double *vec2, double *result)
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

/*
 * Sums two column vectors according to this scheme: result[i]=vec1[i]+vec2[i].
 * The output is in "result" vector.
 */
void addTwoVecs(int size, double *vec1, double *vec2, double *result)
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
/*
 * calculates a local M = the sum of the degrees of the nodes in G.
 */
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

/*
 * Calculates a "f" vector: fVector[i] = sum of the i row in the B[g] matrix (B[g]_ij=Ag_ij-k_i*k_j/M).
 */
double* calcfVec(graph *G)
{
	int size, i, j;
	double *fVec;
	double sub;
	fVec=(double*)malloc(sizeof(double)*size);
	size=G->n;
	//calculating f_i for every i in g
	for(i=0;i<size;i++)
	{
		sub=0;
		//for every j in g
		for(j=0;j<size;j++)
		{
			//we need to provide M!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			sub+=((G->graph_nodes)[i]->degree)*((G->graph_nodes)[j]->degree)/M;
		}
		//row sum equals it's length because the relate matrix have only '1's in it.
		*fVec=((G->relate_matrix)->private[i])->size-sub;
		fVec++;
	}
	return fVec;
}

/*
 * Calculates a matrix's norm.
 */
int calcMatrixNorm(graph *G)
{
	int max=0, i, rowlen;
	for(i=0;i<G->n;i++)
	{
		rowlen=((G->relate_matrix)->private)[i]->size;
		if (rowlen>max)
			max=rowlen;
	}
	return max;
}

/*
 * frees a BHat matrix.
 */
void freeBHat(BHatMatrix *B)
{
	/*other inputs?????????????????????????*/
	free_graph(B->G);
	free(B->f_vector);
}


/*//this is the initial version, before splitting into two functions (because of caclDQ)
void multBHat(BHatMatrix *B, double *eigenVector ,double *result)
{
	double *A_g_eigenVector, *Bnorm_eigenVector, *degVec, *fbVec;
	double dotProduct;

	//calculating A_g*bk
	 A_g_eigenVector=(double*) malloc(sizeof(double)*((B->G)->n));
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

	findEigenMultResult((B->G)->n, A_g_eigenVector, degVec, fbVec, Bnorm_eigenVector, result);
	free(A_g_eigenVector);
	free(degVec);
	free(fbVec);
	free(Bnorm_eigenVector);
}
*/
