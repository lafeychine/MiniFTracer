/*
** EPITECH PROJECT, 2019
** [PSU] ftrace
** File description:
** Signals
*/

#include <signal.h>
#include <unistd.h>

int main(void)
{
    pid_t pid = getpid();

    kill(pid, SIGUSR1);
}
