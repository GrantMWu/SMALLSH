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
        // Check for completed background processes
        pid_t child_pid;
        int child_status;
        while ((child_pid = waitpid(-1, &child_status, WNOHANG)) > 0) 
        {
            printf("background pid %d is done: ", child_pid);
            show_status(child_status);
        }

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
