/*
 * linkedList.c
 *
 *  Created on: 12 баев„ 2020
 *      Author: Avital
 */

#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"
#include "graph_node.h"


/*
 * --------Functions Definition---------
 */

	linkedList_node *createNode(int);
	void delete_node(linkedList *, int);
	linkedList *createLinkedList();
	linkedList *allocateListWithNodes(int);

/*
 * --------Functions Implementation---------
 */

/*constructor for node*/
linkedList_node *createNode(int value) {
	linkedList_node *newNode;
	newNode = (linkedList_node *)malloc(sizeof(linkedList_node));

	if(newNode == NULL){
	    	printf("Allocation of newNode Failed");
	    	exit(0);
	    }

    newNode -> value = value;
    newNode -> index = value;
    newNode -> next = NULL;
    return newNode;
}

/* constructor for linkedList*/
linkedList *createLinkedList() {
    linkedList *list = (linkedList *)malloc(sizeof(linkedList));

    if(list == NULL){
    	printf("Allocation of Linked List Failed");
    	exit(0);
    }

    list -> head = NULL;
    list -> size = 0;
    list -> node_index = -1;
    return list;
}


void delete_node(linkedList *list, int node_value){
	linkedList_node *curr = list -> head, *tmp = list -> head;

	//Case 1: First node in the list
	if(curr -> value == node_value){
		list -> head = curr -> next;
		free(curr);
	}
	else{
		//Case 2 : Not the First. Iterating over the list.
		curr = curr -> next;
		while(curr != NULL){
			if(curr -> value == node_value){
				tmp -> next = curr -> next;
				free(curr);
				break;
			}
			tmp = curr;
			curr = curr -> next;
		}
	}
}

/*Return a new linkedList (which was allocated prior)
 * with the nodes: 0,..., n -1
 */

linkedList *allocateListWithNodes(int n){
	linkedList *newList;
	linkedList_node *newNode, *curr;

	newList = createLinkedList();

	for(; i < n; i++){
		newNode = createNode(i);
		if(i == 0){
			newList -> head = newNode;
			curr = newNode;
		}
		else{
			curr -> next = newNode;
			curr = newNode;
		}
		(newList -> size) ++;
	}

	return newList;
}

