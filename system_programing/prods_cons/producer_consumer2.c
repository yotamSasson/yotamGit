#include <stdio.h> /*print*/
#include <pthread.h> /*pthread_create*/
#include <stdatomic.h> /*atomic_int*/
#include <semaphore.h> /*sem_t*/
#include <fcntl.h> /*sem flag*/
#include <unistd.h>

#define PRODUCER_NUM (1)
#define CONSUMER_NUM (20)
#define SEM_MODE (0666)

void *ProducerRoutine(void *arg);
void *ConsumerRoutine(void *arg);

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
sem_t *sem = NULL;

int message = 0;
int num_consumers_read = 0;

int main (void)
{
    char *sem_name1 = "semy";
    pthread_t producers = 0;
    pthread_t consumers[CONSUMER_NUM] = {0};
    size_t i = 0;
    sem = sem_open(sem_name1, O_CREAT, SEM_MODE, 0);
    if (SEM_FAILED == sem)
    {
        perror("error open semsem\n");
        return 1;
    }
    
    pthread_create(&producers, NULL, ProducerRoutine, NULL);

    for (i = 0; i < CONSUMER_NUM; ++i)
    {
        pthread_create(&consumers[i], NULL, ConsumerRoutine, NULL);
    }

    pthread_join(producers, NULL);

    for (i = 0; i < CONSUMER_NUM; ++i)
    {
        pthread_join(consumers[i], NULL);
    }

    sem_close(sem);
    sem_unlink(sem_name1);

    return 0;
}

void *ProducerRoutine(void* arg)
{
    (void)arg;
    
    while (1)
    {
        pthread_mutex_lock(&mtx);
        ++message;
        while (CONSUMER_NUM > num_consumers_read)
        {
            sem_post(sem);
            pthread_cond_wait(&cond, &mtx);
        }
        
        printf("last\n\n");
        num_consumers_read = 0;
        pthread_mutex_unlock(&mtx);
    }   
    return NULL;
}

void *ConsumerRoutine(void* arg)
{
    (void) arg;

    while (1)
    {
        sem_wait(sem);
        pthread_mutex_lock(&mtx);
        printf("Consumer: %ld read message: %d\n", pthread_self(), message);
        ++num_consumers_read;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mtx);   
    }

    return NULL;
}
