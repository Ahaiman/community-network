
/* algorithm4.h - Header File
 *
 * An algorithm for Modularity Maximization
 *
 * A method to further optimize a division of a network into two groups.
 * Suppose {g1, g2} is an initial division of graph g into two groups.
 * This algorithm optimizes this division further.
 *
 * To achieve this, we find a vertex v that when moved the other group, will give
 * the biggest increase in modularity of the complete network, or the smallest decrease if no
 * increase is possible, and then we move it to the other group.
 *
 * The algorithm performs this process with the constraint that each vertex may only be moved once,
 * until all vertices have been moved.
 * Once done, from all the states of division into two groups during the operation,
 * find the state that has the maximal modularity, and start again from this state.
 *
 * The algorithm repeats the entire process iteratively until no further improvement is found,
 * i.e. until the maximal state is the current one.
 *
 */

#ifndef ALGORITHM4_H_
#define ALGORITHM4_H_

#include "BHatMatrix.h"
#include "graph.h"


/*
 * The main algorithm as described above.
 *
 * The algorithm modifies the vector "s", that represents the division.
 *
 * @param BHatMatrix        - a pointer to a B-Hat matrix
 * @param graph             - a pointer to the current graph (before performing the division)
 * @param vector of doubles - a pointer to the current division vector, before maximizing the division.
 */

void			algorithm4(BHatMatrix*,graph*, double*);

/*
 * Setting zero values to a given vector.
 *
 * @param vector of integers - a pointer to a vector
 * @param integer            - the size of the given vector
 */

void			nullifyVector(int*, int);

#endif
