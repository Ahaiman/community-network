
#include "./structures/linkedList"

 void algorithm4(BHatMatrix *B, int *s, int dQ){
	 int i = 0, j, n = (B -> G) -> n;
	 int max_place, max_i, placeInS;
	 double Q0, max = 0, maxImprove = 0;
	 linkedList *unmoved;
	 linkedList_node *curr;
	 int *score, *indices, *improve;

	 /*Avital: to implement in linkedlist.c
	  * creats a list of all the indices value 0..Ng and a index of the place in s*/
	 unmoved - > allocateWithNodes(unmoved, n);

	 score = (int *)malloc(n * sizeof(int));
	 indices = (int *)malloc(n * sizeof(int));
	 improve = (int *)malloc(n * sizeof(int));

	 curr = unmoved -> head;

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

			 //6 : runining over the unmoved linked list
			 while(curr != NULL){
				 placeInS = curr -> index;

				 *(s + placeInS) *= -1;
				 /*replace : computeDQ(s, B) */
				 score[placeInS] =  computeDQMohamad(s, B) - Q0;
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
			dQ = improve[max_i]
		}

 }










