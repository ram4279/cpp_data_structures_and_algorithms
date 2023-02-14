#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int fp = open("fcntl_3.c", O_RDWR);
    int access_modes, flags;
    flags = fcntl(fp, F_GETFL);
    access_modes = flags & O_ACCMODE;
    if (access_modes == O_WRONLY || access_modes == O_RDWR) {
        printf("file is writable\n");
    }
    close(fp);
    return 0;
}
