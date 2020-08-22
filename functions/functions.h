
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "./structures/graph.h"
#include "./structures/stack.h"
#include "./structures/BHatMatrix.h""

/*computeDQ.c*/
double (*computeDQ)(double *s, BHatMatrix *B);
double (*computeDQChange)(double *s, BHatMatrix *B, int index, int dq);

/*findEigen.c*/
double (*calcDotProduct)(double *vector1, double *vector2, int size);
double (*findEigenValue)(BHatMatrix *B, int *eigenVector);

/*doDivisionByS.c */
void (*doDivisionByS)(graph *group, int *s, stack *divisionToTwo);

/*createGraphFromFile.c*/
graph (*createGraph)(char *name_of_input_file);

/*computeS.c*/
int (*createSVector)(double *eigenVector, int size);

/*BHatMatrix.c*/
void (*calcFirstThreeVecs)(BHatMatrix *B, double *eigenVector ,double *Ag_eigenVector, double *degVec, double *fbVec);
void (*subtractFirstThreeVecs)(int size, double *A_g_eigenVector, double *degVec, double *fbVec, double *result);





#endif

