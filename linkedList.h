
/* linkedList.h - Header File
 *
 * An implementation of a linked list, according to FIFO.
 *
 * Each node in the linked list consists of value (node index) and a pointer to the next node.
 * The structure contains the following fields:
 * 		"size"        - representing the current number of nodes in the list
 * 		"node_index"  - the index of the node that the current linked list represents its neighbors
 * 		"head"        -	pointer to the head node of the list
 *
 * 	createNode                - initialize a new node
 *	createLinkedList          - initialize a new linked list
 *	free_linkedList           - frees the nodes in the list, and the list itself
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "graph.h"

typedef struct _linkedList_node
{
	int        	  				value;

	/*A pointer to the next node in the list */
	struct _linkedList_node*   	next;

} linkedList_node;

typedef struct _linkedList
{
	int        	  				size;
	int 						node_index;
	linkedList_node*   			head;

	void   						(*free_linkedList)(struct _linkedList * );

} linkedList;

/**
 * Allocates a new node using dynamic allocation.
 * Sets the input value to the node's value field, and its next pointer to NULL
 *
 * @param integer - the value of the new node
 *
 * @return
 * If allocation succeeded, returns a pointer to the new linked list node created.
 * Otherwise throws an error and exits the program.
 */

linkedList_node*			createNode(int);

/**
 * Allocates a new linked list using dynamic allocation.
 * Sets the inner fields to initial values.
 *
 * @return
 * If allocation succeeded, returns a pointer to the new linked list created.
 * Otherwise, throws an error and exits the program.
 */

linkedList* 				createLinkedList();

#endif
