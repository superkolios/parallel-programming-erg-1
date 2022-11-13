#include <stdio.h>
#include <mmio.h>
#include <my_csc.h>
#include <my_coloring_algorithm.h>


int main(int argc, char *argc[]){

    if (argc != 2){
        fprintf(stderr, "Usage: %s [martix-market-filename]\n", argv[0]);
        exit(1);
    }

    struct Csc csc;
    my_csc_mtx_to_csc(&csc, argv[1]);

    my_csc_trim(&csc);

    int *result;
    my_coloring_scc_algorithm(&csc, &result);

    //print results
    return(0);
}