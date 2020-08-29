
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../structures/graph.h"
#include "../structures/spmat.h"
#include "../structures/BHatMatrix.h"
#include "../structures/linkedList.h"
#include "../structures/stack.h"
#include "./functions.h"


/*
 * --------Functions Deceleration---------
 */
	/*computeDQ.c*/
	int sumAd (graph *G, int *s,int index);
	double sumDd (BHatMatrix *B, int *s, int index);
	double computeDQ(double *s, BHatMatrix *B);
	double computeDQChange(double *s, BHatMatrix *B, int index, int dq);

	/*findEigen.c*/
	double findEigenValue(BHatMatrix *B, int *eigenVector);
	double* creatRandomVector(double* b0, int size);
	int checkDifference(double *vector1, double *vector2, int size, double eps);
	double calcDotProduct(double *vector1, double *vector2, int size);
	void divide(double *vector1, double norm, int size);

	/*doDivisionByS.c */
	int doDivisionByS(graph *group, int *s, stack *divisionToTwo);
	void updateNodesGroups(int originalSize, spmat *matrix, int *s);

	/*createGraphFromFile.c*/
	graph createGraph(char *name_of_input_file);

	/*computeS.c*/
	int createSVector(double *eigenVector, int size);

/*
 * --------Functions Implementation---------
 */

/* ----------------------------------computeDQ---------------------------------------------------------------*/


	int sumAd (graph *G, int *s,int index)
	{
		spmat *relate_matrix = G -> relate_matrix;
		int sum = 0;
		linkedList* indexRow;
		linkedList_node* currNode;

		indexRow = *((relate_matrix -> private)+ index);
		currNode = indexRow -> head;
		while(currNode!=NULL)
		{
			if (currNode -> partByS == *(s + index))
			{
				sum += *(s + (currNode -> value));
			}
			currNode = currNode -> next;
		}
		return sum;
	}

	double sumDd (BHatMatrix *B, int *s, int index)
	{
		int i, sum=0, counter=0;
		int *listNodes= B->G->graph_nodes, *degrees=B->G->degrees;
		double d;
		d=B->constM*(*(degrees+index));
		for (i=0;i<B->originalSize;i++)
		{
			if (i==*listNodes)
			{
				sum+= *(degrees+i) * (*(s + i));
				counter++;
				listNodes++;
			}
			if (counter == (B->G)->n)
				break;
		}
		return sum*d;
	}


	/*
	 * Returns delta Q: (0.5) * s^T * Bhat * s
	 */
	double computeDQ(double *s, BHatMatrix *B)
	{
		double dq;
		int size = (B->G)->n;
		double *result;

		result=(double*)malloc(sizeof(double)*size);

		B->multBHat(B,s,result);
		dq=calcDotProduct(size, s,result);

		free(result);
		return dq*(0.5);
	}

	/*
	 * Returns a new delta Q, after a change in a single index in the vector s.
	 */
	double computeDQChange(int *s ,BHatMatrix *B, int index)
	{

		int partA;
		double partB, partC;

		partA = 4 * (*(s + index));
		partC = 4 * pow(*(B -> G -> degrees + index), 2) * (B -> constM);
		partB = sumAd (B -> G, s, index) - sumDd (B, s, index);

		return partA * partB + partC;

	}


/* ----------------------------------findEigen---------------------------------------------------------------*/



	/*eigen vector is pre - initaliize
	 * function returns eigenValue and sets value into eigenvector
	 */
	double findEigenValue(BHatMatrix *B, int *eigenVector)
	{

		/*Variables Deceleration*/
		int i = 0 , ifGreatThenEps = 1, matrixSize;
		double *tmp, *result;
		double vector_norm, epsilon = 0.00001, eigenValue;
		clock_t start, end;

		srand(time(NULL));
		start = clock();

		matrixSize = (B -> G)-> n;

		/*Creating Initial Random Vector*/
		if(eigenVector == NULL)
		{
			printf("Initial vector allocation failed");
			exit(0);
		}
		creatRandomVector(eigenVector, matrixSize);

		/*Perform power iteration to obtain the eigenvector
		 * Running the algorithm of power iteration
		 */

		while(ifGreatThenEps)
		{

			result = (double*) malloc(sizeof(double)*(matrixSize));

			/*Calculating (result = ^B[g] * b_k).
			 *  The shifting of the matrix happens in multBHat*/
			B -> multBHat(B, eigenVector ,result);

			/*calculating the vector's magnitude*/
			vector_norm = sqrt(calcDotProduct(result, result, matrixSize));

			/*Calculating the corresponding dominant eigenvalue
			 *
			 *     (Ab_k)*(b_k)
			 * â = --------------
			 *     b_k * b_ k
			 *
			 */
			eigenValue = (calcDotProduct(result, eigenVector, matrixSize) /
					calcDotProduct(eigenVector,eigenVector, matrixSize));


			/*normalizing the vector*/
			if(vector_norm != 0.0)
			{
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

		/*need to be eigen value - Bnorm */
		return eigenValue - (B->matrixNorm);
	}

	double* creatRandomVector(double* b0, int size)
	{
		int i;
		for(i = 0; i < size; i++)
		{
			*b0 = rand();
			b0++;
		}
		return b0;
	}

	/*To Delete */
//	void print(int size, double *row){
//		int i;
//		double k;
//		for(i= 0; i < size; i++){
//			k = *(row +i);
//			printf("curent row is : %f\n", k);
//		}
//
//	}


	/*Divide
	 * The function receives a vector,
	 * and normalize it by dividing it in it's size
	 */
	void divide(double *vector1, double norm, int size)
	{
		double *p = vector1;
		int i = 0;
		for(; i < size; i++)
		{
			*p = (double) (*p) / norm;
			p += 1;
		}
	}

	/*calcDotProduct
	 * The function calculated product between two vectors
	 */
	double calcDotProduct(double *vector1, double *vector2, int size)
	{
		double *firstPointer = vector1, *secondPointer = vector2;
		double product = 0.0;
		int i = 0;
		for(; i < size; i++)
		{
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
	int checkDifference(double *vector1, double *vector2, int size, double eps)
	{
		double *p1 = vector1, *p2 = vector2;
		int i;
		double diff;
		for(i = 0; i < size; i++)
		{
			diff = *p1 - *p2;
			if(fabs(diff) >= eps)
				return 1;
			p1 += 1;
			p2 += 1;
		}
		return 0;
	}


/* ----------------------------------doDivisionByS---------------------------------------------------------------*/


	int doDivisionByS(graph *group, int *s, stack *divisionToTwo)
	{
		graph *group1, *group2;
		int *curr_nodes = group -> graph_nodes;
		int  *graph_nodes1, *graph_nodes2;
		int n = group -> n, n1 = 0, n2 = 0, i = 0;


		/*Finding the sizes of the two new groups */
		for(; i < n; i++)
		{
			if(*s == 1)
			{
				n1++;
			}
			else
			{
				n2++;
			}
			s++;
		}
		s -= n;

		/* Checking sizes before building the groups*/
		if(n1 == 0 || n2 == 0)
		{
			group1 = group;
			*group2 = NULL;
			divisionToTwo -> push(group1, divisionToTwo);
			divisionToTwo -> push(group2, divisionToTwo);
			return 0;
		}


		/*Allocating new list of nodes for each group*/
		graph_nodes1 = (int*) malloc(sizeof(int) * (n1));
		graph_nodes2 = (int*) malloc(sizeof(int) * (n2));

		/*Updating the new lists of nodes for each group*/
		for(i = 0; i < n; i++)
		{
			if(*s == 1)
			{
				*graph_nodes1 = *curr_nodes;
				graph_nodes1++;
			}
			else
			{
				*graph_nodes2 = *curr_nodes;
				graph_nodes2++;
			}
			s++;
			curr_nodes++;
		}

		graph_nodes1 -= n1;
		graph_nodes2 -= n2;


		/*Updating the relation matrix of each group */
		updateNodesGroups(n, group->relate_matrix, s);

		/*Allocating new graph representing each new group */
		group1 = allocate_graph(n1, graph_nodes1, group->relate_matrix);
		group1 -> divisionNumber = 1;
		group2 = allocate_graph(n2, graph_nodes2, group->relate_matrix);
		group2 -> divisionNumber = -1;

		/*Adding division (two graph) to the input stack */
		divisionToTwo -> push(group1, divisionToTwo);
		divisionToTwo -> push(group2, divisionToTwo);

		/*Free only original graph without the nodes, and without the related matrix inside lists */
		free_graph(group, 0);

		return 0;
	}


	/* The function "createRelateMatrix"
	 	 The function creates the new relation matrix, according to input data.
	 */
	void updateNodesGroups(int originalSize, spmat *matrix, int *s)
	{
		linkedList **rows;
		linkedList *currList;
		linkedList_node *currNode;
		int i = 0, j = 0, curr_index;

		rows = matrix -> private;
		for(; i < originalSize; i++)
		{
			currList = **rows;
			currNode=currList->head;
			while (currNode!=NULL)
			{
				currNode->partByS =*(s+(currNode->value));
				currNode=currNode->next;
			}
			rows++;
		}
	}

/* ----------------------------------createGraphFromFile---------------------------------------------------------------*/


	graph *createGraph(char *name_of_input_file){

		/*Variables deceleration*/
		FILE	*input_file;
		graph *input_graph;
		int *nodes_list;
		int *curr_neighbors, *matrix_row, *degrees;
		spmat *relate_matrix;
		int n, m = 0, degree, j, neighboor_index, i = 0;
		int succ;

		/*File Reading into variable, and asserting the process was successful.
		 * if not - exiting the program.*/
		input_file =  fopen(name_of_input_file, 'rb');
		if(input_file == NULL){
			exit("The file is not valid");
		}

		/*Reading number of nodes in the graph*/
		succ = fread(&n, sizeof(int), 1, input_file);
		if(succ != 1){
			exit("The file is empty");
		}

		/*Initializing list size n, of pointers to the nodes of the graph*/
		nodes_list = (int *) malloc(sizeof(int) * (n));

		/*Assert allocation*/
		if(nodes_list == NULL){
				exit("Allocation of nodes list failed");
		}

		/*Initialize Nodes list*/
		for(j = 0; j < n; j++ ){
			/*Allocate returns node*/
			*nodes_list = j;
			nodes_list++;
		}
		nodes_list -= n;

		/*Allocating space to sparse matrix */
		relate_matrix = spmat_allocate_list(n);

		degrees = (int *) malloc(sizeof(int) * (n));
		if(degrees == NULL){
			exit("Allocation of degrees vector failed");
		}

		/*Reading File:
		 *      Reading the input matrix (one row at a time).
		 *      For each row, adding it to the sparse matrix
		 */

		 while( !feof(input_file) ) {

			 /*Read file row : k1 and the indices */
			 succ = fread(&degree, sizeof(int), 1, input_file);
			 if(succ != 1){
			 	exit("Failed degree reading");
			 }
			 *degrees = degree;
			 degrees++;

			 /*Read the neighbors indices into row*/
			 matrix_row =  (int*) malloc(sizeof(int)*(degree));
			 if(matrix_row == NULL){
			 		exit("Allocation failed");
			 }

			 succ =  fread(matrix_row, sizeof(int), degree, input_file);
			 if(succ != degree){
				exit("Failed file read");
			}

			 relate_matrix -> add_row(relate_matrix, matrix_row, degree, i);
			 free(matrix_row);
			 i++;


		 }


		fclose(input_file);


		/*Graph building*/
		input_graph = allocate_graph(n, nodes_list, relate_matrix);
		input_graph -> degrees = degrees;

		return input_graph;

	}

/* ----------------------------------computeS---------------------------------------------------------------*/


	int *createSVector(double *eigenVector, int size){
		int *s;
		int i = 0;


		for(; i < size; i++){
			if(*eigenVector > 0){
				*s = 1;
			}
			else {
				*s = -1;
			}
			eigenVector++;
			s++;
		}
		return s;

	}


