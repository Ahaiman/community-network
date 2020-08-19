/*
 * computeS.c
 *
 *  Created on: 12 баев„ 2020
 *      Author: Avital
 */

#include "functions.h"

int *createSVector(double *eigenVector, int size){
	int *s;
	int i = 0;


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
