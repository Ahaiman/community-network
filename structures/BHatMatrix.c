
#include "./BHatMatrix.h"
#include <stdio.h>
#include <stdlib.h>
#include "./graph.h"
#include "./spmat.h"
#include "../functions/functions.h"

/*
 * --------Functions Definition---------
 */


BHatMatrix* createMatrixBHat (graph*);
void multBHat(BHatMatrix*, double*, double*, int);
int sumRowsA(graph *, int );
double sumRowsD(BHatMatrix *, int);
double sumRowB (BHatMatrix *, int);
void multNumVec(int, double, double*, double*);
void substractTwoVecs(int, double*, double*, double*);
int  calcMatrixNorm(BHatMatrix *);
double calcM(graph *);
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
    if(B == NULL)
    {
    	printf("B Allocation Failed");
    	exit(0);
    }

	B -> G = G;
	B -> constM = calcM(G);
	B -> originalSize = G -> n;
	B -> matrixNorm = calcMatrixNorm(B);
	B -> freeBHat = freeBHat;
	B -> multBHat = multBHat;
	return B;
}

/*
 * Multiplies a shifted Bhat matrix by a vector.
 * The output is in "result" vector.
 */
void multBHat(BHatMatrix *B, double *vector ,double *result, int doShift)
{
	//int *A_s;
	double *A_s, *D_s, *AminusD;
	spmat *relate_matrix  = B -> G -> relate_matrix;
	int m, n = B -> G -> n;
	double K_s;

	/*A * s */
	//A_s = (int *) malloc (sizeof(int) * n);
	A_s = (double *) malloc (sizeof(double) * n);
	relate_matrix -> spmat_mult(relate_matrix, vector, A_s);

	/*K * s */
	K_s = calcDotProduct(B->G->degrees, vector, n) * (B -> constM);

	/*D_s*/
	D_s = (double *) malloc (sizeof(double) * n);

	multNumVec(n, K_s, B->G->degrees, D_s);

	AminusD = (double *) malloc (sizeof(double) * n);
	substractTwoVecs(n, A_s, D_s, AminusD);

	for(m = 0; m < n; m ++)
	{
		*result = *AminusD - (*vector) * (sumRowsD(B, m) - sumRowsA(B -> G, m));

		if(doShift)
			*result += (*vector) * (B -> matrixNorm);

		result++;
		AminusD++;
		vector++;
	}
	free(A_s);
	free(D_s);
}


int sumRowsA(graph *G, int m)
{
	spmat *relate_matrix=G->relate_matrix;
	int *nodesList=G->graph_nodes;
	int counter=0;
	linkedList* mrow;
	linkedList_node* currNode;
	mrow=*((relate_matrix->private)+m);
	currNode=mrow->head;
	while(currNode!=NULL)
	{
		if (currNode->partByS==G->divisionNumber)
			counter ++;
		currNode = currNode -> next;
	}
	return counter;
}

double sumRowsD(BHatMatrix *B, int m)
{
	int i, sum=0, counter=0;
	int *listNodes=B->G->graph_nodes, *degrees=B->G->degrees;
	double d;
	d=B->constM*(*(degrees+m));
	for (i=0;i<B->originalSize;i++)
	{
		if (i==*listNodes)
		{
			sum+=*(degrees+i);
			counter++;
			listNodes++;
		}
		if(counter == (B->G)->n)
			break;
	}
	return sum*d;
}

double sumRowB (BHatMatrix *B, int i)
{
	int k = 0, sum = 0;
	spmat *relate_matrix=B->G->relate_matrix;
	int *degrees=B->G->degrees;

	linkedList* mrow;
	linkedList_node* currNode;
	mrow = *((relate_matrix->private)+ i);
	currNode = mrow->head;

	while(currNode!=NULL)
	{
		k = currNode -> value;
		if(k != i)
		{
			if (currNode -> partByS == B -> G -> divisionNumber)
				sum += abs((1 - *(degrees + k) * *(degrees + i) * (B -> constM)));
		}
		currNode = currNode -> next;
	}
	return sum;
}

/*
 * Calculates a matrix's norm.
 */
double calcMatrixNorm(BHatMatrix *B)
{
	double max=0, i, sumRow;

	for(i = 0; i < B -> G -> n; i++)
	{
		sumRow = abs(pow(*(B -> G -> degrees + i), 2) * (B -> constM) * (-1) - sumRowsA(B-> G, i) + sumRowsD(B, i));
		sumRow += sumRowB;
		if(max < sumRow)
			max = sumRow;
	}
	return max;
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
 * Subtracts two column vectors according to this scheme: result[i]=vec1[i]-vec2[i].
 * The output is in "result" vector.
 */
void substractTwoVecs(int size, double *vec1, double *vec2, double *result)
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
 * calculates a local M = the sum of the degrees of the nodes in G.
 */
double calcM(graph *G)
{
	int i, M=0;
	for(i=0;i<G->n;i++)
	{
		M+=*(G->degrees);
		(G->degrees)++;
	}
	return (double)(1/M);
}

/*
 * frees a BHat matrix.
 */
void freeBHat(BHatMatrix *B)
{
	free_graph(B->G, 1);
}

