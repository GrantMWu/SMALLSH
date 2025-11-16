#include "signal.h"

static bool tstp_recieved = 0;

void handle_SIGTSTP(int signo)
{
    char* message = "signal terminal stop\n";
    write(STDOUT_FILENO, message, 21);
    fflush(stdout);
}

void check_tstp_message()
{
    if (tstp_recieved == 1)
    {
        tstp_recieved = 0;
        char* message = "signal terminal stop\n";
        write(STDOUT_FILENO, message, 21);
        fflush(stdout);
    }
}
void redirect_signals()
{
    // handle sigint
    struct sigaction SIGINT_action = {0};
    SIGINT_action.sa_handler = SIG_IGN;
    sigemptyset(&SIGINT_action.sa_mask);
    SIGINT_action.sa_flags = 0;
    sigaction(SIGINT, &SIGINT_action, NULL);
    
    // handle the sigtstp
    struct sigaction SIGTSTP_action = {0};
    SIGTSTP_action.sa_handler = handle_SIGTSTP;
    sigemptyset(&SIGTSTP_action.sa_mask);
    SIGTSTP_action.sa_flags = 0;
    sigaction(SIGTSTP, &SIGTSTP_action, NULL);
}

void redirect_child(bool is_bg)
{
    // handle the sigint
    struct sigaction SIGINT_action = {0};
    SIGINT_action.sa_handler = (is_bg) ? SIG_IGN : SIG_DFL;
    sigemptyset(&SIGINT_action.sa_mask);
    SIGINT_action.sa_flags = 0;
    sigaction(SIGINT, &SIGINT_action, NULL);

    // handle the sigtstp
    struct sigaction SIGTSTP_action = {0};
    SIGTSTP_action.sa_handler = SIG_IGN;
    sigemptyset(&SIGTSTP_action.sa_mask);
    SIGTSTP_action.sa_flags = 0;
    sigaction(SIGTSTP, &SIGTSTP_action, NULL);
}
