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
	int *curr_nodes = group -> graph_nodes;
	int  *graph_nodes1, *graph_nodes2;
	int n = group -> n, n1 = 0, n2 = 0, i = 0;


	/*Finding the sizes of the two new groups */
	for(; i < n; i++){
		if(*s == 1){
			n1++;
		}
		else{
			n2++;
		}
		s++;
	}
	s -= n;

	/* Checking sizes before building the groups*/
	if(n1 == 0 || n2 == 0){
		divisionToTwo.push(group);
		divisionToTwo.push(NULL);
		return 0;
	}


	/*Allocating new list of nodes for each group*/
	graph_nodes1 = (int*) malloc(sizeof(int) * (n1));
	graph_nodes2 = (int*) malloc(sizeof(int) * (n2));

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
	updateNodesGroups(n, group->relate_matrix, s);

	/*Allocating new graph representing each new group */
	group1 = allocate_graph(n1, graph_nodes1, relate_matrix);
	group1 -> divisionNumber = 1;
	group2 = allocate_graph(n2, graph_nodes2, relate_matrix);
	group2 -> divisionNumber = -1;

	/*Adding division (two graph) to the input stack */
	divisionToTwo.push(group2);
	divisionToTwo.push(group1);

	/*Free only original graph without the nodes, and without the related matrix inside lists */
	free_graph(group, 0);

	return 0;


}


/* The function "createRelateMatrix"
 	 The function creates the new relation matrix, according to input data.
 	 Avital TODO
 */
void updateNodesGroups(int originalSize, spmat *matrix, int *s)
{
	linkedList **rows;
	linkedList *currList;
	linkedList *currNode;
	int i = 0, j = 0, curr_index;

	rows = matrix -> private;
	for(; i < currentSize; i++){
		currList = **rows;
		currNode=currList->head;
		while (currNode!=NULL)
		{
			currNode->index=*(s+(currNode->value));
			currNode=currNode->next;
		}
		rows++;
	}
}

}
