#include "ftrace.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <unistd.h>

static int ftrace_tracee(int binary_fd, char *argv[], char *arge[])
{
    /* TODO: Mute the tracee */

    if (ptrace(PTRACE_TRACEME, 0L, NULL, NULL) == -1) {
        perror("Trace the tracee");
        return (1);
    }
    raise(SIGSTOP);
    fexecve(binary_fd, argv, arge);
    perror("Execute the tracee");
    return (1);
}

int ftrace_fork(ftrace_t *ftrace, crawler_fptr crawler, char *argv[], char *arge[])
{
    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork the tracee");
        return (0);
    }
    if (pid == 0) {
        exit(ftrace_tracee(ftrace->binary_fd, argv, arge));
    }

    ftrace->child_pid = pid;
    return (crawler(ftrace));
}
