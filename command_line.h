#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_LENGTH 2048
#define MAX_ARGS 512

struct command_line
{
    char *argv[MAX_ARGS + 1];
    int argc;
    char *input_file;
    char *output_file;
    bool is_bg;
};

/**
 * @brief Parses the input entered on the command line
 *
 * @return A command_line struct 
 */
struct command_line* parse_input();

/**
 * @brief Checks if a command is a comment or blank line
 *
 * @param A pointer to the command_line struct to check
 *
 * @return true if line should be ignored, false otherwise
 */
bool ignore_line(struct command_line* command_line);
