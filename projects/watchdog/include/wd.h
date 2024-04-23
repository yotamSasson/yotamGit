#ifndef MY_PROJECT_WD_H__
#define MY_PROJECT_WD_H__

#include <stddef.h> /* size_t */
#include <pthread.h> /* pthread */

typedef enum status
{
    SUCCESS = 0,
    FAILURE = -1,
    EXIT_STOP = 1
}status_t;

/*
* StartWD Description:
*    starts the watchdog.
*   if process terminates while watchdog is on, watchdog will restart the process.
*
* @Params:
*    threshold - number of miss signals to restart user process.
*    argc, argv - arguments require to restart the process.
*   
* @Returns:
*    status according to the behaviour of the function.
*
* @Complexity
*    Time: O(1)
*/
status_t StartWD(size_t threshold, int argc, char *argv[]);

/*
* StopWD Description:
*    stop the watchdog.
*
* @Params:
*    none.
*
* @Returns:
*    none.
*
* @Complexity
*    Time: O(1)
*/
void StopWD(void);

#endif
