
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <math.h>
#include "../structures/graph.h"
#include "../structures/BHatMatrix.h"
#include "../structures/stack.h"

/*computeDQ.c*/
int sumAd (BHatMatrix *B, graph *group, double *s,int index);
double sumDd (BHatMatrix *B, graph *group, double *s, int index);
double computeDQ(double *s,graph *group, BHatMatrix *B);
double computeDQChange(BHatMatrix *B, graph *group,double *s, int placeInS);


/*findEigen.c*/
double calcDotProduct(graph *g, double *vector1, double *vector2);
double calcDotProductInt(graph *g, int *vector1, double *vector2);
double* findEigenValue(BHatMatrix *B, graph *group, double *eigenValue);
void creatRandomVector(double* b0, int size);
int checkDifference(graph *g, double *vector1, double *vector2, double eps);
void divideByNorm(graph *group, double *vector1, double norm);

/* Multiplies matrix A by vector v, into result (result is pre-allocated) */
void spmat_mult(BHatMatrix *B, graph *group, const double *v, double *result);

/*doDivisionByS.c */
void divisionByS(spmat *relate_matrix, graph *group, double *s, stack *divisionToTwo, int first);

/*createGraphFromFile.c*/
int *createGraph(FILE *, graph *,spmat *);

/*computeS.c*/
void computeS(double *eigenVector, graph *group, double *s);

void calcFVector(BHatMatrix *B, graph *group);

#endif

