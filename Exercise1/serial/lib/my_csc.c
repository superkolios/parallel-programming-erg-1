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
    csc->row_index = (int*) malloc (nz * sizeof(int));
    csc->col_index = (int*) malloc ((M+1) * sizeof(int));
    if (csc->row_index == NULL || csc->col_index == NULL){
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    int I=0, prev_I=0;
    csc->col_index[0] = 0;
    csc->col_index[M] = nz;
    
    csc->m = M;
    csc->n = N;
    csc->nz = nz;
    csc->remaining = N;
    csc->valid_nodes = (bool*)malloc(N * sizeof(bool));
    if (csc->valid_nodes == NULL){
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    for (int i = 0; i < N; i++){
        csc->valid_nodes[i] = true;
    }
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

    for (prev_I = prev_I+1; prev_I<csc->n; prev_I++){
        csc->col_index[prev_I] = i;
    }
    if (f !=stdin) fclose(f);
    return 0;
}

bool* my_csc_trim(struct Csc *csc, bool *to_trim, bool *has_changed){
    bool* no_edge_in = (bool*)malloc(csc->n * sizeof(bool));
    bool* no_edge_out = (bool*)malloc(csc->n * sizeof(bool));
    if (no_edge_in == NULL || no_edge_out == NULL){
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    for (int i = 0; i < csc->n; i++){
        no_edge_in[i] = true;
        no_edge_out[i] = true;
    }
    
    for (int v = 0; v < csc->n; v++){
        if(!csc->valid_nodes[v])
            continue;
        int start = csc->col_index[v];
        int end = csc->col_index[v+1];
        for (int u = start; u < end; u++){
            if(!csc->valid_nodes[csc->row_index[u]])
                continue;
            no_edge_in[v] = false;
            no_edge_out[csc->row_index[u]] = false;
            }
        }
    for (int i = 0; i < csc->n; i++){
        if (no_edge_in[i] || no_edge_out[i]){
            if (to_trim[i] == false){
                to_trim[i] = true;
                *has_changed = true;
                csc->valid_nodes[i] = false;  //remove node from graph
                csc->remaining -= 1;
            }
        }
    }
    free(no_edge_in);
    free(no_edge_out);
    return(to_trim);
}

bool* my_rec_csc_trim(struct Csc *csc){
    bool has_changed = true;
    bool* to_trim = (bool*)calloc(csc->n, sizeof(bool));
    if (to_trim == NULL){
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    while(has_changed){
        has_changed = false;
        my_csc_trim(csc, to_trim, &has_changed);
    }
    return to_trim;
}