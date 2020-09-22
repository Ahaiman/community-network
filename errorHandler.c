
/*
 * errorHandler.c - Source File
 * Implementation of the functions declared in the header file
 */

#include <stdlib.h>
#include <stdio.h>
#include "errorHandler.h"

char* errorsMessage[] = {
		"No such file or directory",
		"B matrix structure allocation failed",
		"Sparse matrix structure allocation failed",
		"Vector allocation failed",
		"Eigen vector allocation failed",
		"File reading failed",
		"Division by 0",
		"Linked list structure allocation failed",
		"Linked list node structure allocation failed",
		"Stack structure allocation failed",
		"Stack element structure allocation failed"
		};

void returnErrorByType(int errorNumber)
{
	char *message = errorsMessage[errorNumber];
	printf("ERROR! %s\n", message);
	exit(EXIT_FAILURE);
}
