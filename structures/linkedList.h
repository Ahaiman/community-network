/*
 * LinkedList.c
 *
 *  Created on: 12 баев„ 2020
 *      Author: Avital
 */

#include "graph_node.h"

typedef struct linked_list_node {
    int value;
    struct linked_list_node  *next;

} linked_list_node;


typedef struct linkedList {
	linked_list_node   *head;
	int size;

} linkedList;

linked_list_node *createNode(int value);
linkedList *createLinkedList();
