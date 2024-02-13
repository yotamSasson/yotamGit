#include <assert.h> /*assert*/
#include <string.h> /*strlen*/

#include "fsm.h"

#define STATE_COUNT 4
#define EVENT_COUNT 2

#define START_STATE 0
#define END_STATE 2

typedef enum state
{
    INITIAL = 0,
    MIDDLE = 1,
    ACCEPT = 2,
    NOT_ACCEPT = 3
}state_t;

typedef enum event
{
    EVENT_ZERO = 0,
    EVENT_ONE = 1
}event_t;

int state_transition_table[STATE_COUNT][EVENT_COUNT] = 
{
    {MIDDLE, NOT_ACCEPT},
    {ACCEPT, MIDDLE},
    {ACCEPT, MIDDLE},
    {NOT_ACCEPT, NOT_ACCEPT}
};

/************************ Functions ************************/

int IsAcceptable(char *str)
{
	int current_state = START_STATE;
	int input = EVENT_ZERO;
	size_t str_len = 0;
	size_t i = 0;
	
	assert(NULL != str);
	
	str_len = strlen(str);
	
	for (i = 0; i < str_len; ++i)
	{
        input = str[i] - '0';
        current_state = state_transition_table[current_state][input];
    }
    
    return current_state == END_STATE;
}

