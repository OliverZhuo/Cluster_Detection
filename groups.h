#ifndef CLUSTERS_GROUPS_H
#define CLUSTERS_GROUPS_H

typedef struct group {
    int *nodes;
    int length;
    struct group *next;
} group;

/* Initialize new group with elements from array nodes and length */
group* init_group(int* nodes, int length);

/* Frees all resources used by g */
void free_group(group *g);

#endif
