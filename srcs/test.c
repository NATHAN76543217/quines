#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main()
{
    dprintf(1, "uid = %d\neuid = %d\n", (int)getuid(), (int)geteuid);
    setuid(130);
    dprintf(1, "uid = %d\neuid = %d\nerrno = %d\n", (int)getuid(), (int)geteuid, errno);
    return 0;
}