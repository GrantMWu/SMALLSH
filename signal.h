#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void handle_SIGINT(int signo);

void handle_SIGTSTP(int signo);

void redirect_signals();

void redirect_fg_child();
