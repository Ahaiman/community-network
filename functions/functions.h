
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "./structures/graph.h"
#include "./structures/stack.h"
#include "./structures/BHatMatrix.h""

/*computeDQ.c*/
double (*computeDQ)(double *s, BHatMatrix *B);

/*findEigen.c*/
double (*calcDotProduct)(double *vector1, double *vector2, int size);
double (*findEigenValue)(BHatMatrix *B, int *eigenVector);

/*doDivisionByS.c */
void (*doDivisionByS)(Graph *group, int *s, stack *divisionToTwo);

/*createGraphFromFile.c*/
graph (*createGraph)(char *name_of_input_file);

/*compueS.c*/
int (*createSVector)(double *eigenVector, int size);

/*?????????*/
void multNumVec(int size, double num, double *vec, double *res);
void multTwoVecs(int size, double *fVector, double *eigenVector, double *res);
void findEigen_MultResult(int size, double *A_g_eigenVector, double *degVec, double *fbVec, double *Bnorm_eigenVector, double *result);
void SubtractTwoVectors(int size, double *vec1, double *vec2);
void AddTwoVectors(int size, double *vec1, double *vec2);
double findEigenValue(BHatMatrix *B, int *eigenVector);




#endif

