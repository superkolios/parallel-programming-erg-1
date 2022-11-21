#include <my_csc.h>
#include <stdbool.h>

remove_from_graph(struct Csc *csc, bool* to_remove){
    for(int i=0; i< csc->n; i++){
        if (to_remove[i]){
            csc->valid_nodes[i] = false;
        }
    }
}

bool* create_subgraph(struct Csc *csc, int c, int* colors){
    bool *valid_nodes = (bool*)malloc(csc->n * sizeof(bool))
    for(int i=0; i< csc->n; i++){
        if (colors[i] == c){
            valid_nodes[i] = true;
        }
        else{
            valid_nodes[i] = false;
        }
    }
    return(valid_nodes)
}

// create_subgraph(struct Csc *csc, int c, int* colors){
//     struct Csc g;
//     int counter = 0;

//     for (int v = 0; v < csc->n; v++){
//         g.col_index[v] = counter;
//         if (colors[v] != c)
//             continue;

//         int start = csc->col_index[v];
//         int end = csc->col_index[v + 1];
//         for (u = start; u < end; u++){
//             if (colors[u] != c)
//                 continue;
//             g.row_index[counter] = u;
//             counter++;
//         } 
//     }
//     g.col_index[csc->n] = counter;
//     return(g);
// }

// remove_from_graph(struct Csc *csc, bool* to_remove){
//     struct Csc g;
//     int counter = 0;

//     for (int v = 0; v < csc->n; v++){
//         g.col_index[v] = counter;
//         if (to_remove[v])
//             continue;

//         int start = csc->col_index[v];
//         int end = csc->col_index[v + 1];
//         for (u = start; u < end; u++){
//             if (to_remove[u])
//                 continue;
//             g.row_index[counter] = u;
//             counter++;
//         } 
//     }
//     g.col_index[csc->n] = counter;
//     return(g);
// }

int bfs(struct Csc csc, int s, int* colors){
    bool *visited = (bool*)malloc(csc->n * sizeof(bool));
    for(int i = 0; i < csc->n; i++){
        visited[i] = false;
    }    

    int *to_visit = (int*)malloc(csc->n * sizeof(int));
    to_visit[0] = s;
    int to_visit_prt = 1;
    int counter = 1;

    while (to_visit_prt < 0){
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
                counter++;
            }
        }
    }
    int counter2 = 0;
    int *scc = (int*)malloc(counter * sizeof(int));
    for (int i = 0; i < csc->n; i++){
        if (visited[i]){
            scc[counter2] = i;
            counter2++;
        }
        if (counter2 == counter - 1){
            break;
        }
    }
    return visited;
}


my_coloring_scc_algorithm(struct Scs *csc){
    int* colors = (int*)malloc(csc->n * sizeof(int))
    bool colors_changed = true;

    while (csc->nz != 0){
        for (int i=0; i < csc->n; i++){
            if(csc->valid_nodes[i]){
                colors[i] = i;
            }
        }
        while (colors_changed){
            colors_changed = false;
            for (int v = 0; v < csc->n; v++){
                if(!csc->valid_nodes[v])
                    continue;
                int start = csc->col_index[i];
                int end = csc->col_index[i+1];
                for (int u = start; u < end; u++){
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

        int* unique_colors;
        bool* checked_colors = calloc(csc->n, sizeof(bool));
        int c;
        for (int i; c < csc->n; i++){
            c = colors[i]
            if (!(csc->valid_nodes[c] || checked_colors[c]))
                continue;
            scc = bfs(&csc, c, colors)
        }
    }
}