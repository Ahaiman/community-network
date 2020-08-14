/*
 * linkedList.c
 *
 *  Created on: 12 баев„ 2020
 *      Author: Avital
 */

#include "linkedList.h"
#include "graph_node.h"
#include <stdio.h>
#include <stdlib.h>


/*constructor for node*/
linked_list_node *createNode(int value) {
	linked_list_node *newNode = (linked_list_node *)malloc(sizeof(linked_list_node));
	if(newNode == NULL){
	    	printf("Allocation of newNode Failed");
	    	exit(0);
	    }

    newNode->value = value;
//    newNode->index = column;
    newNode->next = NULL;
    return newNode;
}

/* constructor for linkedList*/
linkedList *createLinkedList() {
    linkedList *list = (linkedList *)malloc(sizeof(linkedList));
    if(list == NULL){
    	printf("Allocation of Linked List Failed");
    	exit(0);
    }
    list->head = NULL;
    list -> size = 0;
    return list;
}
