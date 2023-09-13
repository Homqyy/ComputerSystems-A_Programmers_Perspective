#include <csapp.h>

#define MESSAGE "hello world\n"

/*
 * 如何用 dup2 复制 标准输出 到 fd5 */
int main(int argc, char **argv)
{
    if (-1 == Dup2(STDOUT_FILENO, 5))
    {
        perror("fail to dup2(STDOUT_FILENO, 5)");
        return -1;
    }

    write(5, MESSAGE, sizeof(MESSAGE));

    return 0;
}