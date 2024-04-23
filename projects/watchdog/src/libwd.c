
#include <stdio.h> /*print*/
#include <stdlib.h> /*setenv*/
#include <signal.h> /*signals*/
#include <unistd.h> /* getpid fork */
#include <pthread.h> /*pthread*/
#include <semaphore.h> /*sem_t*/
#include <sys/types.h> /*pid_t*/
#include <fcntl.h> /*sem flag*/
#include <sys/wait.h> /*wait*/
#include <string.h> /*strcmp*/
#include <stdatomic.h> /*atomic_int*/

#include "sched.h"
#include "wd.h"

#define SEM_MODE (0666)
#define BUF_SIZE (20)
#define WD_OUT_IMAGE ("./wd.out")
#define SEM_NAME ("semy")


/************************ Signal Routine ************************/
void SIGUSR2Routine(int sig, siginfo_t *info, void *context);
void SIGUSR1Routine(int sig, siginfo_t *info, void *context);
/************************ Thread Routine ************************/
void *ThreadRoutine(void* arg);
/************************ Task Function ************************/
static status_t SendSignalTask(void *param);
static status_t CheckCounterTask(void *param);
/************************ Static Function ************************/
static status_t ReviveClient(void);
static status_t ReviveWD(void);
static status_t InitSced(void);
static status_t InitSigaction(void);
static void CleanUP(void);
/************************ Global Static Variable ************************/
static pthread_mutex_t counter_mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t pid_mtx = PTHREAD_MUTEX_INITIALIZER;
static char **static_argv = NULL;
static sig_atomic_t static_pid = 0;
static sig_atomic_t counter = 0;
static atomic_int stop_flag = 0;
char *sem_name = SEM_NAME;
sem_t *sem = NULL;
sch_t *sched = NULL;
pthread_t task_thread = 0;
struct sigaction sa2 = {0};
struct sigaction sa = {0};

/************************ Function ************************/
status_t StartWD(size_t threshold, int argc, char *argv[])
{
    char threshold_buf[BUF_SIZE] = {0};
    static_argv = argv;

    if (FAILURE == InitSigaction())
    {
        return FAILURE;
    }

    sem = sem_open(sem_name, O_CREAT, SEM_MODE, 0);
    if (SEM_FAILED == sem)
    {
        perror("Error opening sem \n");
        return FAILURE;
    }

    if (0 != strcmp(argv[0], WD_OUT_IMAGE))
    {
        sprintf(threshold_buf, "%lu", threshold);
        setenv("THRESHOLD", threshold_buf, 1);
        setenv("CLIENT_IMAGE", argv[0], 1);

        if (SUCCESS != pthread_create(&task_thread, NULL, ThreadRoutine, NULL))
        {
            perror("Error pthread_create in libwd\n");
            CleanUP();
            return FAILURE;
        } 
    }
    else
    {
        static_pid = getppid();

        if (FAILURE == InitSced())
        {
            CleanUP();
            return FAILURE;
        }
        
        sem_post(sem);
        kill(static_pid, SIGCONT);

        if (FAILURE == SchRun(sched))
        {
           if (FAILURE == ReviveClient())
           {
                CleanUP();
                SchDestroy(sched);
                return FAILURE;
           }
        }
        SchDestroy(sched);
    }
    return SUCCESS;
}

void StopWD(void)
{
    CleanUP();
    kill(static_pid, SIGUSR2);
    wait(NULL);
    pthread_join(task_thread, NULL);
    return;
}

/************************ Signal Routine ************************/
void SIGUSR1Routine(int sig, siginfo_t *info, void *context)
{
    (void)context;
    (void)info;
    
    pthread_mutex_lock(&counter_mtx);
    counter = 0;
    pthread_mutex_unlock(&counter_mtx);
}

void SIGUSR2Routine(int sig, siginfo_t *info, void *context)
{
    (void)context;
    (void)info;

    CleanUP();
}

/************************ Thread Routine ************************/
void *ThreadRoutine(void* arg)
{
    (void)arg;
    if (FAILURE == InitSced())
    {
        CleanUP();
        return NULL;
    }

    if (FAILURE == ReviveWD())
    {
        CleanUP();
        SchDestroy(sched);
        return NULL;
    }

    sem_wait(sem);

    SchRun(sched);

    SchDestroy(sched);

    pthread_exit(NULL);
}

/************************ Task Function ************************/
static status_t SendSignalTask(void *param)
{
    (void)param;

    if (0 == stop_flag)
    {
        pthread_mutex_lock(&pid_mtx);
        kill(static_pid, SIGUSR1);
        pthread_mutex_unlock(&pid_mtx);

        pthread_mutex_lock(&counter_mtx);
        ++counter;
        pthread_mutex_unlock(&counter_mtx);
        return SUCCESS;
    }
    else
    {
        return EXIT_STOP;
    }
}

static status_t CheckCounterTask(void *param)
{
    size_t threshold = (size_t )param;

    pthread_mutex_lock(&counter_mtx);
    if ((sig_atomic_t)threshold < counter)
	{
        if (0 != strcmp(static_argv[0], WD_OUT_IMAGE))
		{
            waitpid(static_pid, NULL, WNOHANG);
            if (FAILURE == ReviveWD())
            {
                return FAILURE;
            }
		    counter = 0;
		}
		else
		{
            pthread_mutex_unlock(&counter_mtx);
		    return FAILURE;
		}
	}
    pthread_mutex_unlock(&counter_mtx);
	return SUCCESS;
}

/************************ Static Function ************************/
static status_t InitSigaction(void)
{
    sa.sa_sigaction = SIGUSR1Routine;
    sa2.sa_sigaction = SIGUSR2Routine;

    if (-1 == sigaction(SIGUSR1, &sa, NULL))
    {
        perror("Error sigaction in StartWD\n");
        return FAILURE;
    }

    if (-1 == sigaction(SIGUSR2, &sa2, NULL))
    {
        perror("Error sigaction2 in StartWD\n");
        return FAILURE;
    }

    return SUCCESS;
}

static status_t ReviveClient(void)
{
    kill(static_pid, SIGTERM);
    waitpid(static_pid, NULL, WNOHANG);
    SchDestroy(sched);
    static_argv[0] = getenv("CLIENT_IMAGE");
    execvp(static_argv[0], static_argv);
    return FAILURE;
}

static status_t ReviveWD(void)
{
    pthread_mutex_lock(&pid_mtx);
    static_pid = fork();

    if (-1 == static_pid)
    {
        pthread_mutex_unlock(&pid_mtx);
        perror("Error fork in libwd\n");
        return FAILURE;
    }
    else if (0 == static_pid)
    {
        kill(getppid(),SIGSTOP);
        execvp(WD_OUT_IMAGE, static_argv);
        perror("execvp()");
        return FAILURE;
    }
    
    pthread_mutex_unlock(&pid_mtx);
    return SUCCESS;
}

static status_t InitSced(void)
{
    size_t threshold = atoi(getenv("THRESHOLD"));
    sched = SchCreate();

    if (NULL == sched)
    {
        perror("Error SchCreate in libwd\n");
        return FAILURE;
    }

    SchAddTask(sched , SendSignalTask, NULL, (time(NULL) + (time_t) 1), 2);
    SchAddTask(sched , CheckCounterTask, (void *)threshold, (time(NULL) + (time_t) 2), 4);

    return SUCCESS;
}

static void CleanUP(void)
{
    ++stop_flag;
    unsetenv("CLIENT_IMAGE");
    unsetenv("THRESHOLD");
    sem_close(sem);
    sem_unlink(sem_name);
}