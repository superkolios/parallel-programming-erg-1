#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <mmio.h>
#include <my_csc.h>
#include <my_scc.h>


int main(int argc, char *argv[]){

    if (argc != 2){
        fprintf(stderr, "Usage: %s [matrix-market-filename]\n", argv[0]);
        exit(1);
    }

    struct Csc csc;
    my_csc_mtx_to_csc(&csc, argv[1]);
    // printf("mtx done\n");
    bool *trim = my_rec_csc_trim(&csc);
    
    for (int i = 0; i < csc.n; i++){
        if (trim[i]){
            printf("css %d: %d\n", i, i);
        }
    }
    printf("\n");
    int *result;
    my_coloring_scc_algorithm(&csc);
    return(0);
}

