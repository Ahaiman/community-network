/*
 * BHatMatrix.h - Header File
 *
 * An implementation of a B matrix according to the project's definition,
 * but in order to save place, we do not keep it in the memory.
 *
 * We use two matrices in order to perform operations on the B matrix:
 *                          B = A - D
 * A is the adjacency matrix of the graph, and D is the degrees matrix as described in the project.
 * Both the matrices refer to the original input graph, so they are calculated only once in the program.
 *
 * A - is represented by a sparse matrix.
 * D - is represented by the degrees vector we keep as a field, and a constant value -  1/M (constM).
 * D[i][j] = (1/M) * degrees[i] * degrees[j]
 *
 * If a function uses B^[g] (and not the original B) we modify the implementation according to the current g group.
 * With the nodes list field inside the graph structure, we can use the original B matrix,
 * but refer only to the relevant data (only to the places that are connected to the current nodes in the graph).
 *
 * B-Hat matrix contains the following fields:
 * 			"originalGraph" - the original input graph received by the user
 *			"relate_matrix" - a sparse matrix representing the adjacency matrix of the original graph
 *			"degrees" 		- a vector containing the degrees of the vertices of the original graph
 *			"constM" 		- a constant calculated by the formula: 1/(sum of degrees in the original graph)
 *			"originalSize" 	- the number of vertices in the original graph
 *			"matrixNorm" 	- the 1-norm of the largest column in B matrix
 *							  (largest according to each column 1-norm calculation)
 *			"f_vector" 		- a vector containing the sums of the rows in B matrix
 *
 * freeBHat - frees the B-Hat structure and its inner fields
 * multBHat - multiplies B-Hat matrix (shifted, if needed) with a given vector
 */

#ifndef BHATMATRIX_H_
#define BHATMATRIX_H_

#include "graph.h"
#include "spmat.h"

typedef struct _BHatMatrix
{
	graph* 			originalGraph;
	spmat* 			relate_matrix;
	int*			degrees;
	double 			constM;
	int 			originalSize;
	double 			matrixNorm;
	double* 		f_vector;


	void 			(*freeBHat)(struct _BHatMatrix *B, int graphIsOneClique);

					/*If the indicator doShift == 1 -> multiplies B^[g] shifted matrix with a vector.
					 *Otherwise -> multiplies B^[g] matrix with a vector.*/
	void 			(*multBHat)(struct _BHatMatrix *B, graph *group, double* vector ,double *result, int doShift);

} BHatMatrix;

/*
 * Allocates a new B-hat matrix using dynamic allocation.
 * Sets B-Hat matrix's fields with values according to the input variables.
 *
 * @param graph 			 - a pointer to the original graph.
 * @param spmat 			 - a pointer to the original graph's adjacency matrix.
 * @param vector of integers - a pointer to the degrees-vector of the given graph.
 *
 * @return
 * If allocation succeeded, returns a pointer to the new B-Hat matrix.
 * Otherwise, throws an error and exists the program.
 */

BHatMatrix* createMatrixBHat (graph*, spmat*, int*);

/*
 * In order to create B^[g] from B[g], we calculate the F vector according to B[g].
 * The function allocates the current B matrix's F-vector using dynamic allocation,
 * and sets it into B's f_vector field.
 * If allocation failed, throws an error and exists the program.
 *
 * @param BHatmatrix - a pointer to the current B-Hat matrix.
 */

void initializeFVector(BHatMatrix*);

/*
 * Multiplies B[g] matrix with a given vector, and inserts the result into a provided vector.
 *
 * @param BHatMatrix 		- a pointer to the current B-Hat matrix.
 * @param graph 			- a pointer to a sub-graph of the original graph.
 * @param vector of doubles - a pointer to the vector to be multiplied with B[g] matrix.
 * @param vector of doubles - a pointer to the result vector.
 */
void BgMult(BHatMatrix*, graph*, double*, double*);

/*
 * Sums a specific row in a given adjacency matrix according to a provided graph.
 *
 * @param spmat 	- a pointer to a adjacency matrix.
 * @param graph 	- a pointer to a sub-graph of the original graph.
 * @param integer 	- a number of a row to sum.
 *
 * @return the sum of the requested row in the provided adjacency matrix according to the given graph.
 */

int sumRowsA(spmat*, graph*, int);

/*
 * Sums a specific row in the "degrees-matrix" of the given B-Hat matrix, according to a provided graph.
 *
 * @param graph 		- a pointer to a sub-graph of the original graph.
 * @param BHatMatrix	- a pointer to a B-Hat matrix.
 * @param integer 		- a number of a row to sum.
 *
 * @return the sum of the requested row in the "degrees matrix" of provided B-Hat matrix,
 * according to the given graph.
 */

double sumRowsD(graph*, BHatMatrix*, int);

/*
 * Sums the absolute values in a specific row in the given B-Hat matrix.
 *
 * @param BHatMatrix - a pointer to a B-Hat matrix.
 * @param integer 	 - a number of a row to sum.
 *
 * @return the sum of absolute values in the requested row in the provided B-Hat matrix.
 */

double sumRowB (BHatMatrix*, int);

/*
 * Multiplies a sub-vector by a number, and inserts the result into a provided vector.
 *
 * @param graph 				- a pointer to a sub-graph of the original graph.
 * @param double				- a number to multiply by.
 * @param vector of integers 	- a pointer to the vector to be multiplied.
 * @param vector of doubles 	- a pointer to the result vector.
 */

void multNumVec(graph* ,double, int*, double*);

/*
 * Subtracts two vectors (result[i] = v1[i] - v2[i]), and inserts the result into a provided vector.
 *
 * @param graph 				- a pointer to a sub-graph of the original graph that was received by the user.
 * @param vector of doubles		- a pointer to the minuend vector.
 * @param vector of doubles		- a pointer to the subtrahend vector.
 * @param vector of doubles 	- a pointer to the result vector.
 */

void substractTwoVecs(graph*, double*, double*, double*);

/*
 * Calculating a given B-Hat matrix's norm: the 1-norm of the largest column in B matrix
 * (largest according to each column 1-norm calculation).
 *
 * @param BHatMatrix - a pointer to a B-Hat matrix.
 *
 * @return the given B-hat matrix's norm.
 */

double calcMatrixNorm(BHatMatrix*);

/*
 * Calculating a given B-Hat matrix's 1/M when M == sum of degrees.
 *
 * @param BHatMatrix - a pointer to a B-Hat matrix.
 *
 * @return the constant: 1/(sum of degrees in the given B-Hat matrix).
 */

double calcM(BHatMatrix*);

/*
 * Calculating a specific place in a given B-Hat matrix.
 *
 * @param BHatMatrix - a pointer to a B-Hat matrix.
 * @param integer 	 - an integer represents a number of a row.
 * @param integer 	 - an integer represents a number of a column.
 *
 * @return the value in the given B-Hat matrix in the place provided.
 */

double calcBgPlace(BHatMatrix*, int, int);

/*
 * Multiplies sub-matrix of a given adjacency matrix by a vector, and inserts the result into a provided vector.
 *
 * @param spmat 		          - a pointer to a adjacency matrix.
 * @param graph 	 	          - a pointer to a sub-graph of the original graph.
 * @param const vector of doubles - a pointer to a vector for the multiplication operation.
 * @param vector of doubles 	  - a pointer to the result vector.
 */

void spmat_mult(spmat*, graph*, const double*, double*);

#endif
