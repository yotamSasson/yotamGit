
#include <stdlib.h> /* malloc */
#include <stdio.h> /*perror*/
#include <errno.h> /*errno*/
#include <assert.h> /*assert*/
#include <stdatomic.h> /*atomic_int*/

#include "sched.h"
#include "task.h"
#include "pq.h"

struct scheduler
{
	pq_t *heap_pq;
	atomic_int stop;
};

/************************ Functions ************************/

static int priority_func(const void *lhs, const void *rhs)
{
	task_t *task1 = NULL;
	task_t *task2 = NULL;
	
	assert(NULL != lhs);
	assert(NULL != rhs);
	
	task1 = (task_t *)lhs;
	task2 = (task_t *)rhs;
	
	return (int)difftime(TaskGetExecTime(task2), TaskGetExecTime(task1));
}

static int IsMatch(const void *lhs, const void *rhs)
{
	task_t *task1 = NULL;
	
	assert(NULL != lhs);
	assert(NULL != rhs);
	
	task1 = (task_t *)lhs;

	return UIDIsSame(TaskGetUID(task1), *(my_uid_t *)rhs);
}

sch_t *SchCreate(void)
{
	sch_t *sched = malloc(sizeof(sch_t));
	
	if (NULL == sched)
    {
        return NULL;
    }
    
    sched->heap_pq = PQCreate(priority_func);
    
    if (NULL == sched->heap_pq)
	{
		free(sched);
		sched = NULL;
	}
	sched->stop = 0;
	return sched;
}

void SchDestroy(sch_t *scheduler)
{
	assert(NULL != scheduler);
	
	SchClear(scheduler);
	PQDestroy(scheduler->heap_pq);
	free(scheduler);
}

size_t SchSize(const sch_t *scheduler)
{
	assert(NULL != scheduler);
	
	return PQSize(scheduler->heap_pq);
}

int SchIsEmpty(const sch_t *scheduler)
{
	assert(NULL != scheduler);
	
	return PQIsEmpty(scheduler->heap_pq);
}

void SchClear(sch_t *scheduler)
{
	assert(NULL != scheduler);
	
	while (!SchIsEmpty(scheduler))
	{
		TaskDestroy((task_t *)PQPeek(scheduler->heap_pq));
		PQDequeue(scheduler->heap_pq);
	}
}

my_uid_t SchAddTask(sch_t *scheduler ,int (*op_func)(void *), void *params, time_t exec_time , time_t interval)
{
	task_t *task = NULL;
	
	assert(NULL != scheduler);
	assert(NULL != op_func);
	
	task = TaskCreate(exec_time, interval, op_func, params);
	
	PQEnqueue(scheduler->heap_pq, (void *)task);
	
	return TaskGetUID(task);
}

void SchRemoveTask(sch_t *scheduler ,my_uid_t task_uid)
{
	assert(!UIDIsSame(task_uid, UIDGetBad()));
	assert(NULL != scheduler);
	
	TaskDestroy((task_t *)PQErase(scheduler->heap_pq, IsMatch, &task_uid));
}

int SchRun(sch_t *scheduler)
{
	int status = 0;
	task_t *task = NULL;
	time_t time_to_exec = 0;
	time_t current_time = 0;
	scheduler->stop = 0;
	
	assert(NULL != scheduler);
	
	while (!SchIsEmpty(scheduler) && 0 == scheduler->stop && 0 == status)
	{
		current_time = time(NULL);
		task = (task_t *)PQPeek(scheduler->heap_pq);
		time_to_exec = (TaskGetExecTime(task) - current_time);
		
		if (time_to_exec < 0)
		{
			time_to_exec = 0;
		}
		
		sleep(time_to_exec);
		status = TaskRun(task);
		PQDequeue(scheduler->heap_pq);
		
		if (0 != TaskGetInterval(task))
		{
			TaskSetExecTime(task, time_to_exec + current_time + TaskGetInterval(task));
			PQEnqueue(scheduler->heap_pq, (void *)task);
		}
		else
		{
			TaskDestroy(task);
		}	
	}
	
	return status;
}

void SchStop(sch_t *scheduler)
{
	assert(NULL != scheduler);
	scheduler->stop = 1;
}


