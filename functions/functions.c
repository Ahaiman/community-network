#define EPSILON 0.00001

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
	double sumDd (BHatMatrix *B, graph *group, double *s, int index);
	//int sumAd (BHatMatrix *B, double *s,int index);
	int sumAd (BHatMatrix *B, graph *group, double *s,int index);


	/*double computeDQ(int *s, BHatMatrix *B);*/
	double computeDQ(double *s,graph *group, BHatMatrix *B);
	double computeDQChange(BHatMatrix *B, graph *group,double *s, int placeInS);


	/*findEigen.c*/
	double* findEigenValue(BHatMatrix *B, graph *group, double *eigenValue);
	void creatRandomVector(double* b0, int size);
	int checkDifference(graph *g, double *vector1, double *vector2, double eps);
	double calcDotProduct(graph *g, double *vector1, double *vector2);
	double calcDotProductInt(graph *g, int *vector1, double *vector2);
	void divideByNorm(graph *group, double *vector1, double norm);
	void spmat_mult(BHatMatrix *B, graph *group, const double *v, double *result);


	/*doDivisionByS.c */
	void divisionByS(spmat *relate_matrix, graph *group, double *s, stack *divisionToTwo, int first);
//	void updateNodesGroups(int originalSize, spmat *matrix, double *s);

	/*createGraphFromFile.c*/
	int *createGraph(FILE *, graph *,spmat *);

	/*computeS.c*/
	void computeS(double *eigenVector, graph *group, double *s);

	void calcFVector(BHatMatrix *B, graph *group);


	/*To delte*/
	double* creatRandomVector1(double* b0, int size);


/*
 * --------Functions Implementation---------
 */

/* ----------------------------------computeDQ---------------------------------------------------------------*/

	int sumAd (BHatMatrix *B, graph *group, double *s,int index)
	{
		linkedList** private;
		linkedList* indexRow;
		linkedList_node* currNode;
		int *nodes=group->graph_nodes;
		int graphNode;
		int sum = 0, counter=0;



		private = (linkedList **)((B -> relate_matrix) -> private);
		indexRow=*(private + index);


		currNode = indexRow -> head;
		while(currNode!=NULL && counter < group->n)
		{
			graphNode=*nodes;
			if (currNode->value==graphNode)
			{

				sum += *(s + (currNode -> value));
				currNode = currNode -> next;
				nodes++;
				counter++;
			}
			else
			{
				if(currNode->value > graphNode)
				{
					nodes++;
					counter++;
				}
				else
					currNode = currNode -> next;
			}
		}
		return sum;
	}


	double sumDd (BHatMatrix *B, graph *group, double *s, int index)
	{
		int i, sum=0, graphNode;
		int *listNodes= group->graph_nodes, *degrees= B->degrees;
		double d;
		int currGroup;

		d = (B -> constM) *(*(degrees+index)); //k_i
		currGroup = *(s + index);

		for (i=0; i < group->n ;i++)
		{
			graphNode=*(listNodes+i);
			sum += *(degrees + graphNode) * (*(s + graphNode));
		}
		return sum * d;
	}
	/*
	 * Returns delta Q: (0.5) * s^T * Bhat * s
	 */
	double computeDQ(double *s,graph *group, BHatMatrix *B)
	{
		double dq;
		int size = B -> originalSize;
		double *result;

		result=(double*)calloc(size, sizeof(double));

		B -> multBHat(B, group,s, result,0);
		dq = calcDotProduct(group, s,result);

		free(result);
		return dq;
	}

	/*
	 * Returns a new delta Q, after a change in a single index in the vector s.
	 */
	double computeDQChange(BHatMatrix *B, graph *group,double *s, int index)

	{

		double partA, partB, partC, result;

		partA = 4 * (*(s + index));
		partC = 4 * pow(*(B -> degrees + index), 2) * B -> constM;
		partB = sumAd (B, group, s, index) - sumDd (B, group, s, index);

		result =  partA * partB + partC;
		return result;

	}


/* ----------------------------------findEigen---------------------------------------------------------------*/



	/*eigen vector is pre - initaliize
	 * function returns eigenValue and sets value into eigenvector
	 */
	double* findEigenValue(BHatMatrix *B,graph *group, double *eigenValue)
	{

		/*Variables Deceleration*/
		int ifGreatThenEps = 1, matrixSize;
		double *eigenVector, *tmp, *result;


		//delete
		int i, k;
		double l, t;
		double b;


		double vector_norm, epsilon = 0.00001;

		matrixSize = B -> originalSize;

		eigenVector = (double *) calloc(matrixSize , sizeof(double));
		/*Creating Initial Random Vector*/
		if(eigenVector == NULL)
		{
			printf("Initial vector allocation failed");
			exit(EXIT_FAILURE);
		}

		creatRandomVector(eigenVector, matrixSize);

		/*Perform power iteration to obtain the eigenvector
		 * Running the algorithm of power iteration
		 */

		result = (double *) calloc(matrixSize, sizeof(double));

		while(ifGreatThenEps)
		{
			B -> multBHat(B, group, eigenVector ,result, 1);

//			*eigenValue = calcDotProduct(group, result, eigenVector);

			/*calculating the vector's magnitude*/
			b = calcDotProduct(group, result, result);
			vector_norm = sqrt(b);

			if(vector_norm <= EPSILON)
			{
				exit(EXIT_FAILURE);
			}


			/*normalizing the vector*/
			divideByNorm(group, result, vector_norm);

			/*Checking if the difference between vectors is smaller then epsilon*/
			ifGreatThenEps = checkDifference(group, eigenVector, result, epsilon);

			/*Swapping information between variables to continue the algorithm
			 * b_k = b_k1*/

			tmp = eigenVector;
			eigenVector = result;
			result = tmp;
		}

		B -> multBHat(B, group, eigenVector ,result, 1);


		*eigenValue -= (B -> matrixNorm);

		free(tmp);

		return eigenVector;
	}

	void creatRandomVector(double* b0, int size)
	{
		int i;
		for(i = 0; i < size; i++)
		{
			*b0 = rand();
			b0++;
		}
	}

	/*To delete*/
	double* creatRandomVector1(double* b0, int size)
		{
			int i;
			for(i = 1; i < size + 1 ; i++)
			{
				*b0 = i ;
				b0++;
			}
			return b0;
		}

	/*To Delete */
	void print(int size, int *row)
	{
		int i;
		int k;
		for(i= 0; i < size; i++)
		{
			k = *(row +i);
			printf("current row is : %d\n", k);
		}
	}


	/*Divide
	 * The function receives a vector,
	 * and normalize it by dividing it in it's size
	 */
	void divideByNorm(graph *group, double *vector1, double norm)
	{
		int i = 0;
		int *nodes = group -> graph_nodes;

		double b;

		for(; i < group -> n; i++)
		{
			b = *(vector1 + *nodes) / norm;
			*(vector1 + *nodes) = b;
			nodes++;
		}
	}

	/*calcDotProduct
	 * The function calculated product between two vectors
	 */
	double calcDotProduct(graph *group, double *vector1, double *vector2)
	{
		double product = 0.0;
		int *nodes = group -> graph_nodes;
		int i = 0;

		for(; i < group -> n; i++)
		{
			product += (*(vector1 + *nodes)) * (*(vector2 + *nodes));
			nodes++;
		}
		return product;
	}



	double calcDotProductInt(graph *group, int *degrees, double *vector)
	{

		double product = 0.0;
		int *nodes = group -> graph_nodes;
		int i = 0, currDeg;
		for(; i < group -> n; i++)
		{
			currDeg = *(degrees + *nodes);
			product += currDeg * (*(vector + *nodes));
			nodes++;
		}
		return product;
	}

	/*checkDifference
	 * The function return "true" if the difference between to vectors
	 * is greater then epsilon. "false" otherwise.
	 */
	int checkDifference(graph *group, double *vector1, double *vector2, double eps)
	{
		int *nodes = group -> graph_nodes;
		int i;
		double diff;
		for(i = 0; i < group -> n; i++)
		{
			diff = *(vector1 + *nodes) - *(vector2 + *nodes);
			if(abs(diff) >= eps)
				return 1;
			nodes++;
		}
		return 0;
	}


/* ----------------------------------divisionByS---------------------------------------------------------------*/


	void divisionByS(spmat *relate_matrix, graph *group, double *s, stack *divisionToTwo, int first)
	{
		graph *group1, *group2;
		int *curr_nodes = group -> graph_nodes;
		int  *graph_nodes1, *graph_nodes2;
		int n = group -> n, n1 = 0, n2 = 0, i = 0, currPlace;
		double currNode;


		/*Finding the sizes of the two new groups */
		for(; i < n; i++)
		{
			currPlace = *(s + *curr_nodes);
			if(currPlace == 1)
			{
				n1++;
			}
			else
			{
				n2++;
			}
			curr_nodes++;
		}
		curr_nodes-= n;

		/* Checking sizes before building the groups*/
		if(n1 == 0 || n2 == 0)
		{
			group1 = group;
			group2 = NULL;
			push(group1, divisionToTwo);
			push(group2, divisionToTwo);
			return;
		}


		/*Allocating new list of nodes for each group*/
		graph_nodes1 = (int*) malloc(sizeof(int) * (n1));
		graph_nodes2 = (int*) malloc(sizeof(int) * (n2));

		/*Allocating new graphs for each group*/
		group1 = (graph*) malloc(sizeof(graph));
		group2 = (graph*) malloc(sizeof(graph));

		/*Updating the new lists of nodes for each group*/
		for(i = 0; i < n; i++)
		{
			currPlace = *curr_nodes;
			currNode = *(s + currPlace);
			if(currNode == 1)
			{
				*graph_nodes1 = *curr_nodes;
				graph_nodes1++;
			}
			else
			{
				*graph_nodes2 = *curr_nodes;
				graph_nodes2++;
			}

			curr_nodes++;
		}

//		s-= n;
		curr_nodes -= n;
		graph_nodes1 -= n1;
		graph_nodes2 -= n2;


		/*Updating the relation matrix of each group */
//		updateNodesGroups(n, relate_matrix, s);

		/*Allocating new graph representing each new group */
		allocate_graph(group1, n1, graph_nodes1);
		group1 -> divisionNumber = 1;
//		group1 -> degrees = (group -> degrees);
		allocate_graph(group2, n2, graph_nodes2);
		group2 -> divisionNumber = -1;
//		group2 -> degrees = (group -> degrees);

		/*Adding division (two graph) to the input stack */
		push(group1, divisionToTwo);
		push(group2, divisionToTwo);

		/*Free only original graph without the nodes, and without the related matrix inside lists */
//		//ToDo: free only after the first time
		if(!first)
			group -> free_graph(group);

	}


	/* The function "createRelateMatrix"
	 	 The function creates the new relation matrix, according to input data.
	 */
//	void updateNodesGroups(int originalSize, spmat *matrix, double *s)
//	{
//		linkedList **rows;
//		linkedList *currList;
//		linkedList_node *currNode;
//		int i = 0;//, curr_index;
//
//		rows = matrix -> private;
//		for(; i < originalSize; i++)
//		{
//			currList = *rows;
//			currNode=currList->head;
//			while (currNode!=NULL)
//			{
//				currNode->partByS =*(s+(currNode->value));
//				currNode=currNode->next;
//			}
//			rows++;
//		}
//	}

/* ----------------------------------createGraphFromFile---------------------------------------------------------------*/


	int *createGraph(FILE *input_file, graph *input_graph, spmat *relate_matrix)
	{

		/*Variables deceleration*/


		int *nodes_list;
		int *matrix_row, *degrees;
//		spmat *relate_matrix;
		int n, degree, j,i = 0, succ;

		//deelte
		int a;



		/*Reading number of nodes in the graph*/
		succ = fread(&n, sizeof(int), 1, input_file);
		if(succ != 1)
		{
			printf("The file is empty");
			exit(EXIT_FAILURE);
		}

		/*Initializing list size n, of pointers to the nodes of the graph*/
		nodes_list = (int *) malloc(sizeof(int) * (n));

		/*Initializing list size n, of pointers to the degrees of the graph*/
		degrees = (int *) malloc(sizeof(int) * (n));

		/*Assert allocation*/
		if(nodes_list == NULL)
		{
			printf("Allocation of nodes list failed");
			exit(EXIT_FAILURE);
		}

		/*Initialize Nodes list*/
		for(j = 0; j < n; j++ )
		{
			/*Allocate returns node*/
			*nodes_list = j;
			nodes_list++;
		}
		nodes_list -= n;

		/*Allocating space to sparse matrix */

		spmat_allocate_list(relate_matrix , n);

		degrees = (int *)malloc (sizeof(int) * (n));
		if(degrees == NULL)
		{
			printf("Allocation of degrees vector failed");
			exit(EXIT_FAILURE);
		}

		/*Reading File:
		 *      Reading the input matrix (one row at a time).
		 *      For each row, adding it to the sparse matrix
		 */

		 while( i < n && !feof(input_file) )
		 {
			 /*Read file row : k1 and the indices */
			 succ = fread(&degree, sizeof(int), 1, input_file);
			 if(succ != 1)
			 {
			 	printf("Failed degree reading");
			 	exit(EXIT_FAILURE);
			 }
			 *degrees = degree;
			 degrees++;

			 /*Read the neighbors indices into row*/
			 matrix_row =  (int*) malloc(sizeof(int)*(degree));
			 if(matrix_row == NULL)
			 {
			 		printf("Allocation failed");
			 		exit(EXIT_FAILURE);
			 }

			 succ =  fread(matrix_row, sizeof(int), degree, input_file);
//			 printf("index is %d and degree is %d\n", i, degree);
//			print(degree, matrix_row);

			 if(succ != degree)
			 {
				printf("Failed file read");
				exit(EXIT_FAILURE);
			 }

			 relate_matrix -> add_row(relate_matrix, matrix_row, degree, i);
			 free(matrix_row);
			 i++;
		 }
		fclose(input_file);

		degrees -= n;
//		for(i = 0; i < n; i++){
//			a = *(degrees + i);
//		}

		/*Graph building*/
		allocate_graph(input_graph, n, nodes_list);
//		degrees = createDegrees;
//		matrix = relate_matrix;

		return degrees;

	}

/* ----------------------------------computeS---------------------------------------------------------------*/

	void computeS(double *eigenVector,  graph *group, double *s)
	{

		int i = 0;
		int *nodes = group -> graph_nodes;
		for(; i < group -> n; i++)
		{

			if(*(eigenVector + *nodes) > 0)
				*(s + *nodes) = 1;
			else
				*(s + *nodes) = -1;
			nodes++;
		}

	}


/* ----------------------------------mult_list---------------------------------------------------------------*/

	void spmat_mult(BHatMatrix *B, graph *group, const double *v, double *result)
	{
		/*must get original size - vector = resukt */
	    linkedList_node *currNode;
	    spmat *A = B -> relate_matrix;
	    int *nodes = group -> graph_nodes, *run = nodes;
	    int originalSize = B -> originalSize;
	    linkedList *currList, **rows_indices = A->private;


	    int row, counter = 0, keepRow;
	    double sum;


	    if(result == NULL)
	    {
			printf("result is not allocated");
			exit(0);
	    }


	    for(row = 0; row < group -> n; row++)
	    {
	    	currList = *(rows_indices + *nodes);
	        currNode = currList -> head;
	        sum = 0;
	        counter = 0;
	        while (currNode != NULL && counter < group -> n)
	        {
	        	if(currNode -> value == *run){
	        		sum += *(v + currNode -> value);
	        		currNode = currNode->next;
	        		counter++;
	        		run++;
	        	}
	        	else{
	        		if(currNode -> value < *run )
	        			currNode = currNode->next;
	        		else{
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
	/* ----------------------------------calcFVector---------------------------------------------------------------*/


	void calcFVector(BHatMatrix *B, graph *group){
		double *f_vector = B -> f_vector;
		int *nodes = group -> graph_nodes;
		int i = 0, currIndex;

		//dele
		double a, b,c;
		//
		for(;i < group -> n; i++){
			currIndex = *(nodes + i);
			a = sumRowsA(B-> relate_matrix, group, currIndex);
			b = sumRowsD(group,B, currIndex);
			c = a-b;
			if(c < EPSILON && c > 0)
				c = 0;

			*(f_vector + currIndex)  = a-b;
		}
	}
