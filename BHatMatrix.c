/*
 * BHatMatrix.c - Source File
 * Implementation of the functions declared in the header file
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "graph.h"
#include "spmat.h"
#include "BHatMatrix.h"
#include "algorithm2.h"
#include "linkedList.h"
#include "errorHandler.h"

/* --------Functions Deceleration--------- */

/*Initialization*/
BHatMatrix*			createMatrixBHat (graph*, spmat*, int*);
void 				initializeFVector(BHatMatrix*);

/*Multiplying With An Input Vector*/
void 				multBHat(BHatMatrix*, graph*, double* ,double*, int);
void 				BgMult(BHatMatrix*, graph*, double*, double*);
void 				spmat_mult(spmat*, graph*, const double*, double*);
void 				multNumVec(graph* ,double, int*, double*);
void 				substractTwoVecs(graph*, double*, double*, double*);

/*Matrix Norm Calculation*/
int					sumRowsA(spmat*, graph* , int);
double 				sumRowsD(graph*, BHatMatrix*, int);
double 				sumRowB (BHatMatrix*, int);
double 				calcMatrixNorm(BHatMatrix*);

/*General*/
double 				calcM(BHatMatrix*);
double 				calcBgPlace(BHatMatrix* ,int, int);
void 				freeBHat(BHatMatrix*, int);


/* --------Functions Implementation---------*/

BHatMatrix *createMatrixBHat (graph *G, spmat *relate_matrix, int *degrees)
{
	BHatMatrix *B;

	B = (BHatMatrix *) malloc (sizeof(BHatMatrix));
	if(B == NULL) returnErrorByType(2);

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

void initializeFVector(BHatMatrix *B)
{
	double *f;

	f = (double *) malloc(sizeof(double) * B -> originalSize);
	if(f == NULL) returnErrorByType(4);

	B -> f_vector = f;
}

void BgMult(BHatMatrix *B, graph *group, double *vector, double *result)
{
	double *A_s, *D_s, *AminusD;
	double K_s;
	int *degrees = B -> degrees, *nodes = group -> graph_nodes;
	int m, n = B -> originalSize, size = group -> n;

	/*Allocating a vector to hold the multiplication result between the relate_matrix and an input vector: A * s*/
	A_s = (double *) malloc (sizeof(double) * n);
	if(A_s == NULL) returnErrorByType(4);

	spmat_mult(B -> relate_matrix, group, vector, A_s);

	/*A constant that holds the dot product result between the degrees vector and another vector, multiplied by constM*/
	K_s = calcDotProductInt(group, degrees, vector);
	K_s *= (B -> constM);

	/*Allocating a vector to hold the multiplication result between D matrix and an input vector: D * s*/
	D_s = (double *) malloc (sizeof(double) * n);
	if(D_s == NULL) returnErrorByType(4);

	multNumVec(group, K_s, degrees, D_s);

	/*Allocating a vector to hold the multiplication result between the current B matrix and an input vector*/
	AminusD = (double *) malloc (sizeof(double) * n);
	if(AminusD == NULL) returnErrorByType(4);

	/* B * s = (A - D) * s = (A * s) - (D * s)*/
	substractTwoVecs(group, A_s, D_s, AminusD);

	/*Inserting values to the result vector: result[i] = B_g[i] * vector*/
	for(m = 0; m < size; m ++)
	{
		*result = *(AminusD + *nodes);
		nodes++;
		result++;
	}
	free(A_s);
	free(D_s);
	free(AminusD);
}

double calcBgPlace(BHatMatrix *B, int i, int k){
	int A_ik = 0;
	double D_ik;
	linkedList* mrow;
	linkedList_node* currNode;

	/*Calculating D[i][k] */
	D_ik = (B -> constM) * (*(B -> degrees + i)) * (*(B -> degrees + k));

	/*Calculating A[i][k] */
	mrow = *((linkedList **)(B -> relate_matrix -> private) + i);

	currNode = mrow -> head;
	while(currNode != NULL)
	{
		/*If the current node's index is greater than k, than k is not a neighbor to node i -> A[i][k] == 0*/
		if(currNode -> value > k)
			return (double)(A_ik - D_ik);

		/*If the current node's index is equal to k, than k is a neighbor to node i -> A[i][k] == 1*/
		if(currNode -> value == k)
		{
			A_ik = 1;
			return (double)(A_ik - D_ik);
		}
		currNode = currNode -> next;
	}

	/*Returning B[i][k] = A[i][k] - D[i][k]*/
	return (double)(A_ik - D_ik);
}

void multBHat(BHatMatrix *B, graph *group, double *vector ,double *result, int doShift)
{
	double *A_s, *D_s, *AminusD;
	double K_s, B_m, v_m, F_m;
	int *degrees = B -> degrees, *nodes = group -> graph_nodes;
	int m, n = B -> originalSize, size = group -> n, nodeIndex;

	/*Allocating a vector to hold the multiplication result between the relate_matrix and an input vector: A * s*/
	A_s = (double *) malloc (sizeof(double) * n);
	if(A_s == NULL) returnErrorByType(4);

	spmat_mult(B -> relate_matrix, group, vector, A_s);

	/*A constant that holds the dot product result between the degrees vector and another vector, multiplied by constM*/
	K_s = calcDotProductInt(group, degrees, vector);
	K_s *= (B -> constM);

	/*Allocating a vector to hold the multiplication result between D matrix and an input vector: D * s*/
	D_s = (double *) malloc (sizeof(double) * n);
	if(D_s == NULL) returnErrorByType(4);

	multNumVec(group, K_s, degrees, D_s);

	/*Allocating a vector to hold the multiplication result between the current B matrix and an input vector*/
	AminusD = (double *) malloc (sizeof(double) * n);
	if(AminusD == NULL) returnErrorByType(4);

	/* B * s = (A - D) * s = (A * s) - (D * s)*/
	substractTwoVecs(group, A_s, D_s, AminusD);

	/*Inserting values to the result vector*/
	for(m = 0; m < size; m ++)
	{
		nodeIndex = *nodes;
		B_m = *(AminusD + nodeIndex);
		v_m = *(vector + nodeIndex);
		F_m = *(B -> f_vector + nodeIndex);

		/* (B^[g] * s) = (A * s) - (D * s) - (f_g * s) */
		*(result + nodeIndex) = B_m - v_m * F_m;

		/*In order to create the shifting matrix, we add the matrix's norm to the matrix's main diagonal*/
		if(doShift)
			*(result + nodeIndex) += (v_m * (B -> matrixNorm));
		nodes++;
	}
	free(A_s);
	free(D_s);
	free(AminusD);
}

/* Multiplication of a sparse matrix by a vector using linked-lists */
void spmat_mult(spmat *A, graph *group, const double *v, double *result)
{
	linkedList_node *currNode;
	linkedList *currList, **rows_indices = A -> private;
	int *nodes = group -> graph_nodes, *run = nodes;
	int row, counter = 0;
	double sum;

	if(result == NULL) returnErrorByType(4);

	/* Iterating through the nodes with "run" pointer,
	 * while iterating on the list of neighbors in the sparse matrix with "currNode".
	 * Summing only the places where A[i][j] = 1
	 */
	for(row = 0; row < group -> n; row++)
	{
		currList = *(rows_indices + *nodes);
		currNode = currList -> head;
		sum = 0;
		counter = 0;
		while (currNode != NULL && counter < group -> n)
		{
			if(currNode -> value == *run)
			{
				sum += *(v + currNode -> value);
				currNode = currNode->next;
				counter++;
				run++;
			}
			else
			{
				if(currNode -> value < *run)
					currNode = currNode->next;
				else
				{
					counter++;
					run++;
				}
			}
		}
		run -= counter;
		*(result + *nodes) = sum;
		nodes++;
	}
}

void multNumVec(graph *g, double num, int *vec, double *result)
{
	int i, nodeIndex;
	int n = g -> n;
	int *nodes = g -> graph_nodes;

	for(i = 0;i < n;i++)
	{
		nodeIndex = *nodes;
		*(result + nodeIndex) = (*(vec + nodeIndex)) * num;
		nodes++;
	}
}

void substractTwoVecs(graph *g, double *vec1, double *vec2, double *result)
{
	int i, nodeIndex;
	int n = g -> n;
	int *nodes = g -> graph_nodes;

	for(i = 0;i < n; i++)
	{
		nodeIndex = *nodes;
		*(result + nodeIndex) = *(vec1 + nodeIndex) - *(vec2 + nodeIndex);
		nodes++;
	}
}

int sumRowsA(spmat *relate_matrix, graph *group , int m)
{
	int counter=0, sum = 0;
	int *nodes = group -> graph_nodes;
	linkedList* mrow;
	linkedList_node* currNode;

	mrow = *((linkedList **)(relate_matrix -> private) + m);
	currNode = mrow->head;

	/*Iterating over the relate matrix row corresponding to index "m"*/
	while (currNode != NULL && counter < group -> n)
	{
		/*If we found the current node value in the linked list of node m, there is an edge between the nodes*/
		if(currNode -> value == *nodes)
		{
			currNode = currNode->next;
			counter++;
			sum++;
			nodes++;
		}
		else
		{
			if(currNode -> value < *nodes )
				currNode = currNode -> next;
			else
			{
				counter++;
				nodes++;
			}
		}
	}
	return sum;
}

double sumRowsD(graph *group, BHatMatrix *B, int m)
{
	int i, sum = 0;
	int *listNodes = group -> graph_nodes, *degrees = B -> degrees;
	double d;

	if(group -> n == B -> originalSize)
		return *(degrees + m);

	d = (B -> constM) * (*(degrees + m));

	for (i = 0; i < group -> n; i++)
	{
		sum += *(degrees + *listNodes);
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
	mrow = *((linkedList **)(relate_matrix -> private) + i);
	currNode = mrow -> head;

	for(j = 0 ; j < B -> originalSize; j++){
		if(currNode == NULL)
		{
			/*The "num" variable indicates if there is an edge between the input "i" node to the current node*/
			num = 0;
			/* sum += |B[i][j]| = 0 - |D[i][j]| */
			sum += fabs(num - (B -> constM) * (*(degrees + i)) * (*(degrees + j)));
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
		/* Sum += |B[i][j]| = num - |D[i][j]| */
		sum +=  fabs(num - (B -> constM) * (*(degrees + i)) * (*(degrees + j)));
	}
	return sum;
}

double calcMatrixNorm(BHatMatrix *B)
{
	double max = 0, sumRow;
	int i;

	for(i = 0; i < B -> originalSize ; i++)
	{
		/*Finding the maximum sum of a row in B*/
		sumRow = sumRowB(B, i);
		if(max < sumRow)
			max = sumRow;
	}
	return max;
}

double calcM(BHatMatrix *B)
{
	int i, M = 0;

	if(B -> originalSize == 0) return 0;

	for(i = 0;i < B -> originalSize ;i++)
		M += *(B -> degrees + i);

	return (double)(1.0/M);
}

void freeBHat(BHatMatrix *B, int graphIsOneClique)
{
	/*Frees the input graph, only if it is not a clique*/
	if(!graphIsOneClique)
		B -> originalGraph -> free_graph (B -> originalGraph);

	/*Frees the relate matrix represented by a sparse matrix*/
	B -> relate_matrix -> spmat_free(B -> relate_matrix);

	free(B -> degrees);
	free(B -> f_vector);
	free(B);
}
