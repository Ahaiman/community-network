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
linkedList_node *createNode(int value) {
	linkedList_node *newNode = (linkedList_node *)malloc(sizeof(linkedList_node));
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


void delete_node(linkedList *list, int node_index){
	linkedList_node *curr = list -> head, *tmp = list -> head;

	//first node in the list
	if(curr -> value == node_index){
		list -> head = curr -> next;
		free(curr);
	}
	else{
		//put curr to point on the next element (not the head)
		curr = curr -> next;
		while(curr != NULL){
			if(curr -> value == node_index){
				tmp -> next = curr -> next;
				break;
			}
			tmp = curr;
			curr = curr -> next;
		}
	}
}

