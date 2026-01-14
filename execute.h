#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

#include "command_line.h"

enum builtin_result
{
    BUILTIN_EXIT,
    BUILTIN_HANDLED,
    BUILTIN_NONE
};

/**
 * @brief runs the three builtin functions
 *
 * the "cd", "exit", and "status" commands
 * are builtin functions for the smallsh
 *
 * @params pointer to command line struct
 * @return builtin_result
 */
enum builtin_result builtin(struct command_line* command_line);

/**
 * @brief change directory to specified path
 *
 * @params {char**} path_ptr - pointer to path to directory
 */
void change_directory(char** path_ptr);

/**
 * @brief show the status of the last executing process
 *
 * @params {int} status - status of the last run process
 */
void show_status(int status);

void exec_other(struct command_line* command_line);

void redirect_io(struct command_line* command_line);

void reap_processes();
