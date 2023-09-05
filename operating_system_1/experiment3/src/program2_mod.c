#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
    int i, j, status;
    printf("current pid: %d, parent pid: %d\n", getpid(), getppid());
    for(i = 0; i < 3; i++)
    {
        status = fork();
        if (status > 0) // make sure one parent process only forks one child process
        {
            printf("fork(): %d, pid: %d, ppid: %d\n", i, getpid(), getppid());
            j = wait(0);
            printf("pid %d: child %d finished\n", getpid(), j);
            break;
        }
    }
    return 0;
}
