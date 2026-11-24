#pragma once
#include <stdio.h>

struct command
{
    size_t token_num;
    size_t max_size;
    size_t current_cmd_idx;
    char** token;
};

