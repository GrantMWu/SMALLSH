#include <stdio.h>
#include <stdbool.h>

#include "command_line.h"

int main()
{
    struct command_line *curr_command;
    while(true)
    {
        curr_command = parse_input();
    }

    return EXIT_SUCCESS;
}
