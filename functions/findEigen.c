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
int counterNonZero(int size, FILE *inputMatrix);
void divide(double *vector1, double norm, int size);
double calcDotProduct(double *vector1, double *vector2, int size);
int checkDifference(double *vector1, double *vector2, int size, double eps);


double findEigenValue(BHatMatrix *B, int *eigenVector, int matrixSize){

	/*Variables deceleration*/
	int i = 0 , ifGreatThenEps = 1, place = 0;
	double *initialVec, *matrixRow, *tmp;
	double vector_norm, epsilon = 0.00001, eigenValue;
	spmat *sparseMatrix;
	clock_t start, end;

	srand(time(NULL));
	start = clock();

	sparseMatrix = spmat_allocate_list(matrixSize);
	creatRandomVector(initialVec, matrixSize);

	/*Reading the vector*/
	initialVec = (double*) malloc(sizeof(double)*(matrixSize));
	if(initialVec == NULL){
		printf("Intial Vector Allocation Failed");
		exit(0);
	}

	/*Perform power iteration to obtain the eigenvector*/
	/*Running the algorithm of power iteration*/
	while(ifGreatThenEps){

		/*Creating A*Bk*/
		//eigenValue = (double*) malloc(sizeof(double)*(matrixSize));

		sparseMatrix -> mult(sparseMatrix, initialVec,eigenVector);

		/*calculating the vector's magnitude*/
		vector_norm = sqrt(calcDotProduct(eigenValue, eigenValue, matrixSize));

		/*normalizing the vector*/
		if(vector_norm != 0.0) {
			divide(eigenVector, vector_norm, matrixSize);
		}

		/*Checking if the difference between vectors is smaller then epsilon*/
		ifGreatThenEps = checkDifference(initialVec, eigenVector,matrixSize, epsilon);

		/*Swaping information between variables to continue the algorithm
		 * b_k = b_k1*/
		tmp = initialVec;
		initialVec = eigenValue;
		eigenVector = tmp;

	}


	/*Calculating the corresponding dominant eigenvalue	 */
	eigenValue = (calcDotProduct(initialVec, eigenValue, matrixSize) /calcDotProduct(eigenValue,eigenValue, matrixSize));

	free(initialVec);
	sparseMatrix -> free(sparseMatrix);
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
	/*b0 = b0 - size;*/
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


/* counts non zero values of the input matrix */
int counterNonZero(int size, FILE *inputMatrix){
	int counter = 0, i = 0, j = 0;
	int n;
	double *row;
	row = (double*) malloc(sizeof(double)*(size));
	assert(row != NULL);

	for(; i < size; i++){
		n = fread(row, sizeof(double), size, inputMatrix);
		assert(n == size);

		for(j = 0; j < size; j++){
			if(*row != 0)
				counter++;
			row++;
		}

		row = row - size;
	}
	free(row);
	return counter;
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


