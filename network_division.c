#include "network_division.h"
#include <stdlib.h>
#include "error_handle.h"
#include "group_division.h"
#include "maximization.h"

/* Check if length of g is bigger than 0 and inset to P or O */
void size_check(link  *O, link *P, group *g){
    if (g->length==1){
        insertg(O,g);
    }
    else {
        insertg(P,g);
    }
}

/* Create g_i according to array node_i and len_i */
void g1_g2_create(double *s, int *nodes, int *nodes1, int *nodes2, int len){
    int i;

    for (i=0;i<len;i++){
        if (*s==1){
            *nodes1=*nodes;
            nodes1++;
        }
        else {
            *nodes2=*nodes;
            nodes2++;
        }
        nodes++;
        s++;
    }

}

/* Divide a network into modularity groups */
link* algorithm3(spmat *A , int *K){
    link *O, *P;
    group *g, *g1, *g2;
    int len, *nodes, i, n=A->n, len1, *nodes1, *nodes2, len2, cnt=0, *indices, *unmoved;
    double *s, *f, *eigen_vector, *b, *tmp, *score, *s_start;

    s = (double *) calloc(n,sizeof(double));
    allocate_error(s);
    eigen_vector = (double *) calloc(n , sizeof(double));
    allocate_error(eigen_vector);
    f = (double *) calloc(n , sizeof(double));
    allocate_error(f);
    b = (double *)calloc(n,sizeof(double));
    allocate_error(b);

    tmp = (double *) calloc(n , sizeof(double));
    allocate_error(tmp);

    indices = (int *) calloc(n , sizeof(int));
    allocate_error(indices);
    unmoved = (int *)calloc(n,sizeof(int));
    allocate_error(unmoved);
    score = (double *) calloc(n , sizeof(double));
    allocate_error(score);


    P=init_P(n);
    O=init_O();
    while (!is_empty(P)){
        cnt++;
        g= delete(P);
        len= g->length;
        nodes= g->nodes;

        algorithm2(A,K,s,nodes,len, f, eigen_vector, b, tmp);

        algorithm4(A,s,eigen_vector,nodes,len,K,unmoved,score,indices, tmp);

        len1=0;
        s_start= s;
        for (i=0;i<len;i++){
            if (*s==1){
                len1++;
            }
            s++;
        }
        s= s_start;
        len2=len-len1;
        if (len1==0||len2==0){
            insertg(O,g);
        }
        else {
            nodes1= (int*) malloc(len1*sizeof(int));
            allocate_error(nodes1);
            nodes2= (int*) malloc(len2*sizeof(int));
            allocate_error(nodes2);
            g1_g2_create(s,nodes,nodes1,nodes2, len);
            g1= init_group(nodes1,len1);
            g2= init_group(nodes2, len2);
            free_group(g);
            size_check(O,P,g1);
            size_check(O,P,g2);
        }
    }
    free(eigen_vector);
    free(f);
    free(s);
    free(b);
    free_link(P);
    free(tmp);
    free(unmoved);
    free(indices);
    free(score);

    return O;
}
