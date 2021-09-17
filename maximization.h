#ifndef CLUSTERS_MAXIMIZATION_H
#define CLUSTERS_MAXIMIZATION_H
#include "spmat.h"

/* Calculate vector score */
void score_calc(int len, const int *K, int *nodes, int M, double *score, double *s, double *x);

/* Find the maximum value and his index in vector score */
void score_max(int *unmoved, double *score, int len, int *max_index, double *max_score);

/* Update vector score */
void update(double *score, int max_index,const int *nodes, const int *K, int M, spmat *A, const double *s, int len);

/* Improving a 2- division of the network */
void algorithm4 (spmat *A, double *s, double *x, int *nodes, int len, int *K, int *unmoved, double *score, int *indices, double *tmp);

#endif
