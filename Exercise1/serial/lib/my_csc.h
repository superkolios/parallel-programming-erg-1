struct Csc{
    int nz;
    int n;
    int m;
    int* row_index;
    int* col_index;
};

int my_csc_mtx_to_csc(struct Csc *csc, char* file);
bool* my_csc_trim(struct Csc *csc);