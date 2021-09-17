#ifndef CLUSTERS_GROUP_DIVISION_H
#define CLUSTERS_GROUP_DIVISION_H
#include "network_division.h"

/* Calculate modularity */
double modularity(spmat *A, double *s, int *nodes, int len, double *f, int *K, double norm1, double *tmp);

/* Divide a group into two */
double algorithm2(spmat *A, int *K, double *s, int *nodes, int len, double *f, double *eigen_vector, double *b, double *tmp);

#endif
