
#ifndef ALGORITHM_H
#define ALGORITHM_H


#include "../structures/graph.h"
#include "../structures/BHatMatrix.h"
#include "../structures/stack.h"


/*algo_2.c*/
double divisionGraphToTwo(graph *group, stack *division, int *s);

/*algo_4.c*/
void algorithm4(BHatMatrix *B, int *s, int dQ);

/*algo_3.c*/
void findCommunities(graph *G, char *name_of_output_file);


#endif

