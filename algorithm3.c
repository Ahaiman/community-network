/*
 * algorithm3.c - Source File
 * Implementation of the functions declared in the header file
 */

#include <stdio.h>
#include <stdlib.h>

#include "algorithm2.h"
#include "algorithm3.h"
#include "algorithm4.h"

#include "graph.h"
#include "BHatMatrix.h"
#include "stack.h"
#include "errorHandler.h"
#include "spmat.h"

/* --------Functions Deceleration--------- */

void			findCommunities(graph*,spmat*, int*, char*);
void			divisionByS(graph*, double*, stack*,int);
int*			createGraph(FILE*, graph*, spmat*);

/* --------Functions Implementation---------*/

void findCommunities(graph *G, spmat *matrix, int * degrees, char *output_name)
{
	FILE *output_file;
	stack *P, *O, *divisionToTwo;
	graph *group, *group1, *group2, *outputGroup;
	BHatMatrix *B;
	int *outputNodes;
	double *s;
	int first = 1, succ, out = 0, graphIsOneClique = 0;

	/*Initializing the stacks*/
	O = initialize();
	P = initialize();
	divisionToTwo = initialize();

	/*Creating the division vector*/
	s =  (double *)malloc(sizeof(double) * G -> n);
	if(s == NULL) returnErrorByType(4);

	/*(1) Start with a trivial division into one group: all the nodes in the graph*/
	push(G, P);

	/*(2) Creating the B matrix*/
	B = createMatrixBHat(G, matrix, degrees);

	/*(3) Repeat until P is empty*/
	while(!empty(P))
	{
		/* 3.1) Remove a group from P*/
		group = pop(P);

		/* 3.2) Divide g into g1, g2 with Algorithm 2 */
		divisionGraphToTwo(B, group,s, &out);

		/* If the eigen-value is positive, perform algorithm 4 (even if dQ <= EPSILON)*/
		if(out != -1) algorithm4(B, group, s);

		/*Creating the division, according to the updated vector "s"*/
		divisionByS(group, s, divisionToTwo, first);

		/*Indicates it's not the first devision*/
		first = 0;

		/*Update the new two groups after the devision*/
		group1 = pop(divisionToTwo);
		group2 = pop(divisionToTwo);

		/* 3.3) If either g1 or g2 is of size 0: Add g to O*/
		if(group1  == NULL || group2 == NULL) {
			if(group1 != NULL)
				push(group1, O);
			else
				push(group2, O);
		}

		/* 3.4) Add to O: any group (g1 and/or g2) of size 1
		 * 		Add to P: any group (g1 and/or g2) of size larger than 1 */
		else {
			if(group1 != NULL)
			{
				if(group1 -> n == 1)
					push(group1, O);
				else
					push(group1, P);
			}
			if(group2 != NULL)
			{
				if(group2 -> n == 1)
					push(group2, O);
				else
					push(group2, P);
			}
		}
	}
	/* 4) Output the division given by O: write to the output file*/
	output_file = fopen(output_name, "wb");

	/* 4.1) The first value represents the number of groups in the division*/
	succ = fwrite(&(O ->cnt), sizeof(int), 1, output_file);
	if(succ !=  1) returnErrorByType(6);

	/*Checking if the original graph is a clique - for further memory release considerations*/
	if(O -> cnt == 1) graphIsOneClique = 1;

	while(!empty(O)) {
		outputGroup = pop(O);
		outputNodes = outputGroup -> graph_nodes;

		/* 4.2) The number of nodes in the current group*/
		succ = fwrite(&(outputGroup -> n), sizeof(int), 1, output_file);
		if(succ !=  1) returnErrorByType(6);

		/* 4.3) The following indices of the nodes in the group in increasing order*/
		succ = fwrite(outputNodes, sizeof(int), outputGroup -> n, output_file);
		if(succ !=  outputGroup -> n ) returnErrorByType(4);

		/*After writing the group, free the structure*/
		outputGroup -> free_graph(outputGroup);
	}

	fclose(output_file);

	B -> freeBHat(B, graphIsOneClique);
	free(s);
	free(O);
	free(P);
	free(divisionToTwo);
}

void divisionByS(graph *group, double *s, stack *divisionToTwo, int first)
{
	graph *group1, *group2;
	int *curr_nodes = group -> graph_nodes;
	int  *graph_nodes1, *graph_nodes2;
	int n = group -> n, n1 = 0, n2 = 0, i = 0, currNodeValue;
	double currValueInS;

	/*Finding the sizes of the two new groups*/
	for(; i < n; i++)
	{
		currValueInS = *(s + *curr_nodes);
		if(currValueInS == 1)
			n1++;
		else
			n2++;
		curr_nodes++;
	}
	curr_nodes-= n;

	/*Checking sizes before building the groups*/
	if(n1 == 0 || n2 == 0)
	{
		group1 = group;
		group2 = NULL;
		push(group1, divisionToTwo);
		push(group2, divisionToTwo);
		return;
	}

	/*Allocating new lists of nodes for each group*/
	graph_nodes1 = (int*) malloc(sizeof(int) * n1);
	if(graph_nodes1 == NULL) returnErrorByType(4);

	graph_nodes2 = (int*) malloc(sizeof(int) * n2);
	if(graph_nodes2 == NULL) returnErrorByType(4);

	/*Allocating new graphs for each group*/
	group1 = (graph*) malloc(sizeof(graph));
	if(group1 == NULL) returnErrorByType(1);

	group2 = (graph*) malloc(sizeof(graph));
	if(group2 == NULL) returnErrorByType(1);

	/*Updating the new lists of nodes for each group*/
	for(i = 0; i < n; i++)
	{
		currNodeValue = *curr_nodes;
		currValueInS = *(s + currNodeValue);

		if(currValueInS == 1)
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

	graph_nodes1 -= n1;
	graph_nodes2 -= n2;

	/*Allocating a new graph representing each new group*/
	allocate_graph(group1, n1, graph_nodes1);
	allocate_graph(group2, n2, graph_nodes2);

	/*Adding the division (the two new graphs) to the input stack*/
	push(group1, divisionToTwo);
	push(group2, divisionToTwo);

	/*Free every divided graph, except for the original graph*/
	if(!first)
		group -> free_graph(group);
}

int *createGraph(FILE *input_file, graph *input_graph, spmat *relate_matrix)
{
	/*Variables deceleration*/
	int *nodes_list, *matrix_row, *degrees;
	int n, degree, i = 0, succ;

	/*Reading the number of nodes in the graph*/
	succ = fread(&n, sizeof(int), 1, input_file);
	if(succ != 1) returnErrorByType(6);

	/*Initializing the list of the graph's nodes*/
	nodes_list = (int *) malloc(sizeof(int) * n);
	if(nodes_list == NULL) returnErrorByType(4);

	/*Initializing the list of the graph nodes's degrees*/
	degrees = (int *) malloc(sizeof(int) * n);
	if(degrees == NULL) returnErrorByType(4);

	/*Allocating a sparse matrix*/
	spmat_allocate_list(relate_matrix , n);

	/*Reading File:
	 *      Reading the input matrix (one row at a time).
	 *      For each row, adding it to the sparse matrix
	 */
	while( i < n && !feof(input_file) )
	{
		/*Setting values to the nodes*/
		*nodes_list = i;
		nodes_list++;

		/*Reading a file row: degrees and the node's neighbors */
		succ = fread(&degree, sizeof(int), 1, input_file);
		if(succ != 1) returnErrorByType(6);

		/*Updating the degrees vector*/
		*degrees = degree;
		degrees++;

		/*Reading the neighbors indices into the matrix row*/
		matrix_row =  (int*) malloc(sizeof(int) * degree);
		if(matrix_row == NULL) returnErrorByType(4);

		succ =  fread(matrix_row, sizeof(int), degree, input_file);
		if(succ != degree) returnErrorByType(6);

		/*Adding the matrix row to the sparse matrix*/
		relate_matrix -> add_row(relate_matrix, matrix_row, degree, i);
		free(matrix_row);
		i++;
	}
	fclose(input_file);

	nodes_list -= n;
	degrees -= n;

	/*Graph structure allocating and initializing*/
	allocate_graph(input_graph, n, nodes_list);
	return degrees;
}
