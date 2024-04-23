
#include <stdio.h> /*print*/
#include <stdlib.h>
#include <unistd.h> /*sleep*/

#include "wd.h"

int main (int argc, char *argv[])
{
    size_t i = 45;
    size_t threshold = 4;

    printf("In client\n");

    if (FAILURE == StartWD(threshold, argc, argv))
    {
        printf("StartWD FAIL \n");
    }

    for (; i != 0; --i)
    {
       printf("Im Still Running! %lu sec left\n", i);
        sleep(1);
    }
    
    StopWD();

    printf("END of client\n");
    return 0;
}
