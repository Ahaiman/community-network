
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "../structures/graph.h"
#include "../structures/BHatMatrix.h"
#include "../structures/stack.h"

/*computeDQ.c*/
int sumAd (graph *G, int *s,int index);
double sumDd (BHatMatrix *B, int *s, int index);
double computeDQ(double *s, BHatMatrix *B);
double computeDQChange(int *s ,BHatMatrix *B, int index);

/*findEigen.c*/
double calcDotProduct(double *vector1, double *vector2, int size);
double findEigenValue(BHatMatrix *B, int *eigenVector);
double* creatRandomVector(double* b0, int size);
int checkDifference(double *vector1, double *vector2, int size, double eps);
void divide(double *vector1, double norm, int size);

/*doDivisionByS.c */
void doDivisionByS(graph *group, int *s, stack *divisionToTwo);
void updateNodesGroup(int originalSize, spmat *matrix, int *s);

/*createGraphFromFile.c*/
graph *createGraph(char *name_of_input_file);

/*computeS.c*/
int *createSVector(double *eigenVector, int size);


#endif

