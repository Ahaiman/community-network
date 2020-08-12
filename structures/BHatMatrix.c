 * BHatMatrix.c
 *
 *  Created on: 12 баев„ 2020
 *      Author: Avital
 */



double (**createMatrixBHat)(double *degrees, spmat *A, spmat *F, double *b_k){
	/*implenet*/
}


void (*free)(struct __BHatMatrix *B){
	free(B - > degrees);
	spmat_free(B - > A);
	spmat_free( B -> F);
}
