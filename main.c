#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "spmat.h"
#include "error_handle.h"
#include "network_division.h"

/* Create Matrix A */
void A_init(spmat *A, int *row, FILE *input){
    int k, j, n=A->n, i, tmp, index, *row_start;


    row_start= row;
    for (i=0;i<n;i++){
        for (j=0;j<n;j++){
            *row=0;
            row++;
        }
        row= row_start;
        k = fread(&tmp, sizeof(int), 1, input);
        reading_error(k,1);
        for(j=0;j<tmp;j++){
            k = fread(&index, sizeof(int), 1, input);
            reading_error(k,1);
            row[index]=1;
        }
        A->add_row(A,row,i);
    }

    fclose(input);
    free(row);
}

/* Calculate M */
int M_calc(int n, FILE *input){
   int M, i, k, tmp/*, j*/;
   M = 0;
    for (i = 0;i < n; i++)
    {
        k = fread(&tmp, sizeof(int), 1, input);
        reading_error(k,1);
        M+=tmp;
        fseek(input, tmp*sizeof(int), SEEK_CUR);
    }
    fseek(input,sizeof(int), SEEK_SET);
    return M;
}

/* Make output file */
void make_output(link *O, FILE *output){
    int k, i, len= O->length, g_len, *nodes;
    group *curr= O->head;

    k= fwrite(&len, sizeof(int), 1, output);
    writing_error(k,1);

    for (i=0;i<len;i++){
        g_len= curr->length;
        k= fwrite(&g_len, sizeof(int), 1, output);
        writing_error(k,1);
        nodes=curr->nodes;
        k= fwrite(nodes, sizeof(int), g_len, output);
        writing_error(k,g_len);
        curr= curr->next;
    }
    fclose(output);
}

int main(int argc, char* argv[])
{
    FILE *input, *output;
    int *K, *row, k, n, M;
    spmat* A;
    link *O;

    srand(time(NULL));
    arguments_error(argc);

    input = fopen(argv[1],"rb");
    open_error(input);
    k = fread(&n, sizeof(int), 1, input);
    reading_error(k,1);

    M= M_calc(n,input);
    M_zero(M);

    A= spmat_allocate_array(n, M);  /*number of edges is M/2*/
    row=(int*)malloc(n*sizeof(int));
    allocate_error(row);
    A_init(A, row, input);
    K=A->nnz_in_row(A);  /* Create vector K */

    O= algorithm3(A,K);

    output = fopen(argv[2],"w");
    open_error(output);
    make_output(O,output);


    free(K);
    A->free(A);
    free_link(O);

    return 0;
}
