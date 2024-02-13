/*******************************
*    Developer : Yotam sasson  *
*    Date      : 11.05.2023    *
*    Reviewer  :            *
*******************************/
#include <stdio.h> /*print*/
#include <pthread.h> /*pthread_create*/
#include <stdatomic.h> /*atomic_int*/
#include <semaphore.h> /*sem_t*/
#include <fcntl.h> /*sem flag*/

#include "/Users/yotamsasson/Documents/Git/yotamGit/ds/include/linked_list.h"
#include "/Users/yotamsasson/Documents/Git/yotamGit/ds/src/linked_list.c"

#define THREAD_SIZE (10)
#define NUM_NODS (5)

void *ProducerRoutine(void *arg);
void *ConsumerRoutine(void *arg);

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static sll_t *linkedList = NULL;
sem_t *sem = NULL;

int main (void)
{
    char *sem_name = "semy";
    pthread_t producers[THREAD_SIZE] = {0};
    pthread_t consumers[THREAD_SIZE] = {0};
    int producer_ids[THREAD_SIZE] = {0};
    size_t i = 0;
    linkedList = SLLCreate();
    sem = sem_open(sem_name, O_CREAT, 0666, 0);

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

    SLLDestroy(linkedList);
    sem_close(sem);
    sem_unlink(sem_name);
    return 0;
}

void *ProducerRoutine(void *arg)
{
    atomic_int i = 0;

    for (i = 0; i < NUM_NODS; ++i)
    {
        pthread_mutex_lock(&mtx);
        SLLInsertBefore(SLLEndIter(linkedList), arg);
        pthread_mutex_unlock(&mtx);
        sem_post(sem);
    }
    return NULL;
}

void *ConsumerRoutine(void *arg)
{
    atomic_int i = 0;
    (void)arg;

    for (i = 0; i < NUM_NODS; ++i)
    {
        sem_wait(sem);
        pthread_mutex_lock(&mtx);
        printf("the consumer read: %d\n", *(int *)SLLGetData(SLLBeginIter(linkedList)));
        SLLRemove(SLLBeginIter(linkedList));
        pthread_mutex_unlock(&mtx);  
    }
    
    return NULL;
}
