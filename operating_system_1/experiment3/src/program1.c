#include <unistd.h>
#include <stdio.h>

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
        printf("It is parent process, pid is %d.\n", getpid());
        printf("The child process is finished.\n");
    }
    else{
        printf("It is child process, pid is %d.\n", getpid());
        sleep(1);
    }
    return 0;
}
