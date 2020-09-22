#define POSITIVE(X) ((X) > 0.00001)


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
	double divisionGraphToTwo(BHatMatrix *B, graph *group, stack *division, double *s);

	/*algo_4.c*/
	void algorithm4(BHatMatrix *B,graph *G, double *s);

	/*algo_3.c*/
	void findCommunities(graph *G, spmat *matrix, int * degrees, char *output_name);


/*
 * --------Functions Implementation---------
 */

/* ----------------------------------algo2---------------------------------------------------------------*/

	double divisionGraphToTwo(BHatMatrix *B, graph *group, stack *division, double *s)

	{

		double eigenValue, dQ;
		double *eigenVector;
		int i = 0;


		calcFVector(B, group);

		/*Compute leading eigenpair u1 and b1 of the modularity matrix b B[g] */
		eigenVector = findEigenValue(B, group, &eigenValue);


		if(!POSITIVE(eigenValue))
		{
			printf("%s eigen is %f", "not possible", eigenValue);
			exit(EXIT_FAILURE);
		}


		computeS(eigenVector, group, s);

		dQ = computeDQ(s,group, B);

		return dQ;
	}


/* ----------------------------------algo3---------------------------------------------------------------*/


	/*AFTER 24/8 WITH MOSHE :
	 * Note we need to count iteration to recongince cases of infinity loops.
	 * do several tries on different sizes, and do maximum loops; if it more than that -> error
	 * inifint loop -> powet iteraion for exapmle -> do exit it's an error.
	 * put an counte for loops- > check what need to be the maximim limit
	 */

	void findCommunities(graph *G, spmat *matrix, int * degrees, char *output_name)

	{
		FILE *output_file;
		stack *P, *O, *divisionToTwo;
		graph *group, *group1, *group2, *output;
		BHatMatrix *B;
		int *outputNodes, currNode;
		double *s = (double *)malloc(sizeof(double) * G -> n);
		int i = 0, first = 1, succ;
		double dQ;
		int second=1;

		//delete
		double b;
		int k, t;
		int bbb = -1;
		 double b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13, b14, b15, b16, b17, b18, b19;

		O = initialize();
		P = initialize();
		divisionToTwo = initialize();


		//	1.Start with a trivial division into one group: the all nodes in the graph
		push(G, P);

		B = createMatrixBHat(G, matrix, degrees);
//		constM = B -> constM;


		while(!empty(P))
		{
			group = pop(P);
			 for(i = 0; i < group -> n ; i++)
				t = *(group -> graph_nodes + i);


			dQ = divisionGraphToTwo(B, group, divisionToTwo, s);

			b0=*(s);
			b1=*(s+1);
			b2=*(s+2);
			b3=*(s+3);
			b4=*(s+4);
			b5=*(s+5);
			b6=*(s+6);
			b7=*(s+7);
			b8=*(s+8);
			b9=*(s+9);
			b10=*(s+10);
			b11=*(s+11);
			b12=*(s+12);
			b13=*(s+13);
			b14=*(s+14);
			b15=*(s+15);
			b16=*(s+16);
			b17=*(s+17);
			b18=*(s+18);
			b19=*(s+19);

			algorithm4(B, group, s);

			b0=*(s);
			b1=*(s+1);
			b2=*(s+2);
			b3=*(s+3);
			b4=*(s+4);
			b5=*(s+5);
			b6=*(s+6);
			b7=*(s+7);
			b8=*(s+8);
			b9=*(s+9);
			b10=*(s+10);
			b11=*(s+11);
			b12=*(s+12);
			b13=*(s+13);
			b14=*(s+14);
			b15=*(s+15);
			b16=*(s+16);
			b17=*(s+17);
			b18=*(s+18);
			b19=*(s+19);


			 /*Creating the division*/
			 divisionByS(B->relate_matrix, group, s, divisionToTwo, first);

			 first = 0;

			 group1 = pop(divisionToTwo);
			 group2 = pop(divisionToTwo);

			/* 3) if either g1 or g2 is of size 0: Add g to O*/
			if(group1  == NULL || group2 == NULL )
			{
				push(group, O);
			}

			/*4) Add to O: any group (g1 and/or g2) of size 1*/
			else{
				if(group1 != NULL){
					if(group1 -> n == 1)
						push(group1, O);
					else
						push(group1, P);
				}
				if(group2 != NULL){
					if(group2 -> n == 1)
						push(group2, O);
					else
						push(group2, P);
				}
			}
		}
		output_file = fopen(output_name, "wb");

		/*Output the division given by O : Write to output file */
		while(!empty(O)){
			output = pop(O);
			outputNodes = output -> graph_nodes;
			succ = fwrite(outputNodes, sizeof(int), output -> n, output_file);
			if(succ !=  output -> n ){
				printf("error in writing into file");
				exit(EXIT_FAILURE);
			}
			//to delete
			fwrite(&bbb, sizeof(int), 1, output_file);
		}
		fclose(output_file);
	}


/* ----------------------------------algo4---------------------------------------------------------------*/



		 void algorithm4(BHatMatrix *B,graph *G, double *s)
		 {
			 /*Q0 ??? */
//			 BHatMatrix *B;


			 int i = 0, j, n = G -> n, originalSize = B -> originalSize;
			 int max_place, max_i, placeInS;
			 double max = 0, maxImprove, currdQChange, dQ = 0;
			 double *score, *improve, *improve_i;
			 linkedList *unmoved;
			 linkedList_node *curr, *prev, *keepMax;
			 int *indices;
			 int first = 1;

			 double Q0;
			 //todelete
			 double b, m, t;
			 int mone=0;


			 //delte
			 for(i = 0; i < n ; i++)
				 t = *(G -> graph_nodes + i);
//			 unmoved = allocateListWithNodes(G, n); // == -1 - > 0 -> 1 -> 2 -> ,,, -> ng

			 score = (double *)malloc(originalSize * sizeof(double));
			 indices = (int *)malloc(originalSize * sizeof(int));
			 improve = (double *)malloc(originalSize * sizeof(double));

			//1 : Repeat
			 do{

				 mone++;
				 unmoved = allocateListWithNodes(G, n);

				 for(i = 0; i < n; i++)
				 {
					 //Q0=computeDQ(s,G,B);
					 prev = unmoved -> head;
					 curr = unmoved -> head -> next;
					 //6 : running over the unmoved linked list
					 while(curr != NULL)
					 {

						 placeInS = curr -> value;

						 *(s + placeInS) *= -1;
						 currdQChange =  computeDQChange(B, G, s, placeInS);
						 //currdQChange=computeDQ(s, G, B)-Q0;
						 //
						 *(score + placeInS) = currdQChange;
						 *(s + placeInS) *= -1;

						 if(first || currdQChange > max)
						 {
							 max = currdQChange;
							 max_place = placeInS; //k = curr -> index
							 keepMax = prev;
							 first = 0;
						 }
						 prev = curr;
						 curr = curr -> next;
					 }
					 //11
					 *(s + max_place) *= -1;
					 *(indices + i) = max_place;
					 improve_i = improve + i;

					 if(i == 0)
					 {
						 /*improve[i] = score[max_place]*/
						 *(improve_i) = max;
					 }
					 else
					 {
						 /*improve[i] = improve[i-1] - score[max_place]*/
						 *(improve_i) =  *(improve_i - 1)+ max;
					 }
					 if(i == 0 || *(improve_i) > maxImprove)
					 {
						 maxImprove =  *(improve_i);
						 max_i = i;
					 }
					 delete_node(unmoved, keepMax);
					 first = 1;
					 if(unmoved -> size == 0){
						 free(unmoved -> head);
//						 free(unmoved);
					 }
				 }

				 //22
				for(i = n - 1; i > max_i; i--)
				{
					j = *(indices + i);
					*(s + j) *= -1;
				}

				//26
				if(max_i == n - 1)
				{
					dQ = 0;
				}
				else
				{
					dQ = *(improve + max_i);
				}
//				delete_node(unmoved, unmoved -> head);
			 } while(POSITIVE(dQ) && mone<10000);

			 //todelte
			 for(i = 0; i < 20; i++){
				 b= *(s+i);
			 }
			free(score);
			free(indices);
			free(improve);
		 }
