#include <stdio.h>
#include <stdlib.h>
#include "error_handle.h"
#define IS_POSITIVE(x)((x)>0.00001)
#define IS_NEGATIVE(x)((x)<-0.00001)

/* Printing error massage and exit from program */
void handle(char* massage)
{
    fprintf(stderr, "%s", massage);
    exit(EXIT_FAILURE);
}

/* Handle reading errors */
void reading_error(int k, int j)
{
    if(k!=j)
    {
        handle("Couldn't read from input file");
    }
}

/* Handle writing errors */
void writing_error(int k, int j)
{
    if(k!=j)
    {
        handle("Couldn't write to output file");
    }
}

/* Handle arguments missing error */
void arguments_error(int k)
{
    if(k!=3)
    {
        handle("There are missing arguments");
    }
}

/* Handle allocate or open errors */
void allocate_error(void* k)
{
    if(k==NULL)
    {
        handle("Couldn't allocate memory");
    }
}

/* Handle error when file doesn't open */
void open_error(FILE *k)
{
    if(k==NULL)
    {
        handle("Couldn't open input/ output file");
    }
}

/* Handle error when M=0 */
void M_zero(int M)
{
    if (M==0)
    {
        handle("There is no edges in the graph/nB undefined");
    }
}

/* Handle division by zero error */
void div_zero(double num)
{
    if (!IS_POSITIVE(num) && !IS_NEGATIVE(num))
    {
        handle("division by zero");
    }
}
