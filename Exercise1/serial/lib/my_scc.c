#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "my_csc.h"
#include <stdbool.h>


int* bfs(struct Csc *csc, int c, int* colors, int *size){
    bool *visited = (bool*)malloc(csc->n * sizeof(bool));
    for(int i = 0; i < csc->n; i++){
        visited[i] = false;
    }    

    int *to_visit = (int*)malloc(csc->n * sizeof(int));
    to_visit[0] = c;
    visited[c] = true;
    csc->valid_nodes[c] = false;
    csc->remaining -= 1;
    int to_visit_prt = 1;
    *size = 1;

    while (to_visit_prt > 0){
        int s = to_visit[to_visit_prt - 1];
        to_visit_prt--;

        int start = csc->col_index[s];
        int end = csc->col_index[s+1];
        for (int i = start; i < end; i++){
            int node = csc->row_index[i];
            if (colors[node] == c && !visited[node]){
                to_visit[to_visit_prt] = node;
                to_visit_prt++;
                visited[node] = true;
                (*size)++;
                csc->valid_nodes[node] = false;
                csc->remaining -= 1;
            }
        }
    }
    free(to_visit);
    // int counter2 = 0;
    // int *scc = (int*)malloc(*size * sizeof(int));
    // for (int i = 0; i < csc->n; i++){
    //     if (visited[i]){
    //         // printf("add%d: %d\n", c, i);
    //         scc[counter2] = i;
    //         counter2++;
    //     }
    //     if (counter2 == *size){
    //         break;
    //     }
    // }
    free(visited);
    // return scc;
    return NULL;
}


int* my_coloring_scc_algorithm(struct Csc *csc){
    int* colors = (int*)malloc(csc->n * sizeof(int));
    bool colors_changed;
    int num_of_scc=0;
    bool* trimmed;
    // for (int i=0; i < csc->n; i++){
    //     colors[i] = i;
    // }
    // trimmed = my_rec_csc_trim(csc, &num_of_scc);
    free(trimmed);
    while (csc->remaining != 0){
        for (int i=0; i < csc->n; i++){
            if(csc->valid_nodes[i]){
                colors[i] = i;
            }
        }
        my_rec_csc_trim(csc, &num_of_scc);
        free(trimmed);
        // printf("%d\n" ,csc->remaining);
        colors_changed = true;
        while (colors_changed){
            colors_changed = false;
            for (int v = 0; v < csc->n; v++){
                if(!csc->valid_nodes[v])
                    continue;
                int start = csc->col_index[v];
                int end = csc->col_index[v+1];
                for (int u = start; u < end; u++){
                    if(!csc->valid_nodes[csc->row_index[u]])
                        continue;
                    if (colors[v] > colors[csc->row_index[u]]){
                        colors[v] = colors[csc->row_index[u]];
                        colors_changed = true;
                    }
                }
            }
        }
        int c;
        for (int i=0; i < csc->n; i++){
            c = colors[i];
            if (!csc->valid_nodes[i] || c != i)
                continue;

            num_of_scc++;
            int size;
            int *scc = bfs(csc, c, colors, &size);
            // printf("scc %d: ",c);
            // for (int j=0; j < size; j++){
            //     printf("%d ", scc[j]);
            // }
            // printf("\n");
            free(scc);
        }
    }
    printf("num of scc: %d\n", num_of_scc);
    return colors;
}