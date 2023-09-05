#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
    int i, j;
    printf("current pid: %d, parent pid: %d\n", getpid(), getppid());
    for(i = 0; i < 3; i++)
    {
        if (fork() == 0)
        {
            printf("fork(): %d, pid: %d, ppid: %d\n", i, getpid(), getppid());
        }
        else
        {
            j = wait(0);
            printf("pid %d: child %d finished\n", getpid(), j);
        }
    }
    return 0;
}
