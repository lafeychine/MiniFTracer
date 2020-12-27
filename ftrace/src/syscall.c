#include "syscall.h"

#include "libtrace.h"

#include <stdio.h>
#include <sys/user.h>

typedef struct syscall_info_s {
    unsigned long long id;
    unsigned long long arg_1, arg_2, arg_3, arg_4, arg_5, arg_6;
} syscall_info_t;

static int entering_syscall(syscall_t syscall[], syscall_info_t *args)
{
    printf("%s\n", syscall[args->id].name);
    return (1);
}

static int entering_syscall_interrupt(struct user_regs_struct *regs)
{
    syscall_info_t args = {
        regs->rax,
        regs->rbx, regs->rcx, regs->rdx, regs->rsi, regs->rdi, regs->rbp
    };

    return (entering_syscall(sys_interrupt_table, &(args)));
}

static int entering_syscall_fast(struct user_regs_struct *regs)
{
    syscall_info_t args = {
        regs->rax,
        regs->rdi, regs->rsi, regs->rdx, regs->r10, regs->r8, regs->r9
    };

    return (entering_syscall(sys_interrupt_table, &(args)));
}

int is_syscall(state_t *state)
{
    byte *buffer = state->data.bytes;

    /* Check syscall by interrupt 0x80: Legacy interface */
    if (buffer[0] == 0x0f && buffer[1] == 0x05) {
        return (entering_syscall_interrupt(&(state->regs)));
    }

    /* Check syscall by syscall instruction: Fast syscall */
    if (buffer[0] == 0xCD && buffer[1] == 0x80) {
        return (entering_syscall_fast(&(state->regs)));
    }
    return (1);
}
