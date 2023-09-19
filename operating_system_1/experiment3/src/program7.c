#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void func()
{
    printf("process %d, signal 18 processing function\n", getpid());
}

int main()
{
    int i, j, k;
    signal(18, func);
    if ((i = fork()) > 0)
    {
        j = kill(i, 18);
        printf("parent %d: signal 18 sent to child %d, return %d\n", getpid(), i, j);
        k = wait(NULL);
        printf("parent %d waited child %d and finished\n", k, getpid());
    }
    else
    {
        sleep(10);
        printf("child %d received a signal from parent\n", getpid());
    }
    return 0;
}
