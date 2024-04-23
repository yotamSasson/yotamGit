
#include <stdlib.h> /* malloc */
#include <errno.h> /*errno*/
#include <stdio.h> /*perror*/
#include <assert.h> /*assert*/

#include "task.h"

struct task
{
	my_uid_t uid;
	time_t exec_time;
	int (*task)(void *);
	time_t interval;
	void *params;
};


task_t *TaskCreate(time_t exec_time, time_t interval, int (*user_task)(void *params), void *params)
{
	task_t *task = malloc(sizeof(task_t));
	
	assert(NULL != user_task);
	
	if (NULL == task)
    {
        return NULL;
    }
    
    task->exec_time = exec_time;
    task->interval = interval;
    task->task = user_task;
    task->params = params;
    task->uid = UIDCreate();
    
    if (UIDIsSame(task->uid, UIDGetBad()))
    {
    	free(task);
    	return NULL;
    }
    
    return task;
}

void TaskDestroy(task_t *task)
{
	free(task);
	task = NULL;
}

time_t TaskGetExecTime(task_t *task)
{
	assert(NULL != task);
	
	return task->exec_time;
}

time_t TaskGetInterval(task_t *task)
{
	assert(NULL != task);
	
	return task->interval;
}

void *TaskGetParams(task_t *task)
{
	assert(NULL != task);
	
	return task->params;
}

my_uid_t TaskGetUID(task_t *task)
{
	assert(NULL != task);
	
	return task->uid;
}

int TaskRun(task_t *task)
{
	assert(NULL != task);

    return task->task(task->params);
}

void TaskSetExecTime(task_t *task, time_t new_exec_time)
{
	assert(NULL != task);
	
	task->exec_time = new_exec_time;
}


