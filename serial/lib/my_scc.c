#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "my_csc.h"
#include <stdbool.h>


void bfs(struct Csc *csc, int c, int* colors, int *size, int *to_visit, bool *visited){
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
    return;
}


int* my_coloring_scc_algorithm(struct Csc *csc){
    int* colors = (int*)malloc(csc->n * sizeof(int));
    bool colors_changed;
    int num_of_scc=0;
    bool* trimmed;
    while (csc->remaining != 0){
        for (int i=0; i < csc->n; i++){
            if(csc->valid_nodes[i]){
                colors[i] = i;
            }
        }
        trimmed = my_rec_csc_trim(csc, &num_of_scc);
        free(trimmed);
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
        int c, temp_scc_num = 0, removed_nodes = 0;
        bool *visited = (bool*)calloc(csc->n, sizeof(bool)); 
        if (visited == NULL){
            fprintf(stderr, "Memory allocation failed.\n");
            exit(1);
        }
        int *to_visit = (int*)malloc(csc->n * sizeof(int));
        if (visited == NULL){
            fprintf(stderr, "Memory allocation failed.\n");
            exit(1);
        }
        for (int i=0; i < csc->n; i++){
            c = colors[i];
            if (!csc->valid_nodes[i] || c != i)
                continue;
            num_of_scc++;
            int size;
            bfs(csc, c, colors, &size, to_visit, visited);
        }
        free(to_visit);
        free(visited);
    }
    printf("num of scc: %d\n", num_of_scc);
    return colors;
}