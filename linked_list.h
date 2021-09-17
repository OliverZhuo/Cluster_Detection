#ifndef CLUSTERS_LINKED_LIST_H
#define CLUSTERS_LINKED_LIST_H
#include "groups.h"

typedef struct link {
    group *head;
    int length;
} link;

/* Initialize new  empty linked list */
link* init_O();

/* Initialize new linked list with one group containing numbers from 0 to n-1 */
link* init_P(int n);

/* Add set of numbers to start of linked list (nodes is pre- allocated) */
void insertg(link *lst, group *g);

/* Delete the first item of the linked list */
group* delete(link *lst);

/* Return 1 if the linked list is empty or 0 else */
int is_empty(link *lst);

/* Frees all resources used by lst */
void free_link(link *lst);

#endif
