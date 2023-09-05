#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();
    if (pid < 0)
    {
        printf("Error in fork!\n");
        return -1;
    }
    else if (pid == 0)
    {
        printf("It is child process, pid is %d.\n", getpid());
        sleep(3);
        exit(0);
    }
    else
    {
        printf("It is parent process, pid is %d, child pid is %d.\n", getpid(), pid);
        int i;
        pid_t exited = wait(&i);
        printf("The child process %d is finished, returns %d.\n", exited, i);
    }
    return 0;
}
