#include "ftrace.h"

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int ftrace_fork(ftrace_t *ftrace, crawler_fptr crawler, char *argv[], char *arge[]);

static int ftrace_begin(ftrace_t *ftrace, char const binary_name[])
{
    int binary_fd = open(binary_name, O_RDONLY);

    if (binary_fd == -1) {
        perror("Open binary file");
        return (0);
    }

    /* TODO: LibELF */
    /* https://sourceforge.net/projects/elftoolchain/files/Documentation/libelf-by-example/ */

    ftrace->binary_fd = binary_fd;
    return (1);
}

static int ftrace_end(ftrace_t *ftrace)
{
    close(ftrace->binary_fd);
    return (1);
}

int launch_ftrace(crawler_fptr crawler, char *argv[], char *arge[])
{
    ftrace_t ftrace;

    memset(&(ftrace), 0, sizeof(ftrace));
    if (!(ftrace_begin(&(ftrace), argv[0]))) {
        return (0);
    }

    if (!(ftrace_fork(&(ftrace), crawler, argv, arge))) {
        ftrace_end(&(ftrace));
        return (0);
    }

    if (!(ftrace_end(&(ftrace)))) {
        return (0);
    }
    return (1);
}
