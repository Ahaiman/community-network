
#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "./structures/graph.h"
#include "./structures/stack.h"
#include "./structures/BHatMatrix.h""

/*algo_2.c*/
stack *divisionGraphToTwo(graph *group, stack *division, int *s);

/*algo_4.c*/
void algorithm4(BHatMatrix *B, int *s, int dQ);

/*algo_3.c*/
void findCommunities(graph *G);


#endif

