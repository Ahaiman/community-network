
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../structures/graph.h"
#include "../structures/spmat.h"
#include "../structures/BHatMatrix.h"
#include "../structures/linkedList.h"
#include "../structures/stack.h"
#include "../functions/functions.h"
#include "./algorithm.h"



/*
 * --------Functions Deceleration---------
 */
	/*algo_2.c*/

	double divisionGraphToTwo(graph *group, stack *division, int *s);

	/*algo_4.c*/
	void algorithm4(graph *G, int *s, double dQ);

	/*algo_3.c*/
	void findCommunities(graph *G, char *name_of_output_file);

/*
 * --------Functions Implementation---------
 */

/* ----------------------------------algo2---------------------------------------------------------------*/

	double divisionGraphToTwo(graph *group, stack *division, int *s)
	{

		BHatMatrix *B_g;
		double eigenValue, dQ;
		double *eigenVector;

		B_g = createMatrixBHat(group);

		/*Compute leading eigenpair u1 and b1 of the modularity matrix b B[g] */
		eigenVector = (double *) malloc (sizeof(double) * (group -> n));
		eigenValue = findEigenValue(B_g, eigenVector);

		//if (b1 <= 0): The network is indivisible
		if(eigenValue <= 0)
		{
			printf("not possible");
			return NULL;
		}

		//compute s
		 s = computeS(eigenVector,group -> n);

		 dQ = computeDQ(s, B_g);

		 //if (s^T b B[g]s <= 0): The network is indivisible
		 if( dQ <= 0)
		 {
			 printf("not possible");
			 return NULL;
		 }

		 return dQ;
	}


/* ----------------------------------algo3---------------------------------------------------------------*/


	/*AFTER 24/8 WITH MOSHE :
	 * Note we need to count iteration to recongince cases of infinity loops.
	 * do several tries on different sizes, and do maximum loops; if it more than that -> error
	 * inifint loop -> powet iteraion for exapmle -> do exit it's an error.
	 * put an counte for loops- > check what need to be the maximim limit
	 */

	void findCommunities(graph *G, char *name_of_output_file)
	{
		FILE	*output_file;
		stack *P, *O, *divisionToTwo;
		graph *group, *group1, *group2;
		int *s;
		int n = G -> n;
		double dQ;


		initialize(O);
		initialize(P);
		initialize(divisionToTwo);
		s = (int *) malloc (sizeof(int) * n);
		output_file =  fopen(name_of_output_file, "wb");

		//	1.Start with a trivial division into one group: the all nodes in the graph
		P -> push(G, P);

		while(!empty(P))
		{
			group = P -> pop(P);

			/* 1) Divide g into g1; g2 with Algorithm 2 */
			dQ  = divisionGraphToTwo(group,divisionToTwo, s);



			/*2)Even if the division in trivial (one group full, and another empty)
			 * Impemant optimization - */
			algorithm4(group, s, dQ);

			 /*Creating the division*/
			 doDivisionByS(group, divisionToTwo, s);

			 group1 = divisionToTwo -> pop(divisionToTwo);
			 group2 = divisionToTwo -> pop(divisionToTwo);

			/* 3) if either g1 or g2 is of size 0: Add g to O*/
			if(group1  == NULL || group2 == NULL )
			{
				O -> push(group, O);
			}

			/*4) Add to O: any group (g1 and/or g2) of size 1*/
			if(group1 -> n == 1)
			{
				O -> push(group1, O);
			}
			else
			{
				P -> push(group1, P);
			}

			if(group2 -> n == 1)
			{
				O -> push(group2, O);
			}
			else
			{
				P -> push(group2, P);
			}
		}
	}

		/*Write to output file */

/* ----------------------------------algo4---------------------------------------------------------------*/



		 void algorithm4(graph *G, int *s, double dQ)
		 {
			 BHatMatrix *B;
			 int i = 0, j, n = (B -> G) -> n;
			 int max_place, max_i, placeInS;
			 double Q0, max = 0, maxImprove = 0, *score;
			 linkedList *unmoved;
			 linkedList_node *curr;
			 int *indices, *improve;

			 B = createMatrixBHat(G);

			 unmoved = allocateListWithNodes(n); // == 0 -> 1 -> 2 -> ,,, -> ng

			 score = (double *)malloc(n * sizeof(double));
			 indices = (int *)malloc(n * sizeof(int));
			 improve = (int *)malloc(n * sizeof(int));

			//1 : Repeat
			 while(dQ > 0)
			 {

				 //3
				 for(; i < n; i++)
				 {
					 if(i == 0)
					 {
						 Q0 = dQ;
					 }
					 else
					 {
						 Q0 = computeDQ(s, B);
					 }

					 curr = unmoved -> head;
					 //6 : running over the unmoved linked list
					 while(curr != NULL)
					 {
						 placeInS = curr -> value;

						 *(s + placeInS) *= -1;
						 score[placeInS] =  computeDQChange(s , B, placeInS);
						 *(s + placeInS) *= -1;

						 if(score[placeInS] > max)
						 {
							 max = score[placeInS];
							 max_place = placeInS; //k = curr -> index
						 }
						 curr ++;
					 }
					 //11
					 *(s + max_place) *= -1;
					 indices[i] = max_place;
					 if(i == 0)
					 {
						 /*improve[i] = score[max_place]*/
						 improve[i] = max;
					 }
					 else
					 {
						 /*improve[i] = improve[i-1] - score[max_place]*/
						 improve[i] = improve[i-1] + max;
					 }
					 if(improve[i] > maxImprove)
					 {
						 maxImprove = improve[i];
						 max_i = i;
					 }
					 delete_node(unmoved, max_place);
				 }

				 //22
				for(i = n - 1; i > max_i + 1; i--)
				{
					j = indices[i];
					*(s + j) *= -1;
				}

				//26
				if(max_i == n - 1)
				{
					dQ = 0;
				}
				else
				{
					dQ = improve[max_i];
				}
			 }
		 }
