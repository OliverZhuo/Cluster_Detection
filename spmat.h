#ifndef CLUSTERS_SPMAT_H
#define CLUSTERS_SPMAT_H

typedef struct _spmat {
    /* Matrix size (n*n) */
    int		n;
    int *colind;
    int *rowptr;

    /* Adds row i the matrix. Called before any other call,
     * exactly n times in order (i = 0 to n-1) */
    void	(*add_row)(struct _spmat *A, const int *row, int i);

    /* Frees all resources used by A */
    void	(*free)(struct _spmat *A);

    /* Multiplies matrix A by vector v, into result (result is pre-allocated) */
    void	(*mult)(const struct _spmat *A, const double *v, double *result);

    /* Return array K such that K[i] is how much non-zero elements in row i*/
    int* (*nnz_in_row)(struct _spmat *A);

} spmat;

/* Allocates a new arrays sparse matrix of size n with nnz non-zero elements */
spmat* spmat_allocate_array(int n, int nnz);

#endif
