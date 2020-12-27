#ifndef LIBTRACE_H_
#define LIBTRACE_H_

#include <sys/user.h>

#define WORD_SIZE (sizeof(long))

typedef unsigned char byte;

typedef struct ftrace_s ftrace_t;
typedef struct state_s state_t;

/* TODO: Improvement - Transform this structure into calls */
struct state_s {
    int signal;

    struct user_regs_struct regs;

    /* TODO: Specialise this union into well-represented opcode structure */
    union {
        long word;
        byte bytes[WORD_SIZE];
    } data;
};

typedef int (*crawler_fptr)(ftrace_t *ftrace);
int launch_ftrace(crawler_fptr crawler, char *argv[], char *arge[]);

int ftrace_loop(ftrace_t *ftrace, state_t *state);

#endif /* LIBTRACE_H_ */
