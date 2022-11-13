struct Csc{
    int nz;
    int n;
    int m;
    int* row_index;
    int* col_index;
};

int mtx_to_csc(struct csc *csc, char* file);