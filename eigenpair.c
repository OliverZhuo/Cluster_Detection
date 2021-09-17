#include "eigenpair.h"
#include <stdlib.h>
#include <math.h>
#include "error_handle.h"
#define IS_POSITIVE(x)((x)>0.00001)

/* Create random vector */
void vector_b0(double *b, int len){
    int i;

    for (i=0;i<len;i++){
        *b= (double) rand();
        b++;
    }
}

/* Multiply part of vector K corresponding to g by a given vector b
 * Create vector f from vector K */
void KM_mult(double *b, const int *K, double *res, const int *nodes, int len, int M, double *f, int sub){
    int i, index;
    double sum=0, tmp=0, tmp2;
    for (i=0;i<len;i++){
        index=nodes[i];
        tmp2=K[index];
        tmp+=tmp2;
        sum+=(tmp2*(*b));
        b++;
    }
    for (i=0;i<len;i++){
        index=nodes[i];
        tmp2=(double) K[index]/M;
        *res-=sum*tmp2;
        res++;
        if (!sub) {
            *f-=tmp*tmp2;
            f++;
        }
    }
}

/* Multiply the relevant elements in (-f+norm) by the given vector b */
double f_norm1_mult(double *b, double *res, int len, double *f, double norm1, int option){
    double magnitude=0;
    int i;
    for (i=0;i<len;i++){
        if(option!=2) {
            *res += (norm1 - *f) * (*b);
        }
        else{
            *res += (*f) * (*b);
        }
        if (option==1) { /* for B[g]_hat mult */
            magnitude+=(*res)*(*res);
        }
        res++;
        b++;
        f++;
    }
    return magnitude;
}

/* Multiply sub matrix of A corresponding to g by a given vector b
 * Create vector f from sub matrix of A */
void A_mult(spmat *A, double *b, int *nodes, int len, double *f, double *res, int sub){
    int *colind = A->colind,*rowptr = A->rowptr,i/*,*row*/, j, k, *nodes_start, tmp1, l, *nodes_i;
    double *b_start;

    /* When sub=0: A[g]!=A, so we can't use mult function of spmat */
    if(!sub) {
        nodes_i = nodes;
        nodes_start = nodes;
        b_start = b;

        for (i=0;i<len;i++){
            *res=0;
            *f=0;
            tmp1=*nodes_i;
            k=rowptr[tmp1];
            l=rowptr[tmp1+1];
            for (j = 0; j < len; j++) {
                while (k!=l) {
                    if (colind[k] < *nodes) {
                        k++;
                    } else {
                        if (colind[k] == *nodes) {
                            (*f)++;
                            *res += *b;
                            k++;
                        }
                        b++;
                        nodes++;
                        break;
                    }
                }
            }
            b=b_start;
            nodes=nodes_start;
            nodes_i++;
            f++;
            res++;
        }
    }
    else{ /* A[g]=A */
        A->mult(A,b,res);
    }
}

/* Calculate Aij element in Matrix according to g */
int Aij(const int *colind,const int *rowptr, int i, int j){
    int k, l=rowptr[i], m=rowptr[i+1];

    for (k=l; k<m; k++){
        if(colind[k] == j){
            return 1;
        }
    }
    return 0;
}

/* Calculate norm1 of matrix B[g] hat */
void norm1_calc(spmat *A, const int *nodes, int len, const double *f, double *norm1, const int *K){
    int i, j, a, *colind=A->colind,*rowptr=A->rowptr, M=A->rowptr[A->n],gi,gj;
    double v, d, sum;

    for (i=0;i<len;i++){
        gi=*(nodes+i);
        sum=0;
        for (j=0;j<len;j++){
            gj=*(nodes+j);
            a= Aij(colind, rowptr, gi, gj);

            d= (double) (K[gi] * K[gj]) / M;
            if (gi==gj){
                v=a-d-f[i];
            }
            else{
                v=a-d;
            }
            sum+=fabs(v);
        }
        if(*norm1<sum){
            *norm1=sum;
        }
    }
}

/* Multiply B[g] hat matrix by a given vector b */
double Bg_hat_mult(spmat *A, double *b, int *nodes, int len, double *f, double *res, int *K, double *norm1, int option){
    int sub=0;
    double magnitude;
    if (A->n == len) {
        sub = 1;
    }
    A_mult(A, b, nodes, len, f, res, sub);

    KM_mult(b, K, res, nodes, len, A->rowptr[A->n], f, sub);

    if(option==1 && *norm1==0) {
        norm1_calc(A, nodes, len, f, norm1, K);
    }

    magnitude= f_norm1_mult(b, res, len, f, *norm1, option);
    return magnitude;
}

/* Produces eigen vector corresponding to max eigen value of B[g] hat shifted matrix */
void power_iteration(spmat *A, int *K, int *nodes, int len, double *res, double *f, double *norm1, double *b){
    double magnitude, *tmp, *res_start, *b_start;
    int i, flag=1, cnt=0, option=1;


    vector_b0(b,len);

    while (flag==1) {
        cnt++;
        if (cnt>=20000*len+80000){
            handle("Couldn't produce eigen vector with power iteration");
        }
        flag=0;

        magnitude= Bg_hat_mult(A, b, nodes, len, f, res, K, norm1, option);
        div_zero(magnitude);
        magnitude=sqrt(magnitude);
        res_start= res;
        b_start= b;
        for (i=0;i<len;i++){
            *res=*res/magnitude;
            if(IS_POSITIVE(fabs(*res-*b))){
                flag=1;
            }
            res++;
            b++;
        }
        res= res_start;
        b= b_start;
        if(flag==1) {
            tmp = b;
            b = res;
            res = tmp;
        }
    }
}

/* Calculate dot product of two vectors */
double vector_mult(double *u, double *v, int len){
    int i;
    double sum=0;
    for(i=0;i<len;i++){
        sum+=(*u)*(*v);
        u++;
        v++;
    }
    return sum;
}

/* Calculate the largest eigen value of B[g] hat matrix */
double eigen_value(spmat *A, double *b, int *nodes, int len, double *f, int *K, double norm1, double *tmp){
    double numerator, denominator;

    Bg_hat_mult(A, b, nodes, len, f, tmp, K, &norm1, 0);
    numerator= vector_mult(tmp,b,len);
    denominator= vector_mult(b, b, len);
    div_zero(denominator);

    return numerator/denominator-norm1;
}
