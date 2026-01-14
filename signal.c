#include "signal.h"

static bool background_enabled = 1;

void handle_SIGTSTP(int signo)
{
    if (background_enabled)
    {
        char* message = "Entering foreground-only mode (& is now ignored)\n";
        write(STDOUT_FILENO, message, 50);
        background_enabled = 0;
    }
    else
    {
        char* message = "Exiting foreground-only mode\n";
        write(STDOUT_FILENO, message, 30);
        background_enabled = 1;
    }
    fflush(stdout);
}

bool fg_only()
{
    if (background_enabled == 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void redirect_signals()
{
    // handle SIGINT
    struct sigaction SIGINT_action = {0};
    SIGINT_action.sa_handler = SIG_IGN;
    sigemptyset(&SIGINT_action.sa_mask);
    SIGINT_action.sa_flags = 0;
    sigaction(SIGINT, &SIGINT_action, NULL);
    
    // handle the SIGTSTP with custom handler
    struct sigaction SIGTSTP_action = {0};
    SIGTSTP_action.sa_handler = handle_SIGTSTP;
    sigemptyset(&SIGTSTP_action.sa_mask);
    SIGTSTP_action.sa_flags = 0;
    sigaction(SIGTSTP, &SIGTSTP_action, NULL);
}

void redirect_child(bool is_bg)
{
    // handle the SIGINT with ignore for background process, default otherwise
    struct sigaction SIGINT_action = {0};
    SIGINT_action.sa_handler = (is_bg) ? SIG_IGN : SIG_DFL;
    sigemptyset(&SIGINT_action.sa_mask);
    SIGINT_action.sa_flags = 0;
    sigaction(SIGINT, &SIGINT_action, NULL);

    // ignore the SIGTSTP
    struct sigaction SIGTSTP_action = {0};
    SIGTSTP_action.sa_handler = SIG_IGN;
    sigemptyset(&SIGTSTP_action.sa_mask);
    SIGTSTP_action.sa_flags = 0;
    sigaction(SIGTSTP, &SIGTSTP_action, NULL);
}
