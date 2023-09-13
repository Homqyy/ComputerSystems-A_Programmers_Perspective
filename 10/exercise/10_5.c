#include <csapp.h>

int main(int argc, char **argv)
{
    int fd1, fd2;
    char c;

    fd1 = Open("foobar.txt", O_RDONLY, 0);
    fd2 = Open("foobar.txt", O_RDONLY, 0);

    Read(fd2, &c, 1);
    Dup2(fd2, fd1); // fd1 now points to the same file as fd2
    Read(fd1, &c, 1);

    printf("c = %c\n", c);
    exit(0);
}