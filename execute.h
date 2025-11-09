#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#include "command_line.h"

enum builtin_result
{
    BUILTIN_EXIT,
    BUILTIN_HANDLED,
    BUILTIN_NONE
};

enum builtin_result builtin(struct command_line* command_line);

void change_directory(char** path_ptr);

void exec_other(struct command_line* command_line);

