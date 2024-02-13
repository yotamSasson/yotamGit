#include <stdio.h> /*print*/
#include <pthread.h> /*pthread_create*/
#include <stdatomic.h> /*atomic_int*/
#include <semaphore.h> /*sem_t*/
#include <fcntl.h> /*sem flag*/

#include "fsq2.h"
#include "fsq2.c"

#define THREAD_SIZE (10)
#define QUEUE_SIZE (10)
#define SEM_MODE (0666)

void *ProducerRoutine(void *arg);
void *ConsumerRoutine(void *arg);

static pthread_mutex_t mtx1 = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mtx2 = PTHREAD_MUTEX_INITIALIZER;
fsq_t *fsq = NULL;
sem_t *sem_empty = NULL;
sem_t *sem_full = NULL;


int main (void)
{
    char *sem_name1 = "sem_empty";
    char *sem_name2 = "sem_full";
    pthread_t producers[THREAD_SIZE] = {0};
    pthread_t consumers[THREAD_SIZE] = {0};
    int producer_ids[THREAD_SIZE] = {0};
    size_t i = 0;
    sem_empty = sem_open(sem_name1, O_CREAT, SEM_MODE, QUEUE_SIZE);
    if (SEM_FAILED == sem_empty)
    {
        perror("sem_empty");
        return 1;
    }
    sem_full = sem_open(sem_name2, O_CREAT, SEM_MODE, 0);
    if (SEM_FAILED == sem_full)
    {
        perror("sem_full");
        return 1;
    }

    fsq = FSQCreate(QUEUE_SIZE, &mtx2, &mtx1);

    for (i = 0; i < THREAD_SIZE; ++i)
    {
        producer_ids[i] = i;
        pthread_create(&producers[i], NULL, ProducerRoutine, &producer_ids[i]);
        pthread_create(&consumers[i], NULL, ConsumerRoutine, NULL);
    }

    for (i = 0; i < THREAD_SIZE; ++i)
    {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
    }

    sem_close(sem_empty);
    sem_unlink(sem_name1);
    sem_close(sem_full);
    sem_unlink(sem_name2);
    FSQDestroy(fsq);

    return 0;
}

void *ProducerRoutine(void *arg)
{
    int id = *(int*)arg;
    int i = 0;

    for (i = 0; i < 1; ++i)
    {
        sem_wait(sem_empty);
        FSQEnqueue(fsq, id);
        sem_post(sem_full);
    }
    return NULL;
}

void *ConsumerRoutine(void *arg)
{
    int i = 0;
    
    (void)arg;
    for (i = 0; i < 1; ++i)
    {
        sem_wait(sem_full);
        printf("the consumer read: %d\n",FSQDequeue(fsq));
        sem_post(sem_empty);
    }
    return NULL;
}
