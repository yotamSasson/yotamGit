
#include <stdio.h> /*printf*/
#include <stdlib.h> /*system*/
#include "sched.h"

static void DrawSuccess(void);
static void DrawFailure(void);
static int StopTask(void *params);
static int PrintTask(void *params);
static int PrintDragonTask(void *params);
static void TestSchCreate(void);
static void TestSchIsEmpty(void);
static void TestSchSize(void);
static void TestSchAddTask(void);
static void TestSchRemoveTask(void);
static void TestSchRun(void);

int main(void)
{
	TestSchCreate();
	TestSchIsEmpty();
	TestSchSize();
	TestSchAddTask();
	TestSchRemoveTask();
	TestSchRun();
	return 0;
}

static int PrintTask(void *params)
{
	int status = 0;
	
	printf("You are %d\n", *(int *)params);
	return status;
}

static int PrintDragonTask(void *params)
{
	int status = 0;
	(void)params;
	
    system("cowsay -f dragon you are ROCK!");
	return status;
}

static int StopTask(void *params)
{
	sch_t *sch = (sch_t *)params;
    SchStop(sch);
    
    return 0;
}

static void TestSchCreate(void)
{
	sch_t *sched = SchCreate();
	printf("SchCreate :\n");
    if (NULL != sched)
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    SchDestroy(sched);
}

static void TestSchIsEmpty(void)
{
	sch_t *sched = SchCreate();
	printf("SchIsEmpty :\n");
    if (SchIsEmpty(sched))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    SchDestroy(sched);
}

static void TestSchSize(void)
{
	sch_t *sched = SchCreate();
	printf("SchSize :\n");
    if (0 == SchSize(sched))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    SchDestroy(sched);
}

static void TestSchAddTask(void)
{
	sch_t *sched = SchCreate();
	my_uid_t uid = {0};
	my_uid_t uid2 = UIDGetBad();
	time_t exec_time = time(NULL);
	time_t interval = 0;
	int data1 = 100;
	
	uid = SchAddTask(sched , PrintTask, &data1, exec_time, interval);
	printf("SchAddTask :\n");
    if (!SchIsEmpty(sched) && !UIDIsSame(uid, uid2) && 1 == SchSize(sched))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    SchDestroy(sched);
}

static void TestSchRemoveTask(void)
{
	sch_t *sched = SchCreate();
	my_uid_t uid1 = {0};
    my_uid_t uid2 = {0};
	time_t exec_time = time(NULL);
	time_t interval = 0;
	int data1 = 100;
	
	uid1= SchAddTask(sched , PrintTask, &data1, exec_time, interval);
	uid2 = SchAddTask(sched , PrintTask, &data1, exec_time, interval);
	SchRemoveTask(sched, uid1);

	printf("SchRemoveTask :\n");
    if (!SchIsEmpty(sched) && 1 == SchSize(sched))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    SchRemoveTask(sched, uid2);
     if (SchIsEmpty(sched) && 0 == SchSize(sched))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }

    SchDestroy(sched);
}

static void TestSchRun(void)
{
	sch_t *sched = SchCreate();
	time_t exec_time = time(NULL);
	time_t exec_time2 = (time(NULL) + 11);
	time_t time_to_stop = (time(NULL) + 19);
	time_t interval = 5;
	time_t interval2 = 3;
	int data1 = 100;
	int data2 = 0;
	
	SchAddTask(sched, PrintTask, &data1, exec_time, interval);
	SchAddTask(sched, PrintDragonTask, &data2, exec_time2, interval2);
	SchAddTask(sched, StopTask, sched, time_to_stop, 0);
	
	printf("SchRun :\n");
    if (0 == SchRun(sched))
    {
        DrawSuccess();
    }
    else
    {
        DrawFailure();
    }
    
    SchDestroy(sched);
}

static void DrawSuccess(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;42mSUCCESS\033[0m\n\n");
}

static void DrawFailure(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;41mFailed, You should be ashamed of yourself!\033[0m\n\n");
}
