/*
Personal linked list implementation
list.c
*/

#include "list.h"
#include <stdio.h>
#include <stdlib.h>


struct list * init_list(void)
{
	struct list * list;
	list = malloc(sizeof(struct list));
	list->head = NULL;
	list->count = 0;
	return list;
} 


BOOLEAN add_node(struct list * list,void * data)
{
	struct node * newNode = malloc(sizeof(struct node));
	struct node * searchNode;
	int i;


	newNode->next = NULL;
	newNode->data = data;

	if(list->head == NULL)
	{

		list->head = newNode;
		list->count++;
		return TRUE;

	}else 
	{
	     searchNode = list->head;

             for(i = 1;i < list->count;i++)
	     {
	     	searchNode = searchNode->next; 
	     }

	     searchNode->next = newNode;
	     list->count++;
	     return TRUE;
	} 
	
	return FALSE;

} 

BOOLEAN remove_node(struct node *  prevNode,struct node * removeNode,struct list * list)
{
	
	prevNode->next = removeNode->next;
	free(removeNode->data);
	free(removeNode);
	list->count--;

	return TRUE;

}

void free_list(struct list * list)
{
	struct node * curr = NULL;
	struct node * next = NULL;
	struct node * edgeCurr = NULL;
	struct node * edgeNext = NULL; 

	curr = list->head;
	
	while(!curr)
	{
		next = curr->next;
		free_edgelist(curr->data);
		free(curr);
		curr = next;
	} 
} 

void free_edgelist(struct list * list)
{
	struct node * curr = NULL;
	struct node * next = NULL;

	while(!curr)
	{
		next = curr->next;
		free(curr->data);
		free(curr);
		curr = next;
	} 

} 
int search(struct list * list, void * comparator, int (*func)(struct node * node, void * comparator))
{
	struct node * searchnode;
	int result;	
	searchnode = list->head;

	while(searchnode || result != 0)
	{

		searchnode=searchnode->next;
		result=func(searchnode,comparator);
	} 
	
	return result;
}
