#ifndef CLUSTERS_ERROR_HANDLE_H
#define CLUSTERS_ERROR_HANDLE_H
#include <stdio.h>

/* Printing error massage and exit from program */
void handle(char* massage);

/* Handle reading errors */
void reading_error(int k, int j);

/* Handle writing errors */
void writing_error(int k, int j);

/* Handle arguments missing error */
void arguments_error(int k);

/* Handle allocate or open errors */
void allocate_error(void* k);

/* Handle error when file doesn't open */
void open_error(FILE *k);

/* Handle error when M=0 */
void M_zero(int M);

/* Handle division by zero error */
void div_zero(double num);

#endif
