#include <stdio.h> /*print*/
#include <pthread.h> /*pthread_create*/
#include <stdatomic.h> /*atomic_int*/
#include <semaphore.h> /*sem_t*/
#include <fcntl.h> /*sem flag*/

#include "fsq.h"
#include "fsq.c"

#define THREAD_SIZE (10)
#define QUEUE_SIZE (10)
#define SEM_MODE (0666)

void *ProducerRoutine(void *arg);
void *ConsumerRoutine(void *arg);

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
fsq_t *fsq = NULL;
sem_t *sem1 = NULL;
sem_t *sem2 = NULL;

int main (void)
{
    char *sem_name1 = "semy1";
    char *sem_name2 = "semy2";
    pthread_t producers[THREAD_SIZE] = {0};
    pthread_t consumers[THREAD_SIZE] = {0};
    int producer_ids[THREAD_SIZE] = {0};
    size_t i = 0;
    sem1 = sem_open(sem_name1, O_CREAT, SEM_MODE, 0);
    sem2 = sem_open(sem_name2, O_CREAT, SEM_MODE, 0);
    fsq = FSQCreate(QUEUE_SIZE, sem2);

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

    sem_close(sem1);
    sem_unlink(sem_name1);
    sem_close(sem2);
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
        pthread_mutex_lock(&mtx);
        FSQEnqueue(fsq, id);
        pthread_mutex_unlock(&mtx);
        sem_post(sem1);
    }
    return NULL;
}

void *ConsumerRoutine(void *arg)
{
    int i = 0;
    (void)arg;
    for (i = 0; i < 1; ++i)
    {
        sem_wait(sem1);
        pthread_mutex_lock(&mtx);
        printf("the consumer read: %d\n",FSQPeek(fsq));
        FSQDequeue(fsq);
        pthread_mutex_unlock(&mtx);
        
    }
    return NULL;
}