#ifndef MY_PROJECT_TASK_H__
#define MY_PROJECT_TASK_H__

#include <time.h> /*time_t*/
#include "uid.h"

/*
* @description
* 	The Task API is a C library designed to create
* 	and manage tasks to be executed at a specific
* 	time. The library includes the task_t typedef 
* 	and a set of functions to manipulate it.
*
*/

typedef struct task task_t;

/*
* @description
* 	This function creates a new task with the specified 
* 	exec_time, interval, user_task function pointer and 
* 	params pointer. 
* 
* @params
* 	exec_time - the time at which the task should be 
* 	executed, in seconds.
* 	interval - the time interval between each execution, in case inteval set to 0 it will not execute again.
* 	of the task, in seconds.
* 	user_task - a function pointer to the task to be 
* 	executed. This function must accept a single void* 
* 	argument and return an int.
* 	params - a pointer to the parameters to be passed to 
* 	the user_task function.
*
* @return
* 	A pointer to the newly created task_t struct, or NULL 
* 	if an error occurred.
*
* @warnings
* 	This function assumes that user_task is a valid function 
* 	pointer and that params points to a valid memory location
*
* @complexity
*	 O(n)
*
*/
task_t *TaskCreate(time_t exec_time, time_t interval, int (*user_task)(void *params), void *params);

/*
* @description
* 	This function frees the memory allocated for the 
* 	specified task.
* 
* @params
* 	task - a pointer to the task to be destroyed.
*	if pointer is invalid behavior is undefined.
*
* @warnings
* 	This function assumes that task points to a valid 
* 	task_t struct.
*
* @complexity
*	 O(1)
*
*/
void TaskDestroy(task_t *task);

/*
* @description
* 	This function returns the status of the function
* 	execution
* 
* @params
* 	task - a pointer to the task to be executed.
*	if pointer is invalid behavior is undefined.
*
* @return
*	The function return integer:
* 	0 - if the task was successfully executed.
*	1 - imitating a stop function
*	any other value represent error in function execution
*
* @warnings
* 	This function assumes that task points to a valid 
* 	task_t struct.
*
* @complexity
*	 O(1)
*
*/
int TaskRun(task_t *task);

/*
* @description
* 	This function returns the execution time of the 
* specified task.
* 
* @params
* 	task - a pointer to the task to be executed.
*	if pointer is invalid behavior is undefined.
*
* @return
*	The execution time of the task, in seconds.
*
* @warnings
* 	This function assumes that task points to a valid 
* 	task_t struct.
*
* @complexity
*	 O(1)
*
*/
time_t TaskGetExecTime(task_t *task);

/*
* TaskGetIntervals Description:
*    Returns the time interval between each execution 
* 	of the task, in seconds.
*
* @params:
*   reference to a task.
*	if pointer is invalid behavior is undefined.
*
* @returns:
*    time_t interval.
*	if pointer is invalid behavior is undefined.
*
* @Complexity
*    O(1)
*/
time_t TaskGetInterval(task_t *task);

/*
* TaskGetParams Description:
*    Returns the task params 
*
* @params:
*   reference to a task.
*
* @returns:
*    pointer to the params variable in the task.
*	if pointer is invalid behavior is undefined.
*
* @Complexity
*    O(1)
*/
void *TaskGetParams(task_t *task);

/*
* TaskGetUID Description:
*    Returns the task UID 
*
* @params:
*   reference to a task.
*	if pointer is invalid behavior is undefined.
*
* @returns:
*    my_uid_t UID object.
*
* @Complexity
*    O(1)
*/
my_uid_t TaskGetUID(task_t *task);

/*
* TaskSetExecTime Description:
*    set a new time to execute the task. 
*
* @params:
*   reference to a task and a new time.
*	if pointer is invalid behavior is undefined.
*
* @returns:
*    none.
*
* @Complexity
*    O(1)
*/
void TaskSetExecTime(task_t *task, time_t new_exec_time);
#endif
