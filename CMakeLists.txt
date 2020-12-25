# Minimum CMake version
cmake_minimum_required(VERSION 3.15)

# Project "ftrace"
project(ftrace C ASM_NASM)

# Set C language standard to GNU-99
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS ON)

# This project requires Python3 to be build
find_package(Python3 REQUIRED COMPONENTS Interpreter)

add_subdirectory(libtrace)
add_subdirectory(ftrace)


# Specify ASM linker
set(CMAKE_ASM_NASM_LINK_EXECUTABLE "ld <CMAKE_ASM_NASM_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")

add_executable(call_ind tests/call_ind.asm)
add_executable(call_rel tests/call_rel.asm)

add_executable(sys_glibc     tests/syscalls/glibc.c)
add_executable(sys_interrupt tests/syscalls/interrupt.asm)
add_executable(sys_syscall   tests/syscalls/syscall.asm)
