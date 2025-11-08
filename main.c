#include <stdio.h>
#include <stdbool.h>

#include "command_line.h"

int main()
{
    struct command_line *curr_command;
    while(true)
    {
        curr_command = parse_input();
        if (ignore_line(curr_command)) continue;

        printf("Do some stuff with the command line\n");
    }

    return EXIT_SUCCESS;
}
