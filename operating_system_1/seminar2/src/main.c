#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h> // semaphore
#include <sys/shm.h> // shared memory
#include <unistd.h>

#define READER_ID 0
#define WRITER_ID 1
#define SEMAPHORE_COUNT 2 // amount of semaphores
#define READER_COUNT 4
#define DELAY (rand() % 5 + 1) // random delay

union semun
{
    int val; // value for setval()
    struct semid_ds *buf; // buffer for IPC_STAT and IPC_SET
    unsigned short *array; // array for GETALL and SETALL (semaphore data)
};

int semid = -1; // semaphore id
int *read_count = NULL;

// reader process
void reader(int i)
{
    printf("\e[36mreader\e[0m process %d, readers: %d\n", i, *read_count);
    sleep(DELAY);
}

// writer process
void writer()
{
    printf("\e[94mwriter\e[0m process  , readers: %d\n", *read_count);
    sleep(DELAY);
}

// P()
void _wait(int semid, int i)
{
    struct sembuf buffer;
    buffer.sem_num = i; // semaphore id
    buffer.sem_op = -1; // wait
    buffer.sem_flg = SEM_UNDO; // let system track the semaphore
    if (semop(semid, &buffer, 1) < 0) // wait for resource
    {
        perror("_wait failed\n");
        exit(1);
    }
}

// V()
void _signal(int semid, int i)
{
    struct sembuf sb;
    sb.sem_num = i; // semaphore id
    sb.sem_op = 1; // signal
    sb.sem_flg = SEM_UNDO; // let system track the semaphore
    if (semop(semid, &sb, 1) < 0) // release resource
    {
        perror("_signal failed\n");
        exit(1);
    }
}

// initialization
void init()
{
    int shmid = -1;
    // init read_count
    if ((shmid = shmget(IPC_PRIVATE, sizeof(int), 0600)) < 0)
    {
        perror("shmget for read_count failed");
        exit(1);   
    }
    read_count = (int*)shmat(shmid, NULL, 0);
    *read_count = 0;

    semid = semget(IPC_PRIVATE, SEMAPHORE_COUNT, IPC_CREAT | 0666);
    if (semid < 0)
    {
        perror("semaphore creation failed\n");
        exit(1);
    }
    
    union semun sem;
    sem.val = READER_COUNT;
    // exclusive read
    // reader can read
    if (semctl(semid, READER_ID, SETVAL, sem) < 0)
    {
        perror("semctl for reader failed");
        exit(1);
    }
    // writer can write
    sem.val = 1;
    if (semctl(semid, WRITER_ID, SETVAL, sem) < 0)
    {
        perror("semctl for writer failed");
        exit(1);
    }
}

int main()
{
    init();
    int i = -1, child = -1;
    for (i = 0; i < READER_COUNT; i++)
    {
        if ((child = fork()) < 0)
        {
            perror("Fork failed");
            exit(1);
        }
        else if (child == 0) // child process as writer
        {
            // printf("child %d, pid = %d, ppid = %d\n", i, getpid(), getppid());
            while (1)
            {
                _wait(semid, READER_ID); // semaphore as mutex lock
                if (*read_count == 0) // first reader
                {
                    _wait(semid, WRITER_ID);
                }
                (*read_count)++; // increase reader count
                //_signal(semid, READER_ID); // reading and release

                reader(i); // print message

                //_wait(semid, READER_ID);
                (*read_count)--; // decrease reader count
                if (*read_count == 0) // first reader
                {
                    _signal(semid, WRITER_ID);
                }
                _signal(semid, READER_ID); // reader complete
                printf("\e[36mreader\e[0m process %d, \e[32mcomplete\e[0m\n", i);
                sleep(2);
            }
        }
    }
    if (child > 0) // parent process
    {
        while (1)
        {
            _wait(semid, WRITER_ID); // wait for write
            writer();
            _signal(semid, WRITER_ID); // write complete
        }
    }
    return 0;
}
