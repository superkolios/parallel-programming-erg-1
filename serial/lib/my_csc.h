struct Csc{
    int nz;
    int n;
    int m;
    int* row_index;
    int* col_index;
    bool* valid_nodes;
    int remaining;
};

int my_csc_mtx_to_csc(struct Csc *csc, char* file);
void my_csc_free(struct Csc *csc);
bool* my_rec_csc_trim(struct Csc *csc, int *num_of_scc);