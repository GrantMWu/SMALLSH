#include "execute.h"

enum builtin_result builtin(struct command_line* command_line)
{
    char* command = command_line->argv[0];
    if (strncmp(command, "exit", 4) == 0)
    {
        // handle child processes
        return BUILTIN_EXIT;
    }
    else if (strncmp(command, "cd", 2) == 0)
    {
        // handle directory change
        change_directory(&command_line->argv[1]);
        fflush(stdout);
        return BUILTIN_HANDLED;
    }
    else if (strncmp(command, "status", 6) == 0)
    {
        // show status
        printf("0\n");
        fflush(stdout);
        return BUILTIN_HANDLED;
    }

    return BUILTIN_NONE;
}        

void change_directory(char** path_ptr)
{
    char* filepath = (*path_ptr == NULL) ? getenv("HOME") : *path_ptr;
    chdir(filepath);
}

void exec_other(struct command_line* command_line)
{
    pid_t child_pid;
    switch(child_pid = fork())
    {
        case -1:
            perror("fork");
            exit(1);
        
        case 0:
            execvp(command_line->argv[0], command_line->argv); 
            perror("execvp failed");
            exit(EXIT_FAILURE);

        default:

            break;
    }
}
