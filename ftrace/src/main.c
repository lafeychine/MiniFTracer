#include "libtrace.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int crawler(ftrace_t *ftrace);

int main(int argc, char *argv[], char *arge[])
{
    if ((argc < 2) || (!(strcmp(argv[1], "-h")))) {
        printf("USAGE: %s <command>\n", argv[0]);
        return (EXIT_SUCCESS);
    }
    if (!(launch_ftrace(crawler, argv + 1, arge))) {
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
