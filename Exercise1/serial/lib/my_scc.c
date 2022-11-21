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
                // printf("+size: %d\n", *size);
                // printf("add: %d\n", node);
            }
        }
    }
    int counter2 = 0;
    int *scc = (int*)malloc(*size * sizeof(int));
    for (int i = 0; i < csc->n; i++){
        if (visited[i]){
            // printf("add%d: %d\n", c, i);
            scc[counter2] = i;
            csc->valid_nodes[i] = false;
            csc->remaining -= 1;
            counter2++;
        }
        if (counter2 == *size){
            break;
        }
    }
    // printf("----------------------\nsize: %d\n", *size);
    return scc;
}


void my_coloring_scc_algorithm(struct Csc *csc){
    int* colors = (int*)malloc(csc->n * sizeof(int));
    bool colors_changed;


    for (int i=0; i < csc->n; i++){
        colors[i] = i;
    }

    while (csc->remaining != 0){
        // printf("remaining: %d\n", csc->remaining);
        for (int i=0; i < csc->n; i++){
            if(csc->valid_nodes[i]){
                colors[i] = i;
            }
        }
        colors_changed = true;
        while (colors_changed){
            colors_changed = false;
            for (int v = 0; v < csc->n; v++){
                // printf("%d\n", v);
                if(!csc->valid_nodes[v])
                    continue;
                // printf("%d\n", v);
                int start = csc->col_index[v];
                int end = csc->col_index[v+1];
                for (int u = start; u < end; u++){
                    // if(v==46){
                    //     printf("v:46 u:%d", csc->row_index[u]);
                    //     if(csc->valid_nodes[csc->row_index[u]])
                    //         printf(" valid");
                    //     printf("\n");
                    // }
                    if(!csc->valid_nodes[csc->row_index[u]])
                        continue;
                    if (colors[v] > colors[csc->row_index[u]]){
                        colors[v] = colors[csc->row_index[u]];
                        colors_changed = true;
                        break;  //we can break because we want colors[v] to take the smallest color of his predecessors and they are sorted.
                    }
                }
            }
        }
        // printf("coloring done.\n");
        // for (int i = 0; i < csc->n; i++){
        //     printf("%d: %d\n",i, colors[i]);
        // }
        // exit(0);
        // int* unique_colors;
        bool* checked_colors = calloc(csc->n, sizeof(bool));
        int c;
        // printf("colors[23]:%d",colors[23]);
        // printf("colors[46]:%d",colors[46]);
        // printf("remaining: %d\n", csc->remaining);
        for (int i=0; i < csc->n; i++){
            // printf("i: %d\n", i);
            c = colors[i];
            if (!csc->valid_nodes[i] || checked_colors[c])
                continue;
            // if(i == 23 || i == 46)
            //     printf("%d %d\n", i, c);
            int size;
            int *scc = bfs(csc, c, colors, &size);
            // printf("unique_colors: %d\n", c);
            // printf("size: %d\n", size);
            printf("scc %d: ",c);
            for (int j=0; j < size; j++){
                printf("%d ", scc[j]);
            }
            printf("\n\n");
            checked_colors[c] = true;
        }
    }
    printf("\n\n");
    for (int i = 0; i< csc->n; i++){
        printf("%d  %d\n", i, colors[i]);
    }
}