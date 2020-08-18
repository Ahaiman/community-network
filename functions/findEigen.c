/*
 * findEigen.c
 *
 *  Created on: 12 баев„ 2020
 *      Author: Avital
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "./structures/spmat.h"
#include "./structures/BHatMatrix.h"
#include <string.h>

double* creatRandomVector(double* b0, int size);
void print(int size, double *row);
void divideByNorm(double *vector1, double norm, int size);
double calcDotProduct(double *vector1, double *vector2, int size);
int checkDifference(double *vector1, double *vector2, int size, double eps);
void multNumVec(int size, double num, double *vec, double *res);
void multTwoVecs(int size, double *fVector, double *eigenVector, double *res);
void findEigen_MultResult(int size, double *A_g_eigenVector, double *degVec, double *fbVec, double *Bnorm_eigenVector, double *result);
void SubtractTwoVectors(int size, double *vec1, double *vec2);
void AddTwoVectors(int size, double *vec1, double *vec2);
double findEigenValue(BHatMatrix *B, int *eigenVector);

//pointers!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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

/*eigen vector is pre - initaliize
 * function returns eigenValue and sets value into eigenvector
 */
double findEigenValue(BHatMatrix *B, int *eigenVector){

	/*Variables Deceleration*/
	int i = 0 , ifGreatThenEps = 1, matrixSize;
	double *tmp, *result;
	double vector_norm, epsilon = 0.00001, eigenValue;
	clock_t start, end;

	srand(time(NULL));
	start = clock();

	matrixSize = (B -> G)->n;

	/*Creating Initial Random Vector*/
	if(eigenVector == NULL){
		printf("Intial Vector Allocation Failed");
		exit(0);
	}
	creatRandomVector(eigenVector, matrixSize);



	/*Perform power iteration to obtain the eigenvector
	 * Running the algorithm of power iteration
	 */

	while(ifGreatThenEps){

		result = (double*) malloc(sizeof(double)*(matrixSize));

		/*Calculating (result = ^B[g] * b_k) */
		B -> BHatMult(B, eigenVector ,result);

		/*calculating the vector's magnitude*/
		vector_norm = sqrt(calcDotProduct(result, result, matrixSize));

		/*Calculating the corresponding dominant eigenvalue
		 *
		 *     (Ab_k)*(b_k)
		 * в = --------------
		 *     b_k * b_ k
		 *
		 */
		eigenValue = (calcDotProduct(result, eigenVector, matrixSize) /
				calcDotProduct(eigenVector,eigenVector, matrixSize));


		/*normalizing the vector*/
		if(vector_norm != 0.0) {
			divideByNorm(result, vector_norm, matrixSize);
		}

		/*Checking if the difference between vectors is smaller then epsilon*/
		ifGreatThenEps = checkDifference(eigenVector, result, matrixSize, epsilon);

		/*Swapping information between variables to continue the algorithm
		 * b_k = b_k1*/

		free(tmp);
		tmp = eigenVector;
		eigenVector = result;
		result = tmp;

	}

	free(tmp);
//	end = clock();
//	printf("Prog  took: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

	return eigenValue;
}




double* creatRandomVector(double* b0, int size){
	int i;
	for(i = 0; i < size; i++){
		*b0 = rand();
		b0++;
	}
	return b0;
}


void print(int size, double *row){
	int i;
	double k;
	for(i= 0; i < size; i++){
		k = *(row +i);
		printf("curent row is : %f\n", k);
	}

}


/*Divide
 * The function receives a vector,
 * and normalize it by dividing it in it's size
 */
void divide(double *vector1, double norm, int size){
	double *p = vector1;
	int i = 0;
	for(; i < size; i++){
		*p = (double) (*p) / norm;
		p += 1;
	}
}

/*calcDotProduct
 * The function calculated product between two vectors
 */
double calcDotProduct(double *vector1, double *vector2, int size){
	double *firstPointer = vector1, *secondPointer = vector2;
	double product = 0.0;
	int i = 0;
	for(; i < size; i++){
		product += (*firstPointer) * (*secondPointer);
		firstPointer = firstPointer + 1;
		secondPointer = secondPointer + 1;
	}
	return product;
}

/*checkDifference
 * The function return "true" if the difference between to vectors
 * is greater then epsilon. "false" otherwise.
 */
int checkDifference(double *vector1, double *vector2, int size, double eps){
	double *p1 = vector1, *p2 = vector2;
	int i;
	double diff;
	for(i = 0; i < size; i++){
		diff = *p1 - *p2;
		if(fabs(diff) >= eps)
			return 1;
		p1 += 1;
		p2 += 1;
	}
	return 0;
}


