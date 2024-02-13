#include <pthread.h> /*pthread_create*/
#include <stdio.h> /*print*/
#include <unistd.h>
#include <stdatomic.h> /*atomic_int*/

#define THREAD_SIZE (2)
#define BUFFER_SIZE (8)

void *ProducerRoutine(void *arg);
void *ConsumerRoutine(void *arg);

atomic_int lock = 0;
int buffer = 0;

int main (void)
{
    pthread_t threads[THREAD_SIZE] = {0};
    pthread_create(&threads[0], NULL, ProducerRoutine, NULL);
    pthread_create(&threads[1], NULL, ConsumerRoutine, NULL);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    return 0;
}

void *ProducerRoutine(void *arg)
{
    int write = 0;
    (void)arg;

    while (1)
    {
        while (1 == lock) {}
        buffer = write;
        printf("Producer write to buffer: %d\n", write);
        ++write;
        lock = 1;
    }
}

void *ConsumerRoutine(void *arg)
{
    int read = 0;
    (void)arg;

    while (1)
    {
        while (0 == lock) {}
        read = buffer;
        lock = 0;
        printf("consumer read from buffer: %d\n", read);
    }
}
