
#include "./structures/linkedList"
#include "./structures/BHatMatrix.h"
#include "./function/function.h"


 void algorithm4(Graph *G, int *s, int dQ){
	 BHatMatrix *B;
	 int i = 0, j, n = (B -> G) -> n;
	 int max_place, max_i, placeInS;
	 double Q0, max = 0, maxImprove = 0, *score;
	 linkedList *unmoved;
	 linkedList_node *curr;
	 int *indices, *improve;


	 B = createMatrixBHat(G);

	 unmoved - > allocateWithNodes(unmoved, n); // == 0 -> 1 -> 2 -> ,,, -> ng

	 score = (double *)malloc(n * sizeof(double));
	 indices = (int *)malloc(n * sizeof(int));
	 improve = (int *)malloc(n * sizeof(int));



	//1 : Repeat
	 while(dQ > 0) {

		 //3
		 for(; i < n; i++)
		 {
			 if(i == 0){
				 Q0 = dQ;
			 }
			 else{
				 Q0 = computeDQ(s, B);
			 }

			 curr = unmoved -> head;
			 //6 : runining over the unmoved linked list
			 while(curr != NULL){
				 placeInS = curr -> index;

				 *(s + placeInS) *= -1;
				 score[placeInS] =  computeDQChange(s, B, placeInS, dQ) - Q0;
				 *(s + placeInS) *= -1;

				 if(score[placeInS] > max){
					 max = score[placeInS];
					 max_place = placeInS; //k = curr -> index
				 	 }
				 curr ++;
			 }
			 //11
			 *(s + max_place) *= -1;
			 indices[i] = max_place;
			 if(i == 0){
				 /*improve[i] = score[max_place]*/
				 improve[i] = max;
			 }
			 else{
				 /*improve[i] = improve[i-1] - score[max_place]*/
				 improve[i] = improve[i-1] + max;
			 	 }
			 if(improve[i] > maxImprove){
				 maxImprove = improve[i];
				 max_i = i;
			 }
			 unmoved -> delete_node(unmoved, max_place);
		 }

		 //22
		for(i = n - 1; i > max_i + 1; i--){
			j = indices[i];
			*(s + j) *= -1;
		}

		//26
		if(max_i == n - 1){
			dQ = 0;
		}
		else{
			dQ = improve[max_i];
		}

 }










