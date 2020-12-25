#ifndef LIBTRACE_H_
#define LIBTRACE_H_

#define WORD_SIZE (sizeof(long))

typedef struct ftrace_s ftrace_t;

typedef unsigned char byte;

typedef int (*crawler_fptr)(ftrace_t *ftrace);

/* Errors: Tube */
int launch_ftrace(crawler_fptr crawler, char *argv[], char *arge[]);

/* */
int ftrace_loop(ftrace_t *ftrace);

int ftrace_get_child_signal(ftrace_t *ftrace);

/* TODO: Specialise this call - Opcode Structure */
void ftrace_get_opcode_word(ftrace_t *ftrace, byte buffer[WORD_SIZE]);

#endif /* LIBTRACE_H_ */
