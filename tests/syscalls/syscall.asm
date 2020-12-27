BITS 64                         ; 64-bit mode

SYS_WRITE EQU 1                 ; Write number syscall
SYS_EXIT EQU 60                 ; Exit number syscall

SECTION .text                   ; [Code section]

GLOBAL _start                   ; Export ‘_start’

_start:
    PUSH RBP                    ; Prologue:
    MOV RBP, RSP                ; Stack frame setup

    MOV RAX, SYS_WRITE          ; Syscall number
    MOV RDI, 1                  ; First parameter
    MOV RSI, str                ; Second parameter
    MOV RDX, len_str            ; Third parameter
    SYSCALL                     ; System call: write()

    MOV RAX, SYS_EXIT           ; Syscall number
    MOV RDI, 0                  ; Return value
    SYSCALL                     ; System call: exit(0)


SECTION .rodata                 ; [Read-only data section]

str: DB 'Hello World', 10       ; String ‘Hello world’
len_str EQU $ - str             ; Length of the string
