
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "../structures/graph.h"
#include "../structures/BHatMatrix.h"
#include "../structures/stack.h"

/*computeDQ.c*/
int sumAd (graph *G, int *s,int index);
double sumDd (BHatMatrix *B, int *s, int index);
double computeDQ(int *s, BHatMatrix *B);
double computeDQChange(int *s ,BHatMatrix *B, int index);

/*findEigen.c*/
double calcDotProduct(double *vector1, double *vector2, int size);
double findEigenValue(BHatMatrix *B, double *eigenVector);
double* creatRandomVector(double* b0, int size);
int checkDifference(double *vector1, double *vector2, int size, double eps);
void divide(double *vector1, double norm, int size);

/*doDivisionByS.c */
int doDivisionByS(graph *group, int *s, stack *divisionToTwo);
void updateNodesGroup(int originalSize, spmat *matrix, int *s);

/*createGraphFromFile.c*/
graph *createGraph(FILE *);

/*computeS.c*/
int *computeS(double *eigenVector, int size);


#endif

