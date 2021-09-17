#include "maximization.h"
#include "eigenpair.h"

/* Calculate vector score */
void score_calc(int len, const int *K, int *nodes, int M, double *score, double *s, double *x){
    int i, d;

    for (i=0;i<len;i++){
        d= *(K+(*nodes));
        *score= -2*( (*s)*(*x) + (double)(d*d)/M ); /* score[i] = -2*(s[i]*x[i] + (k^2)/M) */
        score++;
        nodes++;
        s++;
        x++;
    }
}

/* Find the maximum value and his index in vector score */
void score_max(int *unmoved, double *score, int len, int *max_index, double *max_score){
    int j;

    for (j=0;j<len;j++) {
        if (*unmoved == 0 && *score > *max_score){
            *max_score= *score;
            *max_index= j;
        }
        unmoved++;
        score++;
    }
}

/* Update vector score */
void update(double *score, int max_index,const int *nodes, const int *K, int M, spmat *A, const double *s, int len){
    int k, gi, gj, *rowptr=A->rowptr, *colind=A->colind;

    gj= *(nodes+max_index);
    for (k=0;k<len;k++) {
        if (k==max_index){
            *score= -(*score);
        } else{
            gi= *(nodes+k);
            *score-= 4*(*(s+k))*(*(s+max_index))*(Aij(colind,rowptr,gi,gj)-((double)(K[gi]*K[gj])/M));
        }
        score++;
    }
}

/* Improving a 2- division of the network */
void algorithm4 (spmat *A, double *s, double *x, int *nodes, int len, int *K, int *unmoved, double *score, int *indices, double *tmp){
    int i, j, M=A->rowptr[A->n], max_index, sub=0, cnt=0, *unmoved_start, *indices_start;
    double max_score, max_improve, curr_improve, index_improve, deltaQ=1;

    if (A->n == len) {
        sub = 1;
    }
    A_mult(A,s,nodes,len,tmp,x,sub);
    KM_mult(s,K,x,nodes,len,M,tmp,1);

    score_calc(len, K, nodes, M, score, s, x);

    while(deltaQ>0){
        cnt++;
        unmoved_start= unmoved;
        for (i=0;i<len;i++){
            *unmoved=0;
            unmoved++;
        }
        unmoved= unmoved_start;

        indices_start= indices;
        for (i=0;i<len;i++) {
            if(i!=0){
                update(score,max_index,nodes,K,M,A,s,len);
            }
            max_score= -999999999;
            max_index= -999999999;
            score_max(unmoved, score, len, &max_index, &max_score);

            *(s+max_index)= -(*(s+max_index));
            *indices= max_index;
            if (i==0){
                curr_improve= max_score;
                max_improve= max_score;
                index_improve= i;
            } else{
                curr_improve+= max_score;
                if(curr_improve > max_improve){
                    max_improve= curr_improve;
                    index_improve= i;
                }
            }
            indices++;
            *(unmoved+max_index)= 1;
        }
        indices= indices_start;
        update(score,max_index,nodes,K,M,A,s,len);
        for (i=len-1;i>index_improve;i--) {
            j=*(indices+i);
            *(s+j)= -(*(s+j));
            update(score,j,nodes,K,M,A,s,len);
        }
        if (index_improve==len-1){
            deltaQ= 0;
        } else{
            deltaQ= max_improve;
        }
    }
}
