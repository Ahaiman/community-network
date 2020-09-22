/*
 * LinkedList.c
 *
 *  Created on: 12 баев„ 2020
 *      Author: Avital
 */

#include "./graph.h"

typedef struct linkedList_node
{
    int value;
    double partByS;
    struct linkedList_node  *next;

} linkedList_node;


typedef struct linkedList
{
	linkedList_node   *head;
	int size;
	int node_index;

} linkedList;

linkedList_node *createNode(int value);
void delete_node(linkedList *list, linkedList_node* prev);
linkedList *createLinkedList();
linkedList *allocateListWithNodes(graph *g, int n);
