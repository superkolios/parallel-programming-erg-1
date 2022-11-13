#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "mmio.h"
#include "my_csc.h"


/* 
*   This function is based on Matrix Market I/O example program
*   http://math.nist.gov/MatrixMarket/mmio/c/example_read.c
*/
int my_csc_mtx_to_csc(struct Csc* csc, char* file)
{
    int ret_code;
    MM_typecode matcode;
    FILE *f;
    int M, N, nz;   
    int i;
  
        if ((f = fopen(file, "r")) == NULL) 
            exit(1);

    if (mm_read_banner(f, &matcode) != 0)
    {
        printf("Could not process Matrix Market banner.\n");
        exit(1);
    }


    /*  This is how one can screen matrix types if their application */
    /*  only supports a subset of the Matrix Market data types.      */

    if (mm_is_complex(matcode) && mm_is_matrix(matcode) && 
            mm_is_sparse(matcode) )
    {
        printf("Sorry, this application does not support ");
        printf("Market Market type: [%s]\n", mm_typecode_to_str(matcode));
        exit(1);
    }
    
    
    /* find out size of sparse matrix .... */

    if ((ret_code = mm_read_mtx_crd_size(f, &M, &N, &nz)) !=0)
        exit(1);

    
    /* reseve memory for matrices */
    csc->col_index = (int*) malloc (nz * sizeof(int));
    csc->row_index = (int*) malloc ((M+1) * sizeof(int));

    int I=0, prev_I=0;
    csc->col_index[0] = 0;
    csc->col_index[M] = nz;
    double value;
    if (!mm_is_pattern(matcode)){
        for (i=0; i<nz; i++)
        {
            fscanf(f, "%d %d %lg\n", &csc->row_index[i], &I, &value);
            I--;  /* adjust from 1-based to 0-based */
            if (I > prev_I){
                for (prev_I; prev_I < I; prev_I++){
                    csc->col_index[prev_I + 1] = i;
                }
            }
            csc->row_index[i]--;
        }
    }
    else{
        for (i=0; i<nz; i++)
        {
            fscanf(f, "%d %d\n", &csc->row_index[i], &I);
            I--;  /* adjust from 1-based to 0-based */
            if (I > prev_I){
                for (prev_I; prev_I < I; prev_I++){
                    csc->col_index[prev_I + 1] = i;
                }
            }
            csc->row_index[i]--;
        }
    }
    csc->m = M;
    csc->n = N;
    csc->nz = nz;
    if (f !=stdin) fclose(f);
    return 0;
}

int* my_csc_trim(struct Csc *csc){
    int* no_edge_in = (int*)malloc(csc->n * sizeof(bool));
    int* no_edge_out = (int*)malloc(csc->n * sizeof(bool));
    int* to_trim = (int*)malloc(csc->n * sizeof(bool));
    for (int i = 0; i < csc->n; i++){
        no_edge_in[i] = true;
        no_edge_out[i] = true;
        to_trim[i] = false;
    }
    
    //if the same number appears twice in a row in row_index the this node has no in edges.
    for (int i = 0; i < csc->n; i++){
        if (csc->col_index[i] != csc->col_index[i+1]){
            no_edge_in[i] = false;
        }
    }

    //checks if atleast a node shows 1 time in col_index.
    for (int i = 0; i < csc->nz; i++){
        no_edge_out[csc->row_index[i]] = false;
    }
    
    for (int i = 0; i < csc->n; i++){
        if (no_edge_in[i] || no_edge_out[i]){
            to_trim[i] = true;
        }
    }
    return(to_trim);
}
