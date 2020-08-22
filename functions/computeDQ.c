/*
 * computeDQ.c
 *
 *  Created on: 18 баев 2020
 *      Author: OR
 */

#include "functions.h"
#include "./functions/functions.h" /*necessary for calcDorProduct in computeDQ*/
#include "./structures/linkedList.h"

/*
 * --------Functions Definition---------
 */
double computeDQ(double*, BHatMatrix*);
double computeDQChange(double*, BHatMatrix*, int, int);

/*
 * --------Implementation---------
 */

/*
 * Returns delta Q: (0.5) * s^T * Bhat * s
 */
double computeDQ(double *s, BHatMatrix *B)
{
	double dq;
	int size;
	double *Ag_s, *degVec, *fsVec, *result;

	size=(B->G)->n;
	Ag_s=(double*)malloc(sizeof(double)*size);
	degVec=(double*)malloc(sizeof(double)*size);
	fsVec=(double*)malloc(sizeof(double)*size);
	result=(double*)malloc(sizeof(double)*size);

	multFirstThreeVecs(B, s, Ag_s, degVec, fsVec);

	//calculating Bg_hat * s , and the output is in "result" vector
	MultBMatAndVector(size, Ag_s, degVec, fsVec, result);

	//calculating s^T * result
	dq=calcDotProduct(size, s, result);

	free(Ag_s);
	free(degVec);
	free(fsVec);
	free(result);
	return dq*(0.5);
}


/*
 * Returns a new delta Q, after a change in a single index in the vector s.
 */
//we need to provide M!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
double computeDQChange(double *s, BHatMatrix *B, int index, int dq)
{
	double dqChange, bjj;
	linked_list_node *currNode;
	int indexDegree, sum=0, i=0;
	indexDegree=(B->G)->degrees[index];
	currNode=(((B->G)->relate_matrix)->private[index])->head;

	//calculating Bjj: we assume that Ajj=0. Therefore Bjj=0-((j_dgree)**2/M)
	bjj=(pow(indexDegree,2)*(-1))/M;

	//calculating the sum of column #index.
	while (currNode!=NULL)
	{
		sum+=(currNode->value*(*(s+i)));
		currNode=currNode->next;
		i++;
	}

	dqChange=dq-4*(*(s+index))*sunRowS+4*bjj;
	return dqChange;
}
/*


/*returns a double, multiplies a row vector and a column vector. */
/*
double RowVecMultColVec(int size, double *row, double *col)
{
	int i;
	double res=0;
	for (i=0;i<size;i++)
	{
		res+=((*row)*(*col));
		row++;
		col++;
	}
	return res;
}
*/
