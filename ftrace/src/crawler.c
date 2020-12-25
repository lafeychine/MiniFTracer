#include "libtrace.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void print_child_signal(int status);
void is_syscall(ftrace_t *ftrace);

static int analyse_step(ftrace_t *ftrace)
{
    is_syscall(ftrace);

    return (1);
}

int crawler(ftrace_t *ftrace)
{
    while (ftrace_loop(ftrace)) {
        if (!(analyse_step(ftrace))) {
            return (0);
        }
    }
    print_child_signal(ftrace_get_child_signal(ftrace));
    return (1);
}
