
/*
 * algorithm4.c - Source File
 * Implementation of the functions declared in the header file
 */

#define POSITIVE(X) ((X) > 0.00001)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "algorithm4.h"
#include "graph.h"
#include "BHatMatrix.h"
#include "errorHandler.h"

/* --------Functions Deceleration--------- */

void			algorithm4(BHatMatrix*, graph*, double*);
void     	    nullifyVector(int*, int);

/* --------Functions Implementation---------*/

void algorithm4(BHatMatrix *B,graph *G, double *s)
{
	/*Variables deceleration*/
	int i, j, n, maxScoreIteration = 0, maxImproveIteration = 0, lastMovedIndex, currDeg, currNodeValue;
	int *nodes, *indices, *unmoved;
	double maxScore, maxImprove, currScoreValue, dQ, improve, valueInDMatrix;
	double *score, *Bg_s;

	n = G -> n;
	nodes = G -> graph_nodes;
	dQ = 0;

	/*Initializing vectors */
	score = (double *)malloc(n * sizeof(double));
	if(score == NULL) returnErrorByType(4);

	indices = (int *)malloc(n * sizeof(int));
	if(indices == NULL) returnErrorByType(4);

	Bg_s = (double *)malloc(n * sizeof(double));
	if(Bg_s == NULL) returnErrorByType(4);

	unmoved = (int *)malloc(n * sizeof(int));
	if(unmoved == NULL) returnErrorByType(4);

	/*Iterating until no further improvement is found*/
	do {
		/*Setting (-inf) initial value to maxImprove variable*/
		maxImprove = -HUGE_VAL;

		/*Nullifying the unmoved list*/
		nullifyVector(unmoved, n);

		/*Trying to find an improvement of the current partition defined by s*/
		for(i = 0; i < n; i++) {

			/*Computing DQ for the move of each unmoved vertex*/
			maxScore = -HUGE_VAL;

			/*Setting initial values to the score array, only in the first iteration (i == 0)*/
			if(i == 0)
			{
				/*Performing multiplication of B[g] * s */
				BgMult(B, G, s, Bg_s);

				/*Initializing values to the score array, according to B[g] * s vector*/
				for(j = 0; j < n; j++)
				{
					currNodeValue = *nodes;
					currDeg = *(B -> degrees + currNodeValue);
					valueInDMatrix = B -> constM * currDeg * currDeg;

					/*Calculating the following: score[j] = -2 * (s[j] * Bg_s[j] + D[j][j])*/
					currScoreValue = -2 * (*(s + currNodeValue) * (*Bg_s) + valueInDMatrix);
					*score = currScoreValue;

					/*Finding the maximum score, and the corresponding node index*/
					if(currScoreValue > maxScore){
						maxScore = currScoreValue;
						maxScoreIteration = j;
					}
					score++;
					nodes++;
					Bg_s++;
				}
				score -= n;
				nodes -= n;
				Bg_s -= n;
			}
			else
			{
				/*Updating the score array*/
				for (j = 0; j < n; j++) {
					if (*unmoved == 0) {
						currNodeValue = *(nodes + j);

						/* Calculating the following:
						 * k is the index of the last moved node.
						 * score[j] = score[j] - 4 * (s[j] * s[k] * B_g[j][k])*/
						currScoreValue = *score - 4 * ( *(s + currNodeValue) * (*(s + *(nodes + lastMovedIndex))) *
										calcBgPlace(B, currNodeValue, *(nodes + lastMovedIndex)));

						*score = currScoreValue;

						/*Finding the maximum score, and the corresponding node index*/
						if(currScoreValue > maxScore) {
							maxScore = currScoreValue;
							maxScoreIteration = j;
						}
					}
					score++;
					unmoved++;
				}
				score -= n;
				unmoved -= n;
			}

			/*Moving the vertex corresponding to the maximal score*/
			*(s + *(nodes + maxScoreIteration)) *= -1;

			/*Updating the indices array, according to the previous node*/
			*(indices + i) = maxScoreIteration;

			/*Updating the last moved index*/
			lastMovedIndex = maxScoreIteration;

			/*Marking the maxScoreIteration node as moved*/
			*(unmoved + maxScoreIteration) = 1;

			/*Updating the current improvement*/
			improve = i == 0 ? maxScore : improve + maxScore;

			/*Updating the maximal improvement in the algorithm*/
			if(improve > maxImprove) {
				maxImprove =  improve;
				maxImproveIteration = i;
			}
		}

		/*Updating the "s" vector representing the current division, according to the indices array*/
		for(i = n - 1; i > maxImproveIteration; i--)
			*(s + *(nodes + *(indices + i))) *= -1;

		/*Updating the DQ value according to the current iteration*/
		dQ = maxImproveIteration == n - 1 ? 0 : maxImprove;

	} while(POSITIVE(dQ));

	/*Frees all the allocated vectors*/
	free(unmoved);
	free(Bg_s);
	free(score);
	free(indices);
}

void nullifyVector(int *unmoved, int n){
	int i;
	for(i = 0; i <n; i++)
	{
		*unmoved = 0;
		unmoved++;
	}
}
