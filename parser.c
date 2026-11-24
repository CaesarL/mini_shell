#include <stdlib.h>
#include <string.h>
#include <parser.h>


// parser cmd into input.token
struct command parser_cmd(char* buffer)
{
    struct command input;
    
    char* digit = " \f\r\t\v\n";
    char* tmp_buffer;

    tmp_buffer = strtok(buffer, digit);
    input.token = (char**)malloc(sizeof(char*));
    input.token_num = 0;
    input.max_size = 1;
    input.current_cmd_idx = 0;
    
    while(tmp_buffer != NULL)
    {
        input.token[input.token_num] = (char*)malloc(sizeof(tmp_buffer));
        input.token[input.token_num] = tmp_buffer;
        input.token_num++;
        
        if(input.token_num >= input.max_size / 2)
        {
            input.max_size *= 2;
            input.token = (char**)realloc(input.token, sizeof(char*) * input.max_size);
        }
        tmp_buffer = strtok(NULL, digit);
    }
    return input;
}

int is_number_pipe(char* buffer, int* num)
{
    if((strlen(buffer) < 2) || (buffer[0] != "!" && buffer[0] != "|"))
    {
        return 0;
    }
    else
    {
        *num = atoi(buffer + 1);
        return (*num > 0) ? 1 : 0;
    }
}
