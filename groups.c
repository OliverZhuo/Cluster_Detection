#include "groups.h"
#include "error_handle.h"
#include <stdlib.h>

/* Initialize new group with elements from array nodes and length */
group* init_group(int* nodes, int length){
    group *g= (group*) malloc(sizeof(group));
    allocate_error(g);
    g->length= length;
    g->nodes= nodes;
    g->next= NULL;
    return g;
}

/* Frees all resources used by g */
void free_group(group *g){
   free(g->nodes);
   free(g);
}
