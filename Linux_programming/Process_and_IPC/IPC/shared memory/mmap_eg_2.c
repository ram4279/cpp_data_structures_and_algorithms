#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>

struct student
{
    int roll_no;
    int marks;
    char name[30];
};

typedef struct student student_t;

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("%s <file with some content>\n", argv[0]);
        return 0;
    }

    const char *file_path = argv[1];

    int fd = open(file_path, O_RDWR);

    if (fd < 0) {
        printf("open failed!!!\n");
        return -1;
    }
    
    struct stat stat_buf;
    int err = fstat(fd, &stat_buf);
    if (err < 0) {
        printf("Cannot open file fd\n");
        return -1;
    }

    char *ptr = mmap(NULL,
                     stat_buf.st_size,
                     PROT_READ|PROT_WRITE,
                     MAP_SHARED,
                     fd, /* Identifier of external data source in this case file*/
                     0 /* Offset from where mapping has to begin*/);

    if (ptr == MAP_FAILED) {
        perror("Map failed\n");
        return -1;
    }

    student_t student_1 = {
        .marks = 90,
        .roll_no = 1,
        .name = "sairam"
    };

    memcpy(ptr, &student_1, sizeof(student_1));
    msync(ptr, sizeof(student_1), MS_SYNC);

    munmap(ptr, stat_buf.st_size); /* Destroy mapping once done */
    printf("Name = %s\n", student_1.name);
    return 0;
}
