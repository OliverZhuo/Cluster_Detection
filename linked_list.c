#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include "error_handle.h"

/* Initialize new  empty linked list */
link* init_O(){
    link *lst=(link*) malloc(sizeof(link));
    allocate_error(lst);
    lst->length=0;
    lst->head=NULL;
    return lst;
}

/* Initialize new linked list with one group containing numbers from 0 to n-1 */
link* init_P(int n){
    int *g, i, *g_start;
    link *lst=(link*) malloc(sizeof(link));
    allocate_error(lst);
    g=(int*) malloc(n*sizeof(int));
    allocate_error(lst);
    lst->length=1;
    g_start= g;
    for (i=0;i<n;i++){
        *g=i;
        g++;
    }
    g= g_start;
    lst->head=init_group(g,n);
    return lst;
}

/* Add set of numbers to start of linked list (nodes is pre- allocated) */
void insertg(link *lst, group *g){
    group *tmp;
    lst->length++;
    tmp=lst->head;
    g->next=tmp;
    lst->head=g;
}

/* Delete the first item of the linked list */
group* delete(link *lst)
{
    group *g= lst->head;
    if (is_empty(lst)){
        return NULL;
    }
    lst->head= g->next;
    lst->length-=1;
    return g;
}

/* Return 1 if the linked list is empty or 0 else */
int is_empty(link *lst)
{
    if (lst->length==0)
    {
        return 1;
    }
    return 0;
}

/* Frees all resources used by lst */
void free_link(link *lst)
{
    int len, i;
    group *head, *curr;

    len=lst->length;
    head= lst->head;
    for(i=0;i<len;i++){
        curr= head;
        head=head->next;
        free_group(curr);
    }
    free(lst);
}
