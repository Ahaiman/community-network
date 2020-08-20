


 void algorithm4(BHatMatrix *B, int *s, int dQ){
	 int i = 0, j, n = (B -> G) -> n, max_k;
	 double Q0, max = 0;

	 int *unmoved = (int *)malloc(n * sizeof(int));
	 int *score = (int *)malloc(n * sizeof(int));
	 int *indices = (int *)malloc(n * sizeof(int));
	 int *improve = (int *)malloc(n * sizeof(int));

	 for(; i < n; i++){
		 *unmoved = i;
	 }

	 for(; i < n; i++)
	 {
		 for(j = 0; j < n; j++){
			 Q0 = dQ;

			 for (k = 0; ){
				 *(s + k) = -1;
				 score[k] = computeDQ(s, B) - Q0;
				 *(s + k) = -1;
				 if(score[k] > max){
					 max = score[k];
					 max_k = k; //k = j`
				 }
			 }

			 s[max_index] *= -1;
			 indices[i] = max_index;
			 if(i == 0){
				 improve[i] = score[max_index];
			 }
			 else{
				 improve[i] = improve[i-1] - score[max_index];
			 }
			 unmoved.remove(max_index);////change)
			 //Max = 0?
		 }



	 }


 }
