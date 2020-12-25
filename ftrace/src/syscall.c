#include "syscall.h"

#include "libtrace.h"

#include <stdio.h>

void is_syscall(ftrace_t *ftrace)
{
    byte buffer[WORD_SIZE] = { 0 };

    ftrace_get_opcode_word(ftrace, buffer);

    if (buffer[0] == 0x0f && buffer[1] == 0x05) {
        printf("Syscall\n");
    }
    if (buffer[0] == 0xCD && buffer[1] == 0x80) {
        printf("Syscall - Interrupt\n");
    }
}
