
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "graph.h"


double (*RowVecMultColVec)(int size, double *row, double *col);
double (*computeDQ)(double *s, BHatMatrix *B);
int *createSVector(double *eigenVector, int size
graph *createGraph(char *name_of_input_file){
double* creatRandomVector(double* b0, int size);
void print(int size, double *row);
void divideByNorm(double *vector1, double norm, int size);
double calcDotProduct(double *vector1, double *vector2, int size);
int checkDifference(double *vector1, double *vector2, int size, double eps);
void multNumVec(int size, double num, double *vec, double *res);
void multTwoVecs(int size, double *fVector, double *eigenVector, double *res);
void findEigen_MultResult(int size, double *A_g_eigenVector, double *degVec, double *fbVec, double *Bnorm_eigenVector, double *result);
void SubtractTwoVectors(int size, double *vec1, double *vec2);
void AddTwoVectors(int size, double *vec1, double *vec2);
double findEigenValue(BHatMatrix *B, int *eigenVector);


#endif

