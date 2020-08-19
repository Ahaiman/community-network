/*
 * computeDQ.c
 *
 *  Created on: 18 баев 2020
 *      Author: OR
 */

#include "functions.h"

/*returns a double, multiplies a row vector and a column vector*/
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

/*returns a double - delta Q*/
double computeDQ(double *s, BHatMatrix *B){
	double dq;
	int size;
	double *res, *Ag_s;
	size=(B->G)->n;
	res=(double*)malloc(sizeof(double)*size);
	Ag_s=(double*)malloc(sizeof(double)*size);

	/*    calculating A_g*s    */
	((B->G)->relate_matrix)->spmat_mult((B->G)->relate_matrix, s, Ag_s);

	/*   calculating: (0.5) * s^T * B_g_hat * s. returns a number    */

		/*   calculating: B_g_hat * s and the output is a vector - res    */
		MultBMatAndVector(size, Ag_s, B->degrees, B->f_vector, res);

		/*   calculating: s^T * res. returns a number    */
		dq=RowVecMultColVec(size, s, res);

	free(res);
	free(Ag_s);
	return dq*(0.5);
}
