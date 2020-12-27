#include "libtrace.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void print_child_signal(int status);
void is_syscall(state_t *state);

static int analyse_step(state_t *state)
{
    is_syscall(state);

    return (1);
}

int crawler(ftrace_t *ftrace)
{
    state_t state;

    while (ftrace_loop(ftrace, &(state))) {
        if (!(analyse_step(&(state)))) {
            return (0);
        }
    }

    print_child_signal(state.signal);
    return (1);
}
