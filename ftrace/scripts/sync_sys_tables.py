#!/usr/bin/env python3

from requests import get

REPO_URL = "https://raw.githubusercontent.com/strace/strace/master/"
REPO_SYS_INTERRUPT = REPO_URL + "linux/x86_64/syscallent.h"
REPO_SYS_SYSCALL = REPO_URL + "linux/64/syscallent.h"

FILE_SYS_INTERRUPT = "sys_interrupt_table.data"
FILE_SYS_SYSCALL = "sys_syscall_table.data"


def main():
    sync_file(REPO_SYS_INTERRUPT, FILE_SYS_INTERRUPT)
    sync_file(REPO_SYS_SYSCALL, FILE_SYS_SYSCALL)


def sync_file(repo, filepath):
    response = get(repo)
    with open(filepath, "wb") as outputFile:
        outputFile.write(response.content)


if __name__ == "__main__":
    main()
