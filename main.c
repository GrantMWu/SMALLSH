#include <stdio.h>
#include <stdbool.h>

#include "command_line.h"
#include "execute.h"
#include "signal.h"

int main()
{
    struct command_line *curr_command;
    
    while(true)
    {
        reap_processes();

        redirect_signals();

        // parse command line
        curr_command = parse_input();

        // check for comment or blank line
        if (ignore_line(curr_command)) continue;

        // check for built-in function
        enum builtin_result result = builtin(curr_command);
        if (result == BUILTIN_EXIT)
        {
            break;
        }    
        else if (result == BUILTIN_HANDLED)
        {
            continue;
        }

        // fork() and exec()
        exec_other(curr_command);
         
    }

    return EXIT_SUCCESS;
}
