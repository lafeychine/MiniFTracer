#ifndef FTRACE_H_
#define FTRACE_H_

#include "libtrace.h"

#include <sys/types.h>
#include <sys/user.h>

struct ftrace_s {
    int binary_fd;

    pid_t child_pid;

    state_t state;
};

#endif /* FTRACE_H_ */
