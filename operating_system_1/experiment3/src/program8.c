#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <signal.h>

#define PRODUCER_COUNT 3
#define CONSUMER_COUNT 2
#define BUFFER_SIZE 5

sem_t blank, product;
pthread_t tid[PRODUCER_COUNT + CONSUMER_COUNT];
pthread_mutex_t mutex;
int buffer[BUFFER_SIZE];
int *malloced_pointer[PRODUCER_COUNT + CONSUMER_COUNT];

void *produce(void *arg)
{
    int id = *(int *) arg, i = 0;
    while (1)
    {
        sem_wait(&blank); // wait for blank space to produce
        pthread_mutex_lock(&mutex); // lock the buffer
        buffer[i] = rand() % 100 + 1;
        printf("producer %d: produce %d in buffer[%d]\n", id, buffer[i], i);
        i = (i + 1) % BUFFER_SIZE; // simulate circular buffer
        pthread_mutex_unlock(&mutex); // unlock the buffer
        sem_post(&product); // signal that a product is produced (call consumer to consume)
        sleep(sleep(rand() % 3 + 1)); // sleep for 1-3 seconds
    }
    return arg;
}

void *consumer(void *arg)
{
    int id = *(int *) arg, i = 0;
    while (1)
    {
        sem_wait(&product); // wait for product to consume
        pthread_mutex_lock(&mutex); // lock the buffer
        printf("consumer %d: consume %d in buffer[%d]\n", id, buffer[i], i);
        buffer[i] = 0; // consume the product
        i = (i + 1) % BUFFER_SIZE; // simulate circular buffer
        pthread_mutex_unlock(&mutex); // unlock the buffer
        sem_post(&blank); // signal that a product is consumed (call producer to produce)
        sleep(sleep(rand() % 3 + 1)); // sleep for 1-3 seconds
    }
    return arg;
}

// handle SIGINT (Ctrl+C) signal
void sigint_handler()
{
    int i;

    // cancel producer threads
    for (i = 0; i < PRODUCER_COUNT; i++)
    {
        pthread_cancel(tid[i]);
        free(malloced_pointer[i]);
        printf("producer %d cancelled\n", i);
    }

    // cancel consumer threads
    for (i = 0; i < CONSUMER_COUNT; i++)
    {
        pthread_cancel(tid[PRODUCER_COUNT + i]);
        free(malloced_pointer[PRODUCER_COUNT + i]);
        printf("consumer %d cancelled\n", i);
    }

    // destroy mutex and semaphores
    pthread_mutex_destroy(&mutex);
    sem_destroy(&blank);
    sem_destroy(&product);

    printf("program terminated\n");
    exit(0);
}

int main()
{
    int i;
    srand(time(NULL)); // seed random number generator
    pthread_mutex_init(&mutex, NULL); // initialize mutex
    sem_init(&blank, 0, BUFFER_SIZE); // initialize blank space to BUFFER_SIZE
    sem_init(&product, 0, 0); // initialize product to 0

    signal(SIGINT, sigint_handler); // register SIGINT handler (Ctrl+C

    // create producer threads
    for (i = 0; i < PRODUCER_COUNT; i++)
    {
        int *p = malloc(sizeof(int));
        *p = i; // producer id
        malloced_pointer[i] = p; // save malloced pointer for later free
        pthread_create(&tid[i], NULL, produce, p);
    }

    // create consumer threads
    for (i = 0; i < CONSUMER_COUNT; i++)
    {
        int *p = malloc(sizeof(int));
        *p = i; // consumer id
        malloced_pointer[PRODUCER_COUNT + i] = p; // save malloced pointer for later free
        pthread_create(&tid[PRODUCER_COUNT + i], NULL, consumer, p);
    }

    // wait for all threads to exit
    for (i = 0; i < PRODUCER_COUNT + CONSUMER_COUNT; i++)
    {
        int *p = NULL;
        pthread_join(tid[i], (void **) &p);
        free(p);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&blank);
    sem_destroy(&product);
    return 0;
}
