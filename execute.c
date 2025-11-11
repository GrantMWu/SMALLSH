#include "execute.h"

static int fg_status = 0;

enum builtin_result builtin(struct command_line* command_line)
{
    char* command = command_line->argv[0];
    if (strcmp(command, "exit") == 0)
    {
        // handle child processes
        return BUILTIN_EXIT;
    }
    else if (strcmp(command, "cd") == 0)
    {
        // handle directory change
        change_directory(&command_line->argv[1]);
        fflush(stdout);
        return BUILTIN_HANDLED;
    }
    else if (strcmp(command, "status") == 0)
    {
        // show status
        if (WIFEXITED(fg_status))
        {
            printf("exit value %d\n", WEXITSTATUS(fg_status));
        }
        else if (WIFSIGNALED(fg_status))
        {
            printf("terminated by signal %d\n", WTERMSIG(fg_status));
        }
        fflush(stdout);
        return BUILTIN_HANDLED;
    }

    return BUILTIN_NONE;
}        

void change_directory(char** path_ptr)
{
    char* filepath = (*path_ptr == NULL) ? getenv("HOME") : *path_ptr;
    if (chdir(filepath) == -1)
        perror(filepath);
}

void exec_other(struct command_line* command_line)
{
    pid_t child_pid;
    int child_status;

    switch(child_pid = fork())
    {
        case -1:
            perror("fork");
            exit(1);
        
        case 0:
            // redirect the input and output files if needed
            redirect_io(command_line->input_file, command_line->output_file);

            // execute command
            execvp(command_line->argv[0], command_line->argv); 
            fprintf(stderr, "%s: %s\n", command_line->argv[0], strerror(errno));
            exit(EXIT_FAILURE);

        default:
            waitpid(child_pid, &child_status, 0);
            fg_status =  child_status;
            break;
    }
}

void redirect_io(char* input, char* output)
{
    if (input) 
    {
        // open input file for read only
        int inFD = open(input, O_RDONLY);
        if (inFD == -1)
        {
            perror("source open()");
            exit(1);
        }

        // redirect stdin to input file
        int result = dup2(inFD, 0);
        if (result == -1)
        {
            perror("source dup2()");
            exit(1);
        }
    }

    if (output) 
    {
        // open output file for read only
        int outFD = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (outFD == -1)
        {
            perror("target open()");
            exit(1);
        }

        // redirect stdout to output file
        int result = dup2(outFD, 1);
        if (result == -1)
        {
            perror("target dup2()");
            exit(1);
        }
    }
}
