#include "ftrace.h"

#include <stdio.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>

static int is_signal_recieved(int status)
{
    if (WIFSIGNALED(status)) {
        return (1);
    }
    if (WIFSTOPPED(status)) {
        if (WSTOPSIG(status) != SIGSTOP && WSTOPSIG(status) != SIGTRAP) {
            return (1);
        }
    }
    if (WIFEXITED(status)) {
        return (1);
    }
    return (0);
}

static void ftrace_peek_data(pid_t pid, state_t *state)
{
    ptrace(PTRACE_GETREGS, pid, NULL, &(state->regs));
    state->data.word = ptrace(PTRACE_PEEKTEXT, pid, state->regs.rip, NULL);
}

static int ftrace_process_loop(ftrace_t *ftrace)
{
    int status;

    ptrace(PTRACE_SINGLESTEP, ftrace->child_pid, NULL, NULL);

    if (waitpid(ftrace->child_pid, &(status), 0) == -1) {
        perror("Wait pid");
        return (0);
    }

    ftrace->state.signal = status;
    if (is_signal_recieved(status)) {
        return (0);
    }

    ftrace_peek_data(ftrace->child_pid, &(ftrace->state));
    return (1);
}

int ftrace_loop(ftrace_t *ftrace, state_t *state)
{
    int rc = ftrace_process_loop(ftrace);

    memcpy(state, &(ftrace->state), sizeof(ftrace->state));
    return (rc);
}
