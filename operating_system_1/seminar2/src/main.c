#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h> // semaphore
#include <sys/shm.h> // shared memory
#include <unistd.h>

#define READER 0
#define WRITER 1
#define SHM_SIZE (1024 * 1024) // shared memory size
#define DELAY (rand() % 3 + 1)

union semun
{
    int val; // value for setval()
    struct semid_ds *buf; // buffer for IPC_STAT and IPC_SET
    unsigned short *array; // array for GETALL and SETALL
};

int semid = -1; // semaphore id
int shmid = -1; // shared memory id

struct readcount
{
    int read; // reader count
    int l;
} *rdc;

// reader process
void reader(int i)
{
    sleep(DELAY);
    printf("This is process %d, and there are %d are reading\n", i, rdc->read);
}

// writer process
void writer()
{
    sleep(DELAY);
    printf("This is the writer process\n");
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
        perror("Wait failed");
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
        perror("Signal failed");
        exit(1);
    }
}

void init() // initialization
{
    // shared memory for readcount
    if ((shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666)) < 0)
    {
        perror("Create shared memory failed");
        exit(1);
    }
    rdc = (struct readcount *)shmat(shmid, NULL, 0); // attach shared memory
    rdc->read = 0; // reset reader count
    semid = semget(IPC_PRIVATE, 3, IPC_CREAT | 0666); // create semaphores
    if (semid < 0)
    {
        perror("Create semaphore failed");
        exit(1);
    }
    union semun sem;
    sem.val = 1;
    // semnum for multiple semaphores
    // exclusive read
    // reader can read at first
    if (semctl(semid, READER, SETVAL, sem) < 0)
    {
        perror("Semctl failed");
        exit(1);
    }
    // source
    // no writer at first
    if (semctl(semid, WRITER, SETVAL, sem) < 0)
    {
        perror("Semctl failed");
        exit(1);
    }
}

int main()
{
    init();
    int i = -1, child = -1;
    for (i = 0; i < 4; i++)
    {
        if ((child = fork()) < 0)
        {
            perror("Fork failed");
            exit(1);
        }
        else if (child == 0)
        {
            printf("Kid %d, pid = %d, ppid = %d\n", i, getpid(), getppid());
            while (1)
            {
                _wait(semid, READER); // wait for reader resource
                if (rdc->read == 0) // notify writer to write
                {
                    _wait(semid, WRITER);
                }
                rdc->read++; // increase reader count
                _signal(semid, READER); // reader complete
                reader(i); // print message
                _wait(semid, READER);
                rdc->read--; // decrease reader count
                printf("Process %d have read\n", i);
                if (rdc->read == 0)
                {
                    _signal(semid, WRITER);
                }
                _signal(semid, READER);
                sleep(2);
            }
            break;
        }
    }
    if (child > 0) // parent process
    {
        while (1)
        {
            _wait(semid, WRITER);
            writer();
            _signal(semid, WRITER);
        }
    }
    return 0;
}
