#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

static char const *get_signal_name(int status)
{
    if (WIFSIGNALED(status)) {
        return (strsignal(WTERMSIG(status)));
    }
    return (strsignal(WSTOPSIG(status)));
}

void print_child_signal(int status)
{
    if (WIFSIGNALED(status) || WIFSTOPPED(status)) {
        printf("Received signal %s\n", get_signal_name(status));
    } else if (WIFEXITED(status)) {
        printf("+++ exited with %d +++\n", WEXITSTATUS(status));
    }
}
