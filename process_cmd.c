#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>




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


void update_pipe_tbl(struct pipe_tbl *cmd_pipe_tbl, int* output_fd)
{
    for(int i = 1; i < cmd_pipe_tbl->tbl_size; ++i)
    {
        cmd_pipe_tbl->cnt_tbl[i-1][0] = cmd_pipe_tbl->cnt_tbl[i][0];
        cmd_pipe_tbl->cnt_tbl[i-1][1] = cmd_pipe_tbl->cnt_tbl[i][1];
        cmd_pipe_tbl->cnt_tbl[i][0] = 0;
        cmd_pipe_tbl->cnt_tbl[i][1] = 1;
    }
    
    /* there has pipe input from previous cmd*/
    if(cmd_pipe_tbl->cnt_tbl[0][0] != 0)
    {
        *output_fd = cmd_pipe_tbl->cnt_tbl[0][0];
        cmd_pipe_tbl->cnt_tbl[0][0] = 0;
        close(cmd_pipe_tbl->cnt_tbl[0][1]);
    }
}



char** cmd_process(struct command *input, char** separation, char** redirection, int* output_to_num_pipe)
{
    char** process = (char**)malloc(sizeof(char*) * (input->token_num + 1));
    for(int cnt = 0; input->current_cmd_idx < input->token_num; ++cnt, ++input->current_cmd_idx)
    {
        char* arg_temp = input->token[input->current_cmd_idx];
        if((strcmp(arg_temp, "|") == 0) || is_number_pipe(arg_temp, output_to_num_pipe))
        {
            // case xxx_cmd |2  or xxx_cmd !3
            if(arg_temp[0] == "!")
            {
                *separation = "!";
            }
            else
            {
                *separation = "|";
            }
            process[cnt] = NULL;
            ++input->current_cmd_idx;
            break;
        }
        else if(strcmp(arg_temp, ">") == 0)
        {
            // redirection case  xxx_cmd > yyy_cmd
            ++input->current_cmd_idx;
            *redirection = input->token[input->current_cmd_idx];    
        }
        else
        {
            process[cnt] = arg_temp;
            process[cnt + 1] = NULL;
        }
    }
    return process;
}
