#ifndef CLUSTERS_EIGENPAIR_H
#define CLUSTERS_EIGENPAIR_H
#include "group_division.h"

/* Create random vector */
void vector_b0(double *b, int len);

/* Multiply sub matrix of A corresponding to g by a given vector b
 * Create vector f from sub matrix of A */
void A_mult(spmat *A, double *b, int *nodes, int len, double *f, double *res, int sub);

/* Multiply part of vector K corresponding to g by a given vector b
 * Create vector f from vector K */
void KM_mult(double *b, const int *K, double *res, const int *nodes, int len, int M, double *f, int sub);

/* Multiply the relevant elements in (-f+norm) by the given vector b */
double f_norm1_mult(double *b, double *res, int len, double *f, double norm1, int option);

/* Calculate Aij element in Matrix according to g */
int Aij(const int *colind,const int *rowptr, int i, int j);

/* Calculate norm1 of matrix B[g] hat */
void norm1_calc(spmat *A, const int *nodes, int len, const double *f, double *norm1, const int *K);

/* Multiply B[g] hat matrix by a given vector b */
double Bg_hat_mult(spmat *A, double *b, int *nodes, int len, double *f, double *res, int *K, double *norm1, int option);

/* Produces eigen vector corresponding to max eigen value of B[g] hat shifted matrix */
void power_iteration(spmat *A, int *K, int *nodes, int len, double *res, double *f, double *norm1, double *b);

/* Calculate dot product of two vectors */
double vector_mult(double *u, double *v, int len);

/* Calculate the largest eigen value of B[g] hat matrix */
double eigen_value(spmat *A, double *b, int *nodes, int len, double *f, int *K, double norm1, double *tmp);

#endif
