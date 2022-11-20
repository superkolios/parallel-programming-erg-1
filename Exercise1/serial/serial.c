#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <mmio.h>
#include <my_csc.h>
//#include <my_coloring_algorithm.h>


int main(int argc, char *argv[]){

    if (argc != 2){
        fprintf(stderr, "Usage: %s [martix-market-filename]\n", argv[0]);
        exit(1);
    }

    struct Csc csc;
    my_csc_mtx_to_csc(&csc, argv[1]);
    bool *trim = my_rec_csc_trim(&csc);
    
    printf("trim: ");
    for (int i = 0; i < csc.n; i++){
        if (trim[i]){
            printf("%d ", i);
        }
    }
    //int *result;
    //my_coloring_scc_algorithm(&csc, &result);

    //print results
    return(0);
}

