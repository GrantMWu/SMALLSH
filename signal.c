#include "signal.h"


void handle_SIGINT(int signo)
{
    char* message = "signal interrupt\n";
    write(STDOUT_FILENO, message, 17);
}

void handle_SIGTSTP(int signo);

void redirect_signals()
{
    struct sigaction SIGINT_action = {0};
    SIGINT_action.sa_handler = SIG_IGN;
    sigemptyset(&SIGINT_action.sa_mask);
    SIGINT_action.sa_flags = 0;
    sigaction(SIGINT, &SIGINT_action, NULL);
}

void redirect_fg_child()
{
    struct sigaction SIGINT_action = {0};
    SIGINT_action.sa_handler = SIG_DFL;
    sigemptyset(&SIGINT_action.sa_mask);
    SIGINT_action.sa_flags = 0;
    sigaction(SIGINT, &SIGINT_action, NULL);
}
