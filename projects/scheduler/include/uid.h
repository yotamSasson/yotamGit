#ifndef MY_PROJECT_UID_H__
#define MY_PROJECT_UID_H__

#include <stddef.h> /* size_t */
#include <sys/types.h> /*getpid*/
#include <time.h> /*time_t*/
#include <unistd.h>

#define LINUX_IP_SIZE (14)

/* UID is a struct used for attaching a unique identifier to objects. */
struct uid
{
    time_t time_stamp;
    size_t counter;
    pid_t pid;
    unsigned char ip[LINUX_IP_SIZE];
};

typedef struct uid my_uid_t;


/*
* UIDCreate Description:
*	Creates a new UID. 
*
* @params:
*   None
*
* @returns:
*	my_uid_t struct
*
* @Complexity
*	O(1)
*/
my_uid_t UIDCreate(void); 

/*
* UIDIsSame Description:
*	Checks if two UIDs are the same.
*
* @params:
*   lhs, rhs - UIDs
*
* @returns:
*	1 if two UIDs are the same, 0 if not.
*
* @Complexity
*	O(1)
*/
int UIDIsSame(my_uid_t lhs, my_uid_t rhs); 

/*
* UIDGetBad Description:
*	Returns a UID with invalid fields.
*   This UID is used to represent a state of error.
*
* @params:
*   None.
*
* @returns:
*	UID.
*
* @Complexity
*	O(1)
*/
my_uid_t UIDGetBad(void);

#endif
