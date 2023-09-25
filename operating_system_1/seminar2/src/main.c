#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h> // semaphore
#include <sys/shm.h> // shared memory
#include <unistd.h>


#define SHM_SIZE (1024 * 1024)
#define SHM_MODE 0600
#define SEM_MODE 0600

#if defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)
#else

#define n 4
#define DELAY (rand() % 5 + 1)

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};
#endif

int semid = -1, shmId = -1;

struct readcount
{
    int read;
    int l;
} *rdc;

// reader process
void reader(int i)
{
    sleep(DELAY);
    printf("This is process %d,and there are %d are reading\n", i, rdc->read);
}

// writer process
void writer()
{
    sleep(DELAY);
    printf("This is the writing process\n");
}

void wait(int semid, int i)
{
    struct sembuf sb;
    sb.sem_num = i;
    sb.sem_op = -1;
    sb.sem_flg = SEM_UNDO;
    if (semop(semid, &sb, 1) < 0)
    {
        perror("Wait Failed");
        exit(1);
    }
}
void signal(int semid, int i)
{
    struct sembuf sb;
    sb.sem_num = i;
    sb.sem_op = 1;
    sb.sem_flg = SEM_UNDO;
    if (semop(semid, &sb, 1) < 0)
    {
        perror("Signal Failed");
        exit(1);
    }
}

void init() // initialization
{
    // share readcount
    if ((shmId = shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE)) < 0)
    {
        perror("Create Chared Memory Failed");
        exit(1);
    }
    rdc = (struct readcount *)shmat(shmId, 0, 0);
    rdc->read = 0;
    semid = semget(IPC_PRIVATE, 3, IPC_CREAT | 0666);
    if (semid < 0)
    {
        perror("Create Semaphore Failed");
        exit(1);
    }
    union semun sem;
    sem.val = 1;
    // exclusive read
    if (semctl(semid, 0, SETVAL, sem) < 0)
    {
        perror("Semctl Failed");
        exit(1);
    }
    sem.val = 0;
    // readcount count
    if (semctl(semid, 1, SETVAL, sem) < 0)
    {
        perror("Semctl Failed");
        exit(1);
    }
    sem.val = 1;
    // source
    if (semctl(semid, 2, SETVAL, sem) < 0)
    {
        perror("Semctl Failed");
        exit(1);
    }
}

int main()
{
    init();
    int i = -1, child = -1;
    for (i = 0; i < n; i++)
    {
        if ((child = fork()) < 0)
        {
            perror("Fork Failed");
            exit(1);
        }
        else if (child == 0)
        {
            printf("This is the kid %d , pid = %d , ppid = %d\n", i, getpid(),
                   getppid());
            while (1)
            {
                wait(semid, 0);
                if (rdc->read == 0)
                    wait(semid, 2);
                rdc->read = rdc->read + 1;
                signal(semid, 0);
                reader(i);
                wait(semid, 0);
                rdc->read--;
                printf("%d process have read\n", i);
                if (rdc->read == 0)
                    signal(semid, 2);
                signal(semid, 0);
                sleep(2);
            }
            break;
        }
    }
    if (child > 0) // parent process
    {
        while (1)
        {
            wait(semid, 2);
            writer();
            signal(semid, 2);
        }
    }
    return 0;
}
