#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("pid: %d\n", getpid());
    printf("ppid: %d\n", getppid());
    printf("uid: %d\n", getuid());
    printf("euid: %d\n", geteuid());
    printf("gid: %d\n", getgid());
    printf("egid: %d\n", getegid());
    sleep(5);
    printf("execute ls -lh? (y/n): ");
    char choice;
    scanf("%c", &choice);
    printf("\n");
    if (choice == 'y')
    {
        char *args[] = {"ls", "-lh", NULL};
        execvp("ls", args);
    }
    return 0;
}
