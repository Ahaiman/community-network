

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "./graph.h"
#include "./spmat.h"
#include "./BHatMatrix.h"
#include "./linkedList.h"
#include "../functions/functions.h"

/*
 * --------Functions Definition---------
 */


BHatMatrix* createMatrixBHat (graph*, spmat *, int *);
void multBHat(BHatMatrix *, graph *, double * ,double *, int );
void initializeFVector(BHatMatrix *B);
int sumRowsA(spmat *, graph * , int );
double sumRowsD(graph *, BHatMatrix *, int);
double sumRowB (BHatMatrix *, int);
void multNumVec(graph * ,double, int*, double*);
void substractTwoVecs(graph *, double*, double*, double*);
double  calcMatrixNorm(BHatMatrix *);
double calcM(BHatMatrix *);
void freeBHat(BHatMatrix *);

/*
 * --------Implementation---------
 */

/*
 * Bhat matrix initialization.
 */
BHatMatrix *createMatrixBHat (graph *G, spmat *relate_matrix, int *degrees)
{
	BHatMatrix *B;
    B = (BHatMatrix *) malloc (sizeof(BHatMatrix));
    if(B == NULL)
    {
    	printf("B Allocation Failed");
    	exit(0);
    }
	B -> originalGraph = G;
	B -> relate_matrix = relate_matrix;
	B -> degrees = degrees;
	B -> originalSize = G -> n;
	B -> constM = calcM(B);
	initializeFVector(B);
	B -> matrixNorm = calcMatrixNorm(B);
	B -> freeBHat = freeBHat;
	B -> multBHat = multBHat;
	return B;
}

void initializeFVector(BHatMatrix *B){
	double *f = (double *) malloc(sizeof(double) * B -> originalSize);
	B->f_vector = f;
}
/*
 * Multiplies a shifted Bhat matrix by a vector.
 * The output is in "result" vector.
 */
void multBHat(BHatMatrix *B, graph *group, double *vector ,double *result, int doShift)
{

	double *A_s, *D_s, *AminusD;
	int *degrees = B -> degrees, *nodes = group -> graph_nodes;
	int m, n = B -> originalSize, size = group -> n, nodeIndex;
	double K_s;

	/*delete*/
	double a,b,c,d, t;
	int i;

	/*A * s */
	//A_s = (int *) malloc (sizeof(int) * n);
	A_s = (double *) malloc (sizeof(double) * n);
	spmat_mult(B, group, vector, A_s);
//	spmat_mult(B->G, vector, A_s);

	/*delete*/
	for(i = 0; i < n; i++){
		t = *(A_s + i);
	}

	/*K * s */
	K_s = calcDotProductInt(group, degrees, vector);
	K_s *= (B -> constM);

	/*D_s*/
	D_s = (double *) malloc (sizeof(double) * n);

	multNumVec(group, K_s, degrees, D_s);
//	multNumVec(B->G, K_s, degrees, D_s);

	AminusD = (double *) malloc (sizeof(double) * n);
//	substractTwoVecs(B->G, A_s, D_s, AminusD);
	substractTwoVecs(group, A_s, D_s, AminusD);

	for(m = 0; m < size; m ++)
	{
//		*result = *AminusD - (*vector) * (sumRowsD(B, m) - sumRowsA(B -> G, m));
		nodeIndex = *nodes;
		a = *(AminusD + nodeIndex);
		b = *(vector + nodeIndex);
//		c = sumRowsD(group, B, nodeIndex);
//		d = sumRowsA(group , nodeIndex);
//		*(result + nodeIndex) = a + b *(c - d);
		c = *(B -> f_vector + nodeIndex);
		*(result + nodeIndex) = a - b * c;
		if(doShift)
			*(result + nodeIndex) += (b * (B -> matrixNorm));
		nodes++;
	}
	free(A_s);
	free(D_s);
	free(AminusD);
}


int sumRowsA(spmat *relate_matrix, graph *group , int m)
{

	int counter=0, sum = 0;
	int *nodes = group -> graph_nodes;
	linkedList* mrow;
	linkedList_node* currNode;

	mrow = *((linkedList **)(relate_matrix -> private) + m);
	currNode = mrow->head;

	 while (currNode != NULL && counter < group -> n)
	{
		if(currNode -> value == *nodes){
			currNode = currNode->next;
			counter++;
			sum++;
			nodes++;

		}
		else{
			if(currNode -> value < *nodes )
				currNode = currNode -> next;
			else{
				counter++;
				nodes++;
			}
		}
	}
	return sum;
}

double sumRowsD(graph *group, BHatMatrix *B, int m)
{
	int i,counter=0, sum = 0;
	int *listNodes = group -> graph_nodes, *degrees = B -> degrees;
	double d;

	if(group -> n == B -> originalSize)
		return *(degrees+m);

	d = (B-> constM) * (*(degrees+m));

	for (i=0;i <group -> n; i++)
	{
		sum +=*(degrees+ *listNodes);
		listNodes++;
	}
	return (double)(sum * d);
}

double sumRowB (BHatMatrix *B, int i)
{
	int currNodeValue = 0, j, num;
	double sum = 0;
	spmat *relate_matrix = B -> relate_matrix;
	int *degrees = B -> degrees;

	linkedList* mrow;
	linkedList_node* currNode;
	mrow = *((linkedList **)(relate_matrix->private)+ i);
	currNode = mrow -> head;

	for(j = 0 ; j < B -> originalSize; j++){
		if(j == i)
			continue;
		if(currNode == NULL)
		{
			num = 0;
			sum += fabs(num - (B -> constM) * (*(degrees + i)) *
					(*(degrees + j)));
			continue;
		}

		currNodeValue = currNode -> value;


		if(currNodeValue != j)
			num = 0;
		else
		{
			num = 1;
			currNode = currNode -> next;
		}
		sum +=  fabs(num - (B -> constM) * (*(degrees + i)) *
				(*(degrees + j)));
	}

	return sum;
}

/*
 * Mohamads : Calculates a matrix's norm.
 */
double calcMatrixNorm(BHatMatrix *B)
{
	double max = 0, B_ii, sumRow, sumRowBa, partB;
	int *degrees = B -> degrees;
	int currDeg, i;

	for(i = 0; i < B -> originalSize ; i++)
	{
		sumRow = 0;
		currDeg = *(degrees + i);
		//|Aii - 1/M* Dii
		// 0 - 1/M*(degree^2)

		//abs - (B[ii] - fvector[i] )
		//+
		//sum of |B[k][i]| to all k (k!=i)

		B_ii = currDeg * currDeg * (-1) * (B -> constM);
//		partB= *(B -> f_vector + i);
		sumRow = fabs(B_ii) + sumRowB(B, i);

		if(max < sumRow)
			max = sumRow;
	}
	return max;
}



//		sumRow = sumRow - sumRowsA(B, i) + sumRowsD(B -> originalGraph, B, i);
//		sumRow = fabs(sumRow);
//
//
//
//
//
//
//		if(sumRow < 0)
//			sumRow *= -1;
//		sumRow = abs(sumRow);
//		sumRowBa = sumRowB(B, i);
//
//		sumRow += sumRowBa;
//		if(max < sumRow)
//			max = sumRow;
//	}

/*
 * Calculates a matrix's norm.
 */
double calcMatrixNorm1(BHatMatrix *B)
{
	double max=0, sumRow;
	int *nodes =  B -> originalGraph -> graph_nodes;
	int *degrees = B -> degrees;
	int i,j, currRow, graphNodeIndex, currNodeValue;

	//to delere
	int divisionNumber = 0;


	spmat *relate_matrix = B -> relate_matrix;
	linkedList* mrow;
	linkedList_node* currNode;
	int num;

	for(i = 0; i < B -> originalSize; i++)
	{
		currRow = *(nodes + i);

		mrow = *((linkedList **) (relate_matrix->private) + currRow);
		currNode = mrow->head;

		for(j = 0; j < B -> originalSize; j++)
			{
				graphNodeIndex = *nodes;
				if(currNode == NULL)
				{
					num = 0;
					sumRow += fabs(num - (B -> constM) * (*(degrees + currRow)) *
							(*(degrees + graphNodeIndex)));
					nodes++;
				}
				else
				{
					if (currNode -> partByS == divisionNumber)
					{
						currNodeValue = currNode -> value;
						if(currNodeValue != graphNodeIndex)
							num = 0;
						else
						{
							num = 1;
							currNode = currNode -> next;
						}
						sumRow +=  fabs(num - (B -> constM) * (*(degrees + currRow)) *
								(*(degrees + graphNodeIndex)));
						nodes++;
					}
				}
			}
		if(max < sumRow)
			max = sumRow;
		sumRow = 0;
		nodes -= B -> originalSize;
		}
	return max;
}


/*
 * Multiplies a vector by a number.
 * The output is in "result" vector.
 */
void multNumVec(graph *g, double num, int *vec, double *result)
{
	int i, nodeIndex;
	int n = g -> n;
	int *nodes = g -> graph_nodes;

	for(i = 0;i < n;i++)
	{
		nodeIndex = *nodes;
		*(result + nodeIndex) = (*(vec + nodeIndex))*num;
		nodes++;
	}
}

/*
 * Subtracts two column vectors according to this scheme: result[i]=vec1[i]-vec2[i].
 * The output is in "result" vector.
 */
void substractTwoVecs(graph *g, double *vec1, double *vec2, double *result)
{
	int i, nodeIndex;
	int n = g -> n;
	int *nodes = g -> graph_nodes;

	for(i = 0;i < n;i++)
	{
		nodeIndex = *nodes;
		*result=*vec1-*vec2;
		*(result + nodeIndex) = *(vec1 + nodeIndex) - *(vec2 + nodeIndex);
		nodes++;
	}
}

/*
 * calculates a local M = the sum of the degrees of the nodes in G.
 */
double calcM(BHatMatrix *B)
{
	int i, M = 0;
	if(B -> originalSize == 0) return 0;

	for(i = 0;i < B -> originalSize ;i++)
	{
		M += *(B->degrees + i);
	}
	return (double)(1.0/M);
}

/*
 * frees a BHat matrix.
 */
void freeBHat(BHatMatrix *B)
{
	free(B -> degrees);
	B -> originalGraph -> free_graph (B -> originalGraph);
	B -> relate_matrix -> spmat_free(B -> relate_matrix, 1);
	free(B);
}

