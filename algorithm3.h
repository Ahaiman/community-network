
/* algorithm3.h - Header File
 *
 * The main algorithm of the project.
 * This algorithm is called from the main function, after the input graph was created.
 * This algorithm calls the other algorithms during every run.
 *
 * The main propose of the algorithm is to divide a network into modularity groups,
 * using repeated division of the network into two.
 *
 * In each iteration, we try to divide the current group (representing a sub graph) to two groups (using algorithm2).
 * Except for the case "algorithm2" returns that there is no division, we send the division to maximization (using algorithm4).
 * According to the last updated division (represented by vector "s") we create two independent groups,
 * which we try to divide further, until no division is possible.
 *
 * The algorithm stops when we divided the input graph to the maximum division possible, then we write the result into an output file.
 */

#ifndef ALGORITHM3_H_
#define ALGORITHM3_H_

#include "stack.h"
#include "graph.h"
#include "spmat.h"

/* The main algorithm.
 *
 * Performing an iterating devision of the graph into two.
 * This functions is called only once at the beginning of the program, by the main function.
 *
 * @param graph   - a pointer to the original graph
 * @param spmat   - a pointer to the original adjacency matrix of the original graph
 * @param integer - an indicator to the existence of a possible division
 * @param string  - the name of the input file to write the division on
 */

void 			findCommunities(graph*, spmat*, int*, char*);

/* Creates two new graph instances according to the current devision represented by the given vector s.
 * The function allocates and creates the inner fields required for initializing the new graphs.
 *
 * @param graph             - a pointer to the current group, before division.
 * @param vector of doubles - a pointer to the division vector.
 * @param stack             - a pointer to a stack, to hold the two new groups
 * @param integer           - an indicator to the first iteration of the algorithm.
 * 							  Used for memory release considerations (if first = 1)
 */

void 			divisionByS(graph*, double*, stack*, int);

/* This function creates an instance of the input graph, according to an input file by the user.
 * It sets the relevant values into the graph structure, creates the input degrees vector and
 * builds the sparse matrix representing the adjacency matrix (which will be held later on in the BHatMatrix structure).
 *
 * This function is called only once from the main program.
 *
 * @param FILE  - a pointer to the input file (holds the data of the input graph)
 * @param graph - a pointer to a pre-allocated graph structure
 * @param spmat - a pointer to a pre-allocated sparse matrix structure
 *
 * @return the degrees vector of the input graph
 */

int*			createGraph(FILE*, graph*, spmat*);

#endif
