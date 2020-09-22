
/* algorithm2.h - Header File
 *
 * An algorithm for finding an initial devision.
 *
 * Our goal is to find a vector "s", that represents a division of graph G, that maximizes the modularity Q.
 * To divide a group, we look at the additional change, DQ, to the modularity.
 *
 * We obtain the leading eigen-vector of B^[g], i.e., the eigen-vector of B^[g] with the largest eigenvalue.
 * Then, vertices whose corresponding elements are positive go in one group, and the rest of the vertices go in the other.
 *
 * Division of G into two groups (s) is a vector of {+1,-1} where for each vertex i:
 * s[i] = +1 if it belongs to the first group, and s[i] = -1 if it belongs to the second.
 *
 * The algorithm is called from algorithm3, and modifies the input "s" vector according to the algorithm's steps.
 */

#ifndef ALGORITHM2_H_
#define ALGORITHM2_H_

#include "graph.h"
#include "BHatMatrix.h"

/* ------------------------------------- Main Algorithm -------------------------------------- */

/* Divide a graph into two.
 * If the eigen-value calculated during the algorithm is negative (< EPSILON),
 * the "out" indicator holds "-1" for "no division".
 * In any other case, the algorithm calculates the division and represents it with the values {-1,1} in s.
 *
 * @param BHatMatrix        - a pointer to the current B-Hat matrix.
 * @param graph             - a pointer to the current group.
 * @param vector of doubles - a pointer to the division vector.
 * @param integer pointer   - an indicator to the existence of a possible division.
 */
void 			divisionGraphToTwo(BHatMatrix*, graph*, double*, int*);

/* ----------------------------------- F Vector Calculation ----------------------------------- */

/* Computing and updating the F vector corresponding to the B[g] matrix.
 * The function calculates the vector, for each group created after the division.
 *
 * @param BHatMatrix - a pointer to the current B-Hat matrix.
 * @param graph      - a pointer to the current group.
 */

void 			calcFVector(BHatMatrix*, graph*);

/* --------------------------------- Eigen - Pair Calculation --------------------------------- */

/* Computing the leading eigen-pair of a diagonalizable matrix B^[g] using power iteration.
 * Power iteration uses matrix-vector multiplications to find the dominant eigen-vector,
 * the eigen-vector with the largest absolute eigenvalue.
 * In order to find the dominant eigen-vector, we use matrix shifting.
 *
 * We perform the algorithm on B^[g] shifted matrix.
 * The function returns the eigen-vector of the shifted matrix,
 * and updates the eigen-value pointer to the eigen-value of the shifted matrix minus the matrix norm.
 *
 * @param BHatMatrix          - a pointer to the current B-Hat matrix.
 * @param graph               - a pointer to the current group.
 * @param pointer to a double - a pointer to the eigen value.
 *
 * @return the matrix B^[g] dominant eigen vector
 */

double* 		findEigenValue(BHatMatrix*, graph*, double*);

/*
 * The function sets random values to an input vector, according to a given graph.
 *
 * @param vector of doubles - pre allocated empty vector
 * @param graph             - a pointer to the current group
 */

void 			creatRandomVector(double*, graph*);

/*
 * The function calculates the dot product between the degrees vector and another vector.
 *
 * @param graph              - a pointer to the current group
 * @param vector of integers - the original graph degrees vector
 * @param vector of doubles  - a vector to perform the dot product calculation with
 *
 * @return dot product result
 */

double 			calcDotProductInt(graph*, int*, double*);

/*
 * The function calculates the dot product between two vectors.
 *
 * @param graph             - a pointer to the current group
 * @param vector of doubles - a vector to perform the dot product calculation with
 * @param vector of doubles - a vector to perform the dot product calculation with
 *
 * @return dot product result
 */

double 			calcDotProduct(graph*, double*, double*);

/*
 * The function checks if all the differences between each corresponding pair of values in the previous vector and another one
 * are smaller than epsilon (0.00001)
 *
 * @param graph             - a pointer to the current group
 * @param vector of doubles - a vector for the difference check
 * @param vector of doubles - another vector for the difference check
 * @param double 			- a macro representing the epsilon value
 *
 * @return 1 if the difference between the vectors isn't small enough, 0 otherwise
 */

int				checkDifference(graph*, double*, double*, double);

/*
 * The function normalizes a given vector, by dividing its values by its norm
 *
 * @param graph             - a pointer to the current group
 * @param vector of doubles - a vector to normalize
 * @param double 			- the given vector's norm
 */

void 			divideByNorm(graph*, double*, double);

/* ----------------------------------- S Vector Calculation ----------------------------------- */

/*
 * The function sets the values in a given s vector to {-1,+1} according to the positivity (>EPSILON)
 * of the values in the corresponding places in a provided eigen-vector
 *
 * @param vector of doubles - an eigen-vector
 * @param graph             - a pointer to the current group
 * @param vector of doubles - the division vector
 */

void 			computeS(double*, graph*, double*);

/*
 * The function creates a trivial division.
 * If DQ<0 -> there is no division and the algorithm sets "s" to its initial values from the beginning of the algorithm.
 *
 * @param graph             - a pointer to the current group
 * @param vector of doubles - the division vector
 */

void 			createTrivialS(graph*, double*);

/* ----------------------------------- DQ Value Calculation ----------------------------------- */

/*
 * The function computes the DQ value according to the formula: (0.5) * (s^T) * B^[g] * s
 * DQ represents the difference in the modularity value of the given group.
 *
 * @param vector of doubles - the division vector
 * @param graph             - a pointer to the current group
 * @param BHatMatrix        - a pointer to the current B-Hat matrix.
 */

double 			computeDQ(double*, graph*, BHatMatrix*);

#endif
