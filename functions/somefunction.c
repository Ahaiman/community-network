#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <string.h>

double* creatRendomVector(double* b0, int size){
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


int main(int argc, char* argv[]){

	/*Variables deceleration*/
	FILE	*inputMatrix,*outputFile, *vecFile;
	char *implementation;
	int matrixSize, n, nnz;
	int i = 0 , ifGreatThenEps = 1, place = 0;
	double *initialVec, *matrixRow, *result, *tmp;
	double vector_norm, epsilon = 0.00001, eigenValue;

	clock_t start, end;


	srand(time(NULL));
	start = clock();
	(void)argc;

	assert(argc >= 4);

	/*Reading the matrix size into variable*/
	inputMatrix =  fopen(argv[1], "rb");
	assert(inputMatrix != NULL);

	n = fread(&matrixSize, sizeof(int), 1, inputMatrix);
	assert(n == 1);
	fread(&n, sizeof(int), 1, inputMatrix);

	/*Reading the vector*/
	initialVec = (double*) malloc(sizeof(double)*(matrixSize));
	assert(initialVec != NULL);

	/*CASE 1: vector is not provided by user - creating random*/
	if(argc == 4)
		creatRendomVector(initialVec, matrixSize);

	/*CASE 2: vector is provided by user*/
	else{
		vecFile =  fopen(argv[2], "rb");
		n = fread(initialVec, sizeof(double), matrixSize, vecFile);
		assert(n == matrixSize);
		place = 1;
	}

	implementation = argv[place + 3];
	assert (strcmp(implementation, "-array") == 0 ||
			strcmp(implementation, "-list") == 0);


	/*idneftify type*/
	if(strcmp(implementation, "-list") == 0){
	//	sparseMatrix = spmat_allocate_list(matrixSize);
	}

	else{
		nnz = counterNonZero(matrixSize, inputMatrix);
	//	sparseMatrix = spmat_allocate_array(matrixSize, nnz);
	}

	rewind(inputMatrix);
	n = fseek(inputMatrix, 2*sizeof(int),SEEK_SET);


	/*Reading the input matrix (one row at a time).
	 * For each row, adding it to the sparse matrix*/

	for(i = 0; i < matrixSize; i++){
		matrixRow =  (double*) malloc(sizeof(double)*(matrixSize));
		assert(matrixRow != NULL);

		n = fread(matrixRow, sizeof(double), matrixSize, inputMatrix);
		assert(n == matrixSize);

	//	sparseMatrix -> add_row(sparseMatrix, matrixRow, i);
		free(matrixRow);
	}

	/*Perform power iteration to obtain the eigenvector*/
	/*Running the algorithm of power iteration*/
	while(ifGreatThenEps){

		/*Creating A*Bk*/
		result = (double*) malloc(sizeof(double)*(matrixSize));

	//	sparseMatrix -> mult(sparseMatrix, initialVec,result);

		/*calculating the vector's magnitude*/
		vector_norm = sqrt(calcDotProduct(result, result, matrixSize));

		/*normalizing the vector*/
		if(vector_norm != 0.0) {
			divide(result, vector_norm, matrixSize);
		}

		/*Checking if the difference between vectors is smaller then epsilon*/
		ifGreatThenEps = checkDifference(initialVec, result,matrixSize, epsilon);

		/*Swaping information between variables to continue the algorithm
		 * b_k = b_k1*/
		tmp = initialVec;
		initialVec = result;
		result = tmp;
	}

	/*Calculating the corresponding dominant eigenvalue	 */
	eigenValue = (calcDotProduct(initialVec, result, matrixSize) /calcDotProduct(result,result, matrixSize));


	fclose(inputMatrix);
	/*writing the eigen vector to the file*/
	outputFile =  fopen(argv[place + 2], "wb");
	assert(outputFile != NULL);

	place = 1;
	fwrite(&place, sizeof(int), 1, outputFile);
	fwrite(&matrixSize, sizeof(int), 1, outputFile);
	n = fwrite(initialVec, sizeof(double), matrixSize, outputFile);
	assert(n == matrixSize);

	fclose(outputFile);
	free(result);
	free(initialVec);
//	sparseMatrix -> free(sparseMatrix);
	end = clock();
	printf("Prog  took: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
	return 0;
}






