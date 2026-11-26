#include <fcntl.h>
#include <stdlib.h>


void init_pipe_tbl(struct pipe_tbl *num_pipe_tbl, const int tbl_size)
{
    num_pipe_tbl->tbl_size = tbl_size;
    num_pipe_tbl->cnt_tbl = (int**)malloc(sizeof(int*) * tbl_size);
    
    for(int i = 0; i < tbl_size;i++)
    {
        num_pipe_tbl->cnt_tbl[i] = (int*)malloc(sizeof(int) * 2);
        num_pipe_tbl->cnt_tbl[i][0] = 0;
        num_pipe_tbl->cnt_tbl[i][1] = 0;
    }
}
