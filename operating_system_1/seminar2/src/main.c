#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <semaphore.h> // POSIX semaphore
#include <signal.h>
#include <unistd.h>

#define READER_COUNT 4
#define DELAY (rand() % 5 + 1) // random delay

int *read_count = NULL;
sem_t *wmutex;
sem_t *rmutex;
pid_t child_pid[READER_COUNT];
int parent_process = 0;

// reader process
void reader(int i)
{
    printf("\e[33mreader\e[0m process %d, readers: %d\n", i, *read_count);
    sleep(DELAY);
}

// writer process
void writer()
{
    printf("\e[94mwriter\e[0m process  , readers: %d\n", *read_count);
    sleep(DELAY);
}

// initialization
void init()
{
    // allocate shared memory
    if ((read_count = mmap(NULL, sizeof(int), 
        PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0)) < 0)
    {
        perror("mmap for read_count failed\n");
        exit(1);   
    }
    if ((rmutex = mmap(NULL, sizeof(sem_t), 
        PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0)) < 0)
    {
        perror("mmap for rmutex failed\n");
        exit(1);
    }
    if ((wmutex = mmap(NULL, sizeof(sem_t), 
        PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0)) < 0)
    {
        perror("mmap for wmutex failed\n");
        exit(1);
    }

    // initialization
    *read_count = 0;
    if (sem_init(wmutex, 1, 1) != 0)
    {
        perror("sem_init wmutex failed\n");
        exit(1);
    }
    if (sem_init(rmutex, 1, 1) != 0)
    {
        perror("sem_init rmutex failed\n");
        exit(1);
    }
}

void sigint_handler() // SIGINT handler
{
    if (parent_process)
    {
        // kill child process
        int i;
        for (i = 0; i < READER_COUNT; i++)
        {
            kill(child_pid[i], SIGKILL);
            printf("\e[31mkilled\e[0m %d\n", child_pid[i] - getpid() - 1);
        }

        // close semaphores
        sem_close(wmutex);
        sem_close(rmutex);

        // destroy semaphore
        if (rmutex)
        {
            sem_destroy(rmutex);
            if (munmap(rmutex, sizeof(sem_t)) == 0)
            {
                printf("\e[32mreleased\e[0m rmutex\n");
            }
        }
        if (wmutex)
        {
            sem_destroy(wmutex);
            if (munmap(wmutex, sizeof(sem_t)) == 0)
            {
                printf("\e[32mreleased\e[0m wmutex\n");
            }
        }

        // release read_count
        if (read_count)
        {
            if (munmap(read_count, sizeof(int)) == 0)
            {
                printf("\e[32mreleased\e[0m read_count\n");
            }
        }
        exit(0);
    }
    else
    {
        kill(getpid(), SIGKILL); // suicide
    }
}

int main()
{
    init();
    signal(SIGINT, sigint_handler);
    int i = -1;
    pid_t child = -1;
    for (i = 0; i < READER_COUNT; i++)
    {
        if ((child = fork()) < 0)
        {
            perror("Fork failed");
            exit(1);
        }
        else if (child == 0) // child process as writer
        {
            while (1)
            {
                sem_wait(rmutex); // semaphore as mutex lock
                if (*read_count == 0) // notify writer
                {
                    sem_wait(wmutex);
                }
                (*read_count)++; // increase reader count
                sem_post(rmutex); // comment this to perform exculsively read

                reader(i); // reader processing

                sem_wait(rmutex);
                (*read_count)--; // decrease reader count
                if (*read_count == 0) // notify writer
                {
                    sem_post(wmutex);
                }
                sem_post(rmutex); // reader complete
                printf("\e[33mreader\e[0m process %d, \e[32mcomplete\e[0m\n", i);
                sleep(2);
            }
        }
        else
        {
            child_pid[i] = child;
        }
    }
    if (child > 0) // parent process as writer
    {
        parent_process = 1;
        while (1)
        {
            sem_wait(wmutex); // wait for write
            writer();
            sem_post(wmutex); // write complete
            sleep(2);
        }
    }
    return 0;
}
