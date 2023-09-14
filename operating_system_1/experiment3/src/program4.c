#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int global_int = 4;

int main()
{
    int variable = 5;
    printf("before fork\n");
    pid_t pid = fork();
    if (pid < 0)
    {
        printf("fork failed\n");
        exit(0);
    }
    else if (pid == 0)
    {
        global_int++;
        variable--;
        printf(" child %d changed the variable and global_int\n", getpid());
    }
    else
    {
        printf("parent %d did not change the variable and global_int\n", getpid());
    }
    printf("   pid=%d, global_int=%d, variable=%d\n", getpid(), variable, global_int);
    exit(0);
    // return 0;
}

