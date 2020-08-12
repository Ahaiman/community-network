/*
 * computeS.c
 *
 *  Created on: 12 баев„ 2020
 *      Author: Avital
 */


int *createSVector(double *eigenVector, int size){
	int *s;
	int i = 0;

	s = (int *) malloc (sizeof(int) * size);

	for(; i < size; i++){
		if(*eigenVector > 0){
			*s = 1;
		}
		else {
			*s = -1;
		}
		eigenVector++;
		s++;
	}
	return s;

}
