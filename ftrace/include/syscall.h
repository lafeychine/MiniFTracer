#ifndef SYSCALL_H_
#define SYSCALL_H_

typedef struct syscall_s syscall_t;

struct syscall_s {
    int nargs;
    char *name;
};

/* Will be generated during build */
extern syscall_t sys_interrupt_table[];
extern syscall_t sys_syscall_table[];

#endif /* SYSCALL_H_ */
