/*
Personal generic linked list implementation
list.h
	Author: Emile Antognetti - s3488934
*/

/*Boolean type definiton*/
typedef enum truefalse
{
	FALSE, TRUE
} BOOLEAN;

struct list
{
	struct node * head;
	unsigned count;
}; 


struct node
{
	struct node * next;
	void *  data;
};


struct list * init_list(void);
BOOLEAN add_node(struct list * list, void * data);
BOOLEAN remove_node(struct node *  prevNode,struct node * removeNode,struct list * list);
void free_edgelist(struct list * list);
void free_list(struct list * list);
int search(struct list * list, char * string, int (*func)(struct node * node, char * string));

