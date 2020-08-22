#include "./structures/stack.h"
#include "./structures/graph.h"
#include "./structures/graph_node.h"
#include "./structures/spmat.h"
#include "./structures/linkedList.h"


/*
 * --------Functions Declaration---------
 */
void createRelateMatrix(int, int, graph_node **, spmat *);
void doDivisionByS(Graph *group, int *s, stack *divisionToTwo){

/*
 * --------Functions Implementation---------
 */


/* The function "doDivisionByS"
 	 * Input: Graph, vector s which indicates division status for each node and an empty stack.
 	 * Output: Stack containing two graphs according to the division
 */

void doDivisionByS(Graph *group, int *s, stack *divisionToTwo){
	Graph *group1, *group2;
	spmat *relate_matrix1, *relate_matrix2;
	graph_node **graph_nodes1, **graph_nodes2, **curr_nodes = group -> graph_nodes;
	int n = group -> n, n1 = 0, n2 = 0, i = 0;


	/*Finding the sizes of the two new groups */
	for(; i < n; i++){
		if(*s == 1){
			n1++;
		}
		else{
			n2++;
		}
		/*Updating "group" field to the original nodes*/
//		*(curr_nodes) -> group = *s;
//		curr_nodes++;
		s++;
	}

//	curr_nodes -= n;
	s -= n;

	/* Checking sizes before building the groups*/
	if(n1 == 0 || n2 == 0){
		divisionToTwo.push(group);
		divisionToTwo.push(NULL);
		return 0; //exit ?/
	}


	/*Allocating new list of nodes for each group*/
	graph_nodes1 = (graph_node **) malloc(sizeof(graph_node *) * (n1));
	graph_nodes2 = (graph_node **) malloc(sizeof(graph_node *) * (n2));

	/*degree of node is CHANGEING?????? */

	/*Allocating new relation matrix for each group*/
	relate_matrix1 = spmat_allocate_list(n1)
	relate_matrix2 = spmat_allocate_list(n2)


	/*Updating the new lists of nodes for each group*/
	for(i = 0; i < n; i++){
		if(*s == 1){
			*graph_nodes1 = *curr_nodes;
			graph_nodes1++;
		}
		else{
			*graph_nodes2 = *curr_nodes;
			graph_nodes2++
		}
		s++;
		curr_nodes++;
	}

	graph_nodes1 -= n1;
	graph_nodes2 -= n2;

	/*Updating the relation matrix of each group */
	createRelateMatrix(n, n1, graph_nodes1, relate_matrix1);
	createRelateMatrix(n, n2, graph_nodes2, relate_matrix2);

	/*Allocating new graph representing each new group */
	group1 = allocate_graph(n1, **graph_nodes1, *relate_matrix1);
	group2 = allocate_graph(n2, **graph_nodes2, *relate_matrix2);

	/*Adding division (two graph) to the input stack */
	divisionToTwo.push(group2);
	divisionToTwo.push(group1);

	/*Free only original graph without the nodes, and without the related matrix inside lists */
	free_graph(group, 0, 0);

	return 0;


}


/* The function "createRelateMatrix"
 	 The function creates the new relation matrix, according to input data.
 */
void createRelateMatrix(int originalSize, int currentSize, graph_node **listOfNodes, spmat *matrix){
	linkedList **rows;
	int i = 0, j = 0, curr_index;

	rows = matrix -> private;
	for(; i < currentSize; i++){
		curr_index = *(listOfNodes) -> index;
		for(; j < originalSize; j++){
			if((*rows) -> node_index == curr_index){
				*(matrix -> private) = *rows;
				matrix -> private++;
				break;
			}
			rows++;
		}
		listOfNodes++;
	}
}



