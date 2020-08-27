/*
 * LinkedList.c
 *
 *  Created on: 12 баев„ 2020
 *      Author: Avital
 */

#include "graph_node.h"

typedef struct linkedList_node {
    int value;
    int partByS;
    struct linkedList_node  *next;

} linkedList_node;


typedef struct linkedList {
	linkedList_node   *head;
	int size;
	int node_index;

} linkedList;

linkedList_node *createNode(int value);
void delete_node(linkedList *list, int node_value);
linkedList *createLinkedList();
linkedList *allocateListWithNodes(int n);
