BITS 64                         ; 64-bit mode

SYS_EXIT EQU 60                 ; Exit number syscall

SECTION .text                   ; [Code section]

GLOBAL _start                   ; Export ‘_start’

_my_add:
    PUSH RBP                    ; Prologue:
    MOV RBP, RSP                ; Stack frame setup

    MOV RAX, RSI
    ADD RAX, RDI

    MOV RSP, RBP                ; Epilogue:
    POP RBP                     ; Stack frame setup
    RET                         ; Return

_start:
    PUSH RBP                    ; Prologue:
    MOV RBP, RSP                ; Stack frame setup

    MOV RSI, 24
    MOV RDI, 12
    MOV RBX, _my_add            ; Move _my_add into RBX

    CALL RBX                    ; Call ind

    MOV RDI, RAX                ; First parameter
    MOV RAX, SYS_EXIT           ; Syscall number
    SYSCALL                     ; System call: exit(0)
