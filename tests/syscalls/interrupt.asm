BITS 64                         ; 64-bit mode

INT_EXIT EQU 1                  ; Exit number syscall
INT_WRITE EQU 4                 ; Write number syscall

SECTION .text                   ; [Code section]

GLOBAL _start                   ; Export ‘_start’

_start:
    PUSH RBP                    ; Prologue:
    MOV RBP, RSP                ; Stack frame setup

    MOV EAX, INT_WRITE          ; Syscall number
    MOV EBX, 1                  ; First parameter
    MOV ECX, str                ; Second parameter
    MOV EDX, len_str            ; Third parameter
    INT 0x80                    ; System call: write()

    MOV EAX, INT_EXIT           ; Syscall number
    MOV EBX, 0                  ; Return value
    INT 0x80                    ; System call: exit(0)


SECTION .rodata                 ; [Read-only data section]

str: DB 'Hello World', 10, 0    ; String ‘Hello world’
len_str EQU $ - str             ; Length of the string
