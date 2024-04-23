
#include <stdio.h> /*printf*/
#include "task.h"

static void DrawSuccess(void);
static void DrawFailure(void);
static int PrintNumTask(void *params);
static void TestTaskCreate(void);
static void TestTaskRun(void);
static void TestTaskGetExecTime(void);
static void TestTaskGetInterval(void);
static void TestTaskGetParams(void);
static void TestTaskGetUID(void);

int main()
{
    
    TestTaskCreate();
    TestTaskRun();
    TestTaskGetExecTime();
    TestTaskGetInterval();
    TestTaskGetParams();
    TestTaskGetUID();
    
    return 0;
}
static int PrintNumTask(void *params)
{
	int status = 0;
	
	printf("The number is: %d\n", *(int *)params);
	return status;
}

static void TestTaskCreate(void)
{
	time_t exec_time = time(NULL);
	time_t interval = 0;
	int data1 = 4;
	task_t *task = TaskCreate(exec_time, interval, PrintNumTask, &data1);
	
	printf("TaskCreate :\n");
    if (NULL != task)
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    TaskDestroy(task);
}

static void TestTaskRun(void)
{
	time_t exec_time = time(NULL);
	time_t interval = 0;
	int data1 = 4;
	task_t *task = TaskCreate(exec_time, interval, PrintNumTask, &data1);
	
	printf("TaskRun :\n");
    if (0 == TaskRun(task))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    TaskDestroy(task);
}

static void TestTaskGetExecTime(void)
{
	time_t exec_time = time(NULL);
	time_t interval = 0;
	int data1 = 4;
	task_t *task = TaskCreate(exec_time, interval, PrintNumTask, &data1);
	
	printf("TaskGetExecTime :\n");
    if (exec_time == TaskGetExecTime(task))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    TaskDestroy(task);
}

static void TestTaskGetInterval(void)
{
	time_t exec_time = time(NULL);
	time_t interval = 0;
	int data1 = 4;
	task_t *task = TaskCreate(exec_time, interval, PrintNumTask, &data1);
	
	printf("TaskGetInterval :\n");
    if (interval == TaskGetInterval(task))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    TaskDestroy(task);
}

static void TestTaskGetParams(void)
{
	time_t exec_time = time(NULL);
	time_t interval = 0;
	int data1 = 4;
	task_t *task = TaskCreate(exec_time, interval, PrintNumTask, &data1);
	
	printf("TaskGetParams :\n");
    if (data1 == *(int*)TaskGetParams(task))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    TaskDestroy(task);
}

static void TestTaskGetUID(void)
{
	time_t exec_time = time(NULL);
	time_t interval = 0;
	int data1 = 4;
	task_t *task = TaskCreate(exec_time, interval, PrintNumTask, &data1);
	
	printf("TaskGetUID :\n");
    if (UIDIsSame(task->uid, TaskGetUID(task)))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    TaskDestroy(task);
}

static void DrawSuccess(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;42mSUCCESS\033[0m\n\n");
}

static void DrawFailure(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;41mFailed, You should be ashamed of yourself!\033[0m\n\n");
}

