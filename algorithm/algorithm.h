
#ifndef ALGORITHM_H
#define ALGORITHM_H


#include "../structures/graph.h"
#include "../structures/BHatMatrix.h"
#include "../structures/stack.h"


/*algo_2.c*/
double divisionGraphToTwo(BHatMatrix *B, graph *group, stack *division, double *s);
/*algo_4.c*/
void algorithm4(BHatMatrix *B,graph *G, double *s);

/*algo_3.c*/
void findCommunities(graph *G, spmat *matrix, int * degrees, char *output_name);


#endif

