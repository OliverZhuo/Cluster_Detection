#include "spmat.h"
#include <stdlib.h>
#include "error_handle.h"

/* Adds row i the matrix. Called before any other call,
 * exactly n times in order (i = 0 to n-1) */
void array_add_row(spmat *A, const int *row, int i)
{
    int j, row_len, insertind, val;

    row_len = A -> n;
    insertind = A->rowptr[i]; /*from which cell in values array we start filling*/

    for (j = 0; j < row_len; ++j) {
        val = *row;
        if (val != 0)
        {
            A -> colind[insertind] = j;
            insertind++;
        }
        row++;
    }
    A -> rowptr[i+1] = insertind; /*the number of non-zero elements in arr_mat currently*/


}

/* Frees all resources used by A */
void array_free(spmat *A)
{
    free(A -> colind);
    free(A -> rowptr);
    free(A);
}

/* Multiplies matrix A by vector v, into result (result is pre-allocated) */
void array_mult(const spmat *A, const double *v, double *result)
{
    int *rp, *colind, n, i, j, a, nnz_in_row,tmp;
    double tmp2, sum;

    rp = A->rowptr;
    colind = A->colind;
    n = A->n;
    for(i = 0; i < n; ++i)
    {
        a = *rp;
        nnz_in_row = *(rp+1)-a;
        rp++;
        sum = 0;
        for (j = 0; j < nnz_in_row; ++j)
        {
            tmp=*colind;
            tmp2=v[tmp];
            sum += tmp2;
            colind++;
        }
        *result = sum;
        result++;
    }
}

/* Return array K such that K[i] is how much non-zero elements in row i*/
int* nnz_in_row_array(spmat *A)
{
    int *index, *a, *a_start;
    int i, n;
    n=A->n;
    a=(int *) malloc(n*sizeof(int));
    allocate_error(a);
    index=A->rowptr;
    a_start= a;
    for(i=0;i<n;i++){
        *a=*(index+1)-*index;
        a++;
        index++;
    }
    return a_start;
}

/* Allocates a new arrays sparse matrix of size n with nnz non-zero elements */
spmat* spmat_allocate_array(int n, int nnz) {
    spmat *sp;

    sp = (spmat *) malloc(sizeof(spmat));
    allocate_error(sp);

    sp->n = n;
    sp->add_row = array_add_row;
    sp->free = array_free;
    sp->mult = array_mult;
    sp->nnz_in_row = nnz_in_row_array;

    sp->colind = (int *) malloc(sizeof(int) * nnz);
    allocate_error(sp->colind);

    sp->rowptr = (int *) malloc(sizeof(int) * (n + 1));
    allocate_error(sp->rowptr);

    sp->rowptr[0] = 0;

    return sp;
}
