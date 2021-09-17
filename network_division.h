#ifndef CLUSTERS_NETWORK_DIVISION_H
#define CLUSTERS_NETWORK_DIVISION_H
#include "linked_list.h"
#include "spmat.h"
#include <stdio.h>

/* Check if length of g is bigger than 0 and inset to P or O */
void size_check(link  *O, link *P, group *g);

/* Create g_i according to array node_i and len_i */
void g1_g2_create(double *s, int *nodes, int *nodes1, int *nodes2, int len);

/* Divide a network into modularity groups */
link* algorithm3(spmat *A ,int *K);

#endif
