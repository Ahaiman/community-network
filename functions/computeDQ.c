/*
 * computeDQ.c
 *
 *  Created on: 18 баев 2020
 *      Author: OR
 */

#include "functions.h"
#include "./functions/functions.h" /*necessary for calcDotProduct in computeDQ*/
#include "./structures/linkedList.h"

/*
 * --------Functions Definition---------
 */
double computeDQ(double*, BHatMatrix*);
double computeDQChange(double*, BHatMatrix*, int, int);

/*
 * --------Implementation---------
 */



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
		if (currNode -> index == *(s + index)){
			sum += *(s + (currNode -> value));
		}
		currNode = currNode -> next;
	}
	return sum;
}

double sumDd (BHatMatrix *B, int *s, int index)
{
	int i, sum=0, counter=0;
	int *listNodes=B->G->nodesList, *degrees=B->G->degrees;
	double d;
	d=B->constM*(*(degrees+index));
	for (i=0;i<B->originalSize;i++)
	{
		if (i==*nodesList)
		{
			sum+= *(degrees+i) * (*(s + i));
			counter++;
			nodesList++;
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
	partC = 4 * pow(*(B -> G -> degrees) + index), 2) * (B -> constM);
	partB = sumAd (B -> G, s, index) - sumDd (B, s, index);

	return partA * partB + partC;

}
