#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <mmio.h>
#include <my_csc.h>
#include <my_scc.h>
#include <time.h>
#include <omp.h>

int main(int argc, char *argv[]){
    // omp_set_num_threads(2);
    if (argc != 2){
        fprintf(stderr, "Usage: %s [matrix-market-filename]\n", argv[0]);
        exit(1);
    }

    struct Csc csc;
    double seconds;
    seconds = omp_get_wtime();
    my_csc_mtx_to_csc(&csc, argv[1]);
    printf("read file and create matrix: %fs\n", omp_get_wtime() - seconds);

    int *result;
    seconds = omp_get_wtime();
    result = my_coloring_scc_algorithm(&csc);
    printf("my_coloring_scc_algorithm: %fs\n", omp_get_wtime() - seconds);
    for (int i = 0; i< csc.n; i++){
        printf("%d %d\n", i, result[i]);
    }
    free(result);
    my_csc_free(&csc);
    return(0);
}
