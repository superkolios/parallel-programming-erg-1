#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <mmio.h>
#include <my_csc.h>
#include <my_scc.h>
#include <time.h>


int main(int argc, char *argv[]){

    if (argc != 2){
        fprintf(stderr, "Usage: %s [matrix-market-filename]\n", argv[0]);
        exit(1);
    }

    struct Csc csc;
    clock_t seconds;
    seconds = clock();
    my_csc_mtx_to_csc(&csc, argv[1]);
    printf("read file and create matrix: %fs\n", ( clock() - seconds) / (float)(float)CLOCKS_PER_SEC);
    // seconds = clock();
    // // printf("mtx done\n");
    // bool *trim = my_rec_csc_trim(&csc);
    // printf("trim: %fs\n", (clock() - seconds) / (float)(float)CLOCKS_PER_SEC);
    // int num_of_scc = 0;
    // for (int i = 0; i < csc.n; i++){
    //     if (trim[i]){
    //         // printf("css %d: %d\n", i, i);
    //         num_of_scc += 1;
    //     }
    // }
    // printf("\n");
    // free(trim);

    int *result;
    seconds = clock();
    result = my_coloring_scc_algorithm(&csc);
    printf("my_coloring_scc_algorithm: %fs\n", (clock() - seconds) / (float)CLOCKS_PER_SEC);
    // printf("num of trimmed scc: %d\n", num_of_scc);
    // for (int i = 0; i< csc.n; i++){
    //     printf("%d %d\n", i, result[i]);
    // }
    // printf("\n");
    free(result);
    my_csc_free(&csc);
    return(0);
}

