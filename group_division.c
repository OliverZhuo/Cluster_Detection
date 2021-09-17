#include "group_division.h"
#include "eigenpair.h"
#define IS_POSITIVE(x)((x)>0.00001)
#define IS_NEGATIVE(x)((x)<-0.00001)

/* Calculate modularity */
double modularity(spmat *A, double *s, int *nodes, int len, double *f, int *K, double norm1, double *tmp){
    double deltaQ;

    Bg_hat_mult(A,s,nodes,len,f,tmp,K,&norm1,2);
    deltaQ= vector_mult(s,tmp,len);
    if (!IS_POSITIVE(deltaQ) && !IS_NEGATIVE(deltaQ)){
        deltaQ=0;
    }

    return deltaQ;
}

/* Divide a group into two */
double algorithm2(spmat *A, int *K, double *s, int *nodes, int len, double *f, double *eigen_vector, double *b, double *tmp) {
    double max_eigen_value, norm1 = 0, deltaQ=0, *s_start;
    int i;

    power_iteration(A, K, nodes, len, eigen_vector, f, &norm1, b);
    max_eigen_value = eigen_value(A, eigen_vector, nodes, len, f, K, 1, tmp);

    s_start= s;
    if (IS_POSITIVE(max_eigen_value)) {
        for (i = 0; i < len; i++) {
            if (IS_POSITIVE((*eigen_vector))) {
                *s = 1;
            } else {
                *s = -1;
            }
            s++;
            eigen_vector++;
        }
        s= s_start;
        deltaQ=modularity(A, s, nodes, len, f, K, norm1, tmp);
        if(!IS_POSITIVE(deltaQ)){
            for (i=0;i<len;i++){
                *s=1;
                s++;
            }
        }
    } else{
        for (i=0;i<len;i++){
            *s=1;
            s++;
        }
    }
    return deltaQ;
}
