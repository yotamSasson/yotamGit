
#include <stdio.h> /*print*/
#include <stdlib.h>

#include "wd.h"

#define WD_OUT_IMAGE ("./wd.out")

int main (int argc, char *argv[])
{
    size_t threshold = atoi(getenv("THRESHOLD"));
    argv[0] = WD_OUT_IMAGE;
    if (FAILURE == StartWD(threshold, argc, argv))
    {
        perror("StartWD FAIL in WD \n");
        exit(1);
    }
    return 0;
}
