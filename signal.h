#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

void handle_SIGINT(int signo);

void handle_SIGTSTP(int signo);

void redirect_signals();

void redirect_child(bool is_bg);
