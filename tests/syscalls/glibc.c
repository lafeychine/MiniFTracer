#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    syscall(SYS_write, 1, "Hello World\n", 12);
    syscall(SYS_exit, 0);
}
