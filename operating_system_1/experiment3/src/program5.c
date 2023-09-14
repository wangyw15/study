#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int i, r, j, k, l, process1, process2, fd[2];
    char buffer_write[50], buffer_read[50];
    pipe(fd);
    while ((process1 = fork()) == -1); // new process
    if (process1 == 0)
    {
        lockf(fd[1], 1, 0);
        sprintf(buffer_write, "child process p1 is sending\n");
        printf("child process 1: %d\n", getpid());
        write(fd[1], buffer_write, 50);
        lockf(fd[1], 0, 0);
        sleep(5);
        printf("p1 %d is weakup, parent pid is %d\n", getpid(), getppid());
        exit(0);
    }
    else
    {
        while ((process2 = fork()) == -1);
        if (process2 == 0)
        {
            lockf(fd[1], 1, 0);
            sprintf(buffer_write, "child process p2 is sending\n");
            printf("child process 2: %d\n", getpid());
            write(fd[1], buffer_write, 50);
            lockf(fd[1], 0, 0);
            sleep(5);
            printf("p2 %d is weakup, parent pid is %d\n", getpid(), getppid());
            exit(0);
        }
        else
        {
            wait(NULL);
            if ((r = read(fd[0], buffer_read, 50)) == -1)
            {
                printf("read pipe failed\n");
            }
            else
            {
                printf("parent %d: %s\n", getpid(), buffer_read);
            }
            wait(NULL);
            if ((r = read(fd[0], buffer_read, 50)) == -1)
            {
                printf("read pipe failed\n");
            }
            else
            {
                printf("parent %d: %s\n", getpid(), buffer_read);
            }
        }
    }
    return 0;
}
