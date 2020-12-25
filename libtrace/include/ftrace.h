#ifndef FTRACE_H_
#define FTRACE_H_

#include "libtrace.h"

#include <sys/types.h>
#include <sys/user.h>

typedef struct state_s state_t;

struct state_s {
    int signal;
    struct user_regs_struct regs;
    union {
        long word;
        byte bytes[WORD_SIZE];
    } data;
};

struct ftrace_s {
    int binary_fd;

    pid_t child_pid;

    state_t state;
};

#endif /* FTRACE_H_ */
