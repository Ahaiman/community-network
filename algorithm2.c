/*
 * algorithm2.c - Source File
 * Implementation of the functions declared in the header file
 */

#define EPSILON 0.00001
#define POSITIVE(X) ((X) > EPSILON)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "algorithm2.h"
#include "graph.h"
#include "BHatMatrix.h"
#include "errorHandler.h"

/* --------Functions Deceleration--------- */

void 			divisionGraphToTwo(BHatMatrix *B, graph *group, double *s, int *out);
void 			calcFVector(BHatMatrix *B, graph *group);
double* 		findEigenValue(BHatMatrix *B,graph *group, double *eigenValue);
void 			creatRandomVector(double* b0, graph *group);
double 			calcDotProductInt(graph *group, int *degrees, double *vector);
double 			calcDotProduct(graph *group, double *vector1, double *vector2);
int 			checkDifference(graph *group, double *vector1, double *vector2, double eps);
void 			divideByNorm(graph *group, double *vector1, double norm);
void 			computeS(double *eigenVector, graph *group, double *s);
void 			createTrivialS(graph *group, double *s);
double 			computeDQ(double *s,graph *group, BHatMatrix *B);

/* --------Functions Implementation---------*/

/* ------------------------------------- Main Algorithm -------------------------------------- */

void divisionGraphToTwo(BHatMatrix *B, graph *group, double *s, int *out)
{
	double *eigenVector;
	double eigenValue, dQ;

	/*Updating B's F vector according to the current group*/
	calcFVector(B, group);

	/*Compute the leading eigenpair: eigen-vector and eigen-value of the modularity matrix B^[g] shifted*/
	eigenVector = findEigenValue(B, group, &eigenValue);

	/*If the eigenvalue is not positive, the network is indivisible*/
	if(!POSITIVE(eigenValue)){
		*out = -1;
		free(eigenVector);
		return;
	}

	/*Computing the division vector s, according to the eigen-vector*/
	computeS(eigenVector, group, s);

	/*Computing DQ according to the created s*/
	dQ = computeDQ(s,group, B);

	/*If DQ is not positive, the network is indivisible*/
	if(!POSITIVE(dQ))
		createTrivialS(group,s);

	free(eigenVector);
}

/* ----------------------------------- F Vector Calculation ----------------------------------- */

void calcFVector(BHatMatrix *B, graph *group){
	double *f_vector = B -> f_vector;
	int *nodes = group -> graph_nodes;
	int i = 0, currIndex;
	double rowInMatrixA, rowInMatrixD, rowInMatrixB;

	for(;i < group -> n; i++){
		currIndex = *(nodes + i);

		/*Calculating the sum of the i'th row in the adjacency matrix*/
		rowInMatrixA = sumRowsA(B-> relate_matrix, group, currIndex);

		/*Calculating the sum of the i'th row in degrees matrix - D*/
		rowInMatrixD = sumRowsD(group,B, currIndex);

		/*Calculating the sum of the i'th row in B[g] matrix*/
		rowInMatrixB = rowInMatrixA - rowInMatrixD;

		/*Updating B's f vector*/
		*(f_vector + currIndex)  = rowInMatrixB;
	}
}

/* --------------------------------- Eigen - Pair Calculation --------------------------------- */

double* findEigenValue(BHatMatrix *B,graph *group, double *eigenValue)
{
	/*Variables Deceleration*/
	int ifGreatThenEps = 1, matrixSize, iterationCounter = 0, maxIterations;
	double *eigenVector, *tmp, *result;
	double vector_norm;

	/*To avoid infinite loop, we use a limit on the number of iterations*/
	maxIterations = 0.5*(group -> n)*(group -> n) +
			10000*(group -> n) + 300000;

	matrixSize = B -> originalSize;

	eigenVector = (double *) malloc(matrixSize * sizeof(double));
	if(eigenVector == NULL) returnErrorByType(5);

	/*Initializing the eigen vector as a random vector*/
	creatRandomVector(eigenVector, group);

	result = (double *) malloc(matrixSize * sizeof(double));
	if(result == NULL) returnErrorByType(4);

	tmp = result;

	/*Iterating while the difference between b_k and b_k+1 is not small enough*/
	while(ifGreatThenEps && iterationCounter < maxIterations)
	{
		iterationCounter++;

		/*Performing: B^[g] * eigenVector, and inserting the result into the result vector*/
		B -> multBHat(B, group, eigenVector ,result, 1);

		/*Calculating result vector norm*/
		vector_norm = sqrt(calcDotProduct(group, result, result));

		if(vector_norm <= EPSILON) returnErrorByType(7);

		/*Normalizing the result vector*/
		divideByNorm(group, result, vector_norm);

		/*Checking if the difference between the vectors is small enough*/
		ifGreatThenEps = checkDifference(group, eigenVector, result, EPSILON);

		/*Swapping between the vectors*/
		tmp = eigenVector;
		eigenVector = result;
		result = tmp;
	}

	/*Calculating the corresponding dominant eigenvalue*/
	B -> multBHat(B, group, eigenVector ,result, 1);

	/* Calculating the eigen value according to the formula :
	 *
	 *                     (Ab_k)*(b_k)      (Ab_k)*(b_k)
	 * â(shifted matrix) = -------------- = --------------- =  (Ab_k)*(b_k)
	 *                       b_k * b_ k            1
	 *
	 */
	*eigenValue = calcDotProduct(group, result, eigenVector) - (B -> matrixNorm);

	free(result);

	return eigenVector;
}

void creatRandomVector(double* b0, graph *group)
{
	int i;
	int *nodes = group -> graph_nodes;

	for(i = 0; i < group -> n; i++)
	{
		*(b0 + *nodes) = rand();
		nodes++;
	}
}

double calcDotProductInt(graph *group, int *degrees, double *vector)
{
	int *nodes = group -> graph_nodes;
	double dotProduct = 0.0;
	int i = 0, currDeg;

	for(; i < group -> n; i++)
	{
		currDeg = *(degrees + *nodes);
		dotProduct += currDeg * (*(vector + *nodes));
		nodes++;
	}
	return dotProduct;
}

double calcDotProduct(graph *group, double *vector1, double *vector2)
{
	int *nodes = group -> graph_nodes;
	double dotProduct = 0.0;
	int i = 0;

	for(; i < group -> n; i++)
	{
		dotProduct += (*(vector1 + *nodes)) * (*(vector2 + *nodes));
		nodes++;
	}
	return dotProduct;
}

int checkDifference(graph *group, double *vector1, double *vector2, double eps)
{
	int *nodes = group -> graph_nodes;
	int i;
	double diffBetweenValues;

	for(i = 0; i < group -> n; i++)
	{
		diffBetweenValues = *(vector1 + *nodes) - *(vector2 + *nodes);

		/*If we found two places in the vectors, with difference greater than EPSILON, return 1*/
		if(fabs(diffBetweenValues) >= eps)
			return 1;
		nodes++;
	}
	return 0;
}

void divideByNorm(graph *group, double *vector1, double norm)
{
	int i = 0;
	int *nodes = group -> graph_nodes;

	for(; i < group -> n; i++)
	{
		*(vector1 + *nodes) /= norm;
		nodes++;
	}
}

/* ----------------------------------- S Vector Calculation ----------------------------------- */

void computeS(double *eigenVector,  graph *group, double *s)
{
	int i = 0;
	int *nodes = group -> graph_nodes;
	for(; i < group -> n; i++)
	{
		if(POSITIVE(*(eigenVector + *nodes)))
			*(s + *nodes) = 1;
		else
			*(s + *nodes) = -1;
		nodes++;
	}
}

void createTrivialS(graph *group, double *s)
{
	int i = 0;
	int *nodes = group -> graph_nodes;

	/*Check the original value in the s vector, and set this value to all the group's nodes*/
	int orignialValueInS = *(s + *nodes);

	for(; i < group -> n; i++)
	{
		*(s + *nodes) = orignialValueInS;
		nodes++;
	}
}

/* ----------------------------------- DQ Value Calculation ----------------------------------- */

double computeDQ(double *s,graph *group, BHatMatrix *B)
{
	double dQ;
	double *result;

	result = (double*)malloc(B -> originalSize * sizeof(double));
	if(result == NULL) returnErrorByType(4);

	/*Calculate: B^[g] * s*/
	B -> multBHat(B, group,s, result,0);

	/*Calculate DQ*/
	dQ = calcDotProduct(group, s,result);

	free(result);
	return dQ*(0.5);
}
