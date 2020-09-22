
/*
 * linkedlist.c - Source File
 * Implementation of the functions declared in the header file
 */

#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"
#include "graph.h"
#include "errorHandler.h"

/* --------Functions Deceleration--------- */

linkedList_node*			createNode(int);
linkedList* 				createLinkedList();
void 						free_linkedList(linkedList*);
void 						free_linkedList_rec(linkedList_node*);

/* --------Functions Implementation---------*/

linkedList_node* createNode(int value)
{
	linkedList_node *newNode;

	newNode = (linkedList_node *)malloc(sizeof(linkedList_node));
	if(newNode == NULL) returnErrorByType(9);

	newNode -> value = value;
	newNode -> next = NULL;

	return newNode;
}

linkedList* createLinkedList()
{
	linkedList *list = (linkedList *)malloc(sizeof(linkedList));
	if(list == NULL) returnErrorByType(8);

	list -> head = NULL;
	list -> size = 0;
	list -> node_index = -1;
	list -> free_linkedList = free_linkedList;

	return list;
}

/*
 * Frees the list by performing recursive frees of the nodes,
 * and when the list is empty, frees the pointer to the list itself.
 */
void free_linkedList(linkedList* list) {
	free_linkedList_rec(list -> head);
	free(list);
}

/*A recursive implementation of free linked list */
void free_linkedList_rec(struct _linkedList_node* head)
{
	if (head != NULL)
	{
		free_linkedList_rec(head -> next);
		free(head);
	}
}
