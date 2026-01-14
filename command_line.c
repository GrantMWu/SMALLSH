#include "command_line.h"
#include "signal.h"

struct command_line *parse_input()
{
    char input[INPUT_LENGTH];
    struct command_line *curr_command = (struct command_line *) calloc(1,
    sizeof(struct command_line));
    
    // Get input
    printf(": ");
    fflush(stdout);
    char* result = fgets(input, INPUT_LENGTH, stdin);

    if (result == NULL)
    {
        clearerr(stdin);  // Clear the error state
        return curr_command;  // Return empty command (will be ignored)
    }
    
    // Tokenize the input
    char *token = strtok(input, " \n");
    while(token)
    {
        if(!strcmp(token,"<"))
        {
            curr_command->input_file = strdup(strtok(NULL," \n"));
        } 
        else if(!strcmp(token,">"))
        {
            curr_command->output_file = strdup(strtok(NULL," \n"));
        }
        else if(!strcmp(token,"&"))
        {
            if (!fg_only())
            {
                curr_command->is_bg = true;
            }
        }
        else
        {
            curr_command->argv[curr_command->argc++] = strdup(token);
        }

        token=strtok(NULL," \n");
    }

    return curr_command;
}

bool ignore_line(struct command_line* command_line)
{
    char* first_arg = command_line->argv[0];

    if (first_arg == 0 || strncmp(first_arg, "#", 1) == 0) return true;

    return false;

}

